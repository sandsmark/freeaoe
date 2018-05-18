#include "ActionPanel.h"
#include "mechanics/EntityManager.h"
#include "SfmlRenderTarget.h"
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <genie/resource/SlpFile.h>
#include <genie/dat/Unit.h>
#include "resource/Resource.h"

ActionPanel::ActionPanel(const std::shared_ptr<SfmlRenderTarget> &renderTarget) :
    m_renderTarget(renderTarget)
{
}


bool ActionPanel::init()
{
    m_unitIconsSlp = ResourceManager::Inst()->getSlp(ResourceManager::filenameID("btnunit.shp"));
    if (!m_unitIconsSlp) {
        std::cerr << "Failed to load unit icons" << std::endl;
        return false;
    }

    // ico_bld1-4.shp looks identical, for some reason
    m_buildingIconsSlp = ResourceManager::Inst()->getSlp(ResourceManager::filenameID("ico_bld2.shp"));
    if (!m_buildingIconsSlp) {
        std::cerr << "Failed to load building icons" << std::endl;
        return false;
    }

    m_actionIconsSlp = ResourceManager::Inst()->getSlp(ResourceManager::filenameID("btncmd.shp"));
    if (!m_actionIconsSlp) {
        std::cerr << "Failed to load action icons" << std::endl;
        return false;
    }

    m_researchIconsSlp = ResourceManager::Inst()->getSlp(ResourceManager::filenameID("btntech.shp"));
    if (!m_researchIconsSlp) {
        std::cerr << "Failed to load research icons" << std::endl;
        return false;
    }

    genie::SlpFilePtr icons = ResourceManager::Inst()->getSlp(50721, ResourceManager::ResourceType::Interface);
    std::cout << icons->getFrameCount() << std::endl;
    std::cout << int(Icon::IconCount) << std::endl;
    for (int i=0; i<int(Icon::IconCount); i++) {
        if (i >= icons->getFrameCount()) {
            std::cerr << "icon out of range " << i << std::endl;
            break;
        }
        m_icons[Icon(i)].loadFromImage(res::Resource::convertFrameToImage(icons->getFrame(i)));
    }

    return m_entityManager != nullptr;
}

void ActionPanel::handleEvent(sf::Event event)
{
    if (event.type != sf::Event::MouseButtonPressed && event.type != sf::Event::MouseButtonReleased) {
        return;
    }

    for (InterfaceButton &button : currentButtons) {
        if (!buttonRect(button.index).contains(ScreenPos(event.mouseButton.x, event.mouseButton.y))) {
            if (button.pressed) {
                m_dirty = true;
            }

            button.pressed = false;
            continue;
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (button.pressed) {
                m_dirty = true;
            }
            button.pressed = true;
        } else {
            if (button.pressed) {
                m_dirty = true;
            }
            button.pressed = false;
        }
    }
}

bool ActionPanel::update(Time /*time*/)
{
    if (m_entityManager->selected() != m_selectedEntities) {
        m_selectedEntities = m_entityManager->selected();
        updateButtons();
        m_dirty = true;
    }

    if (m_dirty) {
        m_dirty = false;
        return true;
    } else {
        return false;
    }
}

void ActionPanel::draw()
{
    for (const InterfaceButton &button : currentButtons) {
        sf::RectangleShape bevelRect(Size(40, 40));
        sf::RectangleShape shadowRect(Size(38, 38));

        bevelRect.setPosition(buttonPosition(button.index) - ScreenPos(2, 2));
        shadowRect.setPosition(buttonPosition(button.index));

        if (button.pressed) {
            bevelRect.setFillColor(sf::Color(64, 64, 64));
            shadowRect.setFillColor(sf::Color(192, 192, 192));
        } else {
            bevelRect.setFillColor(sf::Color(192, 192, 192));
            shadowRect.setFillColor(sf::Color(64, 64, 64));
        }

        m_renderTarget->draw(bevelRect);
        m_renderTarget->draw(shadowRect);

        m_renderTarget->draw(button.tex, buttonPosition(button.index));
    }
}

void ActionPanel::setEntityManager(const std::shared_ptr<EntityManager> &entityManager)
{
    m_entityManager = entityManager;
}

ScreenRect ActionPanel::rect() const
{
    ScreenRect r;
    r.height = 3 * 51;
    r.width = 5 * 55;
    r.x = 35;
//    r.y = 845;
    r.y = m_renderTarget->getSize().y - r.height - 25;
    return r;
}

void ActionPanel::releaseButtons()
{
    for (InterfaceButton &button : currentButtons) {
        if (button.pressed) {
            m_dirty = true;
        }

        button.pressed = false;
    }
}

void ActionPanel::updateButtons()
{
    currentButtons.clear();
    if (m_selectedEntities.empty()) {
        return;
    }

    Unit::Ptr unit = Entity::asUnit(*m_selectedEntities.begin());
    if (!unit) {
        return;
    }

    bool hasNext = false;
    bool hasPrevious = false;
    for (const genie::Unit *creatable : unit->creatableEntities()) {
        if (creatable->IconID >= m_unitIconsSlp->getFrameCount()) {
            std::cerr << "invalid icon id: " << creatable->IconID << std::endl;
            continue;
        }

        if (creatable->InterfaceKind != m_currentPage) {
            continue;
        }

        if (creatable->Creatable.ButtonID < m_buttonOffset) {
            hasPrevious = true;
            continue;
        }

        if (creatable->Creatable.ButtonID > m_buttonOffset + 15) {
            hasNext = true;
            continue;
        }

        InterfaceButton button;
        if (unit->data.InterfaceKind == genie::Unit::CiviliansInterface) {
            button.tex.loadFromImage(res::Resource::convertFrameToImage(m_buildingIconsSlp->getFrame(creatable->IconID)));
        } else {
            button.tex.loadFromImage(res::Resource::convertFrameToImage(m_unitIconsSlp->getFrame(creatable->IconID)));
        }
        button.index = std::max(creatable->Creatable.ButtonID - 1, 0);

        currentButtons.push_back(std::move(button));
    }

    if (hasNext) {
        InterfaceButton rightButton;
        rightButton.tex = m_icons[Icon::NextPage];
        rightButton.index = 14;
        currentButtons.push_back(rightButton);
    }
}

ScreenPos ActionPanel::buttonPosition(const int index) const
{
    ScreenPos position;
    position.x = index % 5;
    position.x = (position.x) * 50 + 55;
    position.y = index / 5;
    position.y *= 50;
    position.y += m_renderTarget->getSize().y  - 170;
    return position;
}

ScreenRect ActionPanel::buttonRect(const int index) const
{
    ScreenRect rect;
    const ScreenPos screenPos = buttonPosition(index);
    rect.x = screenPos.x;
    rect.y = screenPos.y;
    rect.width = 40;
    rect.height = 40;
    return rect;
}
