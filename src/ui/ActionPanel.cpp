#include "ActionPanel.h"
#include "mechanics/UnitManager.h"
#include "render/SfmlRenderTarget.h"
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include <genie/resource/SlpFile.h>
#include <genie/dat/Unit.h>
#include <genie/dat/UnitCommand.h>
#include "resource/DataManager.h"
#include "resource/Resource.h"
#include "mechanics/UnitFactory.h"

ActionPanel::ActionPanel(const std::shared_ptr<SfmlRenderTarget> &renderTarget) :
    m_renderTarget(renderTarget)
{
}


bool ActionPanel::init()
{
    genie::SlpFilePtr unitIconsSlp = AssetManager::Inst()->getSlp("btnunit.shp", AssetManager::ResourceType::Interface);
    if (!unitIconsSlp) {
        WARN << "Failed to load unit icons";
        return false;
    }
    for (size_t i=0; i<unitIconsSlp->getFrameCount(); i++) {
        m_unitIcons[i].loadFromImage(Resource::convertFrameToImage(unitIconsSlp->getFrame(i)));
    }

    // ico_bld1-4.shp looks identical, for some reason
    genie::SlpFilePtr buildingIconsSlp = AssetManager::Inst()->getSlp("ico_bld2.shp", AssetManager::ResourceType::Interface);
    if (!buildingIconsSlp) {
        WARN << "Failed to load building icons";
        return false;
    }
    for (size_t i=0; i<buildingIconsSlp->getFrameCount(); i++) {
        m_buildingIcons[i].loadFromImage(Resource::convertFrameToImage(buildingIconsSlp->getFrame(i)));
    }

    genie::SlpFilePtr researchIconsSlp = AssetManager::Inst()->getSlp("btntech.shp", AssetManager::ResourceType::Interface);
    if (!researchIconsSlp) {
        WARN << "Failed to load research icons";
        return false;
    }
    for (size_t i=0; i<researchIconsSlp->getFrameCount(); i++) {
        m_researchIcons[i].loadFromImage(Resource::convertFrameToImage(researchIconsSlp->getFrame(i)));
    }

    genie::SlpFilePtr commandIconsSlp = AssetManager::Inst()->getSlp("btncmd.shp", AssetManager::ResourceType::Interface);
    if (!commandIconsSlp) {
        WARN << "Failed to load action icons";
        return false;
    }
    for (size_t i=0; i<int(Command::IconCount); i++) {
        if (i >= commandIconsSlp->getFrameCount()) {
            WARN << "icon out of range " << i;
            return false;
        }
        m_commandIcons[Command(i)].loadFromImage(Resource::convertFrameToImage(commandIconsSlp->getFrame(i)));
    }

    { // hax
        sf::Image prevImage = Resource::convertFrameToImage(commandIconsSlp->getFrame(int(Command::NextPage)));
        prevImage.flipHorizontally();
        m_commandIcons[Command::PreviousPage].loadFromImage(prevImage);
    }

    { // can't find this icon anywhere else
        genie::SlpFilePtr cursorsSlp = AssetManager::Inst()->getSlp("mcursors.shp", AssetManager::ResourceType::Interface);
        if (!cursorsSlp) {
            WARN << "Failed to load cursors";
            return false;
        }
        sf::Image garrisonIcon = Resource::convertFrameToImage(cursorsSlp->getFrame(13));
        m_commandIcons[Command::Garrison].loadFromImage(garrisonIcon);
    }

    return m_unitManager != nullptr;
}

void ActionPanel::handleEvent(sf::Event event)
{
    if (event.type != sf::Event::MouseButtonPressed && event.type != sf::Event::MouseButtonReleased) {
        return;
    }

    for (InterfaceButton &button : currentButtons) {
        if (button.interfacePage != m_currentPage) {
            continue;
        }

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
                handleButtonClick(button);
            }
            button.pressed = false;
        }
    }
}

bool ActionPanel::update(Time /*time*/)
{
    if (m_unitManager->selected() != m_selectedUnits) {
        m_selectedUnits = m_unitManager->selected();
        updateButtons();
        m_dirty = true;
    }

    if (m_dirty) {
        m_dirty = false;
        return true;
    }

    return false;
}

void ActionPanel::draw()
{
    for (const InterfaceButton &button : currentButtons) {
        if (button.interfacePage != m_currentPage) {
            continue;
        }

        sf::RectangleShape bevelRect(Size(40, 40));
        sf::RectangleShape shadowRect(Size(38, 38));

        // need this because the garrison icon is actually a cursor
        sf::RectangleShape backgroundRect(Size(36, 36));
        backgroundRect.setFillColor(sf::Color::Black);

        bevelRect.setPosition(buttonPosition(button.index) - ScreenPos(2, 2));
        shadowRect.setPosition(buttonPosition(button.index));
        backgroundRect.setPosition(buttonPosition(button.index));

        if (button.pressed) {
            bevelRect.setFillColor(sf::Color(64, 64, 64));
            shadowRect.setFillColor(sf::Color(192, 192, 192));
        } else {
            bevelRect.setFillColor(sf::Color(192, 192, 192));
            shadowRect.setFillColor(sf::Color(64, 64, 64));
        }

        m_renderTarget->draw(bevelRect);
        m_renderTarget->draw(shadowRect);
        m_renderTarget->draw(backgroundRect);

        switch(button.type) {
        case InterfaceButton::CreateBuilding:
            m_renderTarget->draw(m_buildingIcons[button.iconId], buttonPosition(button.index));
            break;
        case InterfaceButton::CreateUnit:
            m_renderTarget->draw(m_unitIcons[button.iconId], buttonPosition(button.index));
            break;
        case InterfaceButton::Research:
            m_renderTarget->draw(m_researchIcons[button.iconId], buttonPosition(button.index));
            break;
        case InterfaceButton::Other:
            m_renderTarget->draw(m_commandIcons[button.action], buttonPosition(button.index));
            break;
        }
//        m_renderTarget->draw(button.tex, buttonPosition(button.index));
    }
}

void ActionPanel::setUnitManager(const std::shared_ptr<UnitManager> &unitManager)
{
    m_unitManager = unitManager;
}

void ActionPanel::setHumanPlayer(const Player::Ptr &player)
{
    m_humanPlayer = player;
}

ScreenRect ActionPanel::rect() const
{
    ScreenRect r;
    r.height = 3 * 51;
    r.width = 5 * 55;
    r.x = 35;
//    r.y = 845;
    r.y = m_renderTarget->getSize().height - r.height - 25;
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
    if (m_selectedUnits.empty()) {
        return;
    }

    Unit::Ptr unit = *m_selectedUnits.begin();

    if (unit->data()->Type >= genie::Unit::MovingType && unit->data()->Type < genie::Unit::BuildingType && unit->player.lock() == m_humanPlayer) {
        InterfaceButton killButton;
        killButton.action = Command::Kill;
        killButton.index = 3;
        currentButtons.push_back(killButton);
    }

    const std::unordered_set<Task> actions = unit->availableActions();
    std::unordered_set<int16_t> addedTypes;
    for (const Task &task : actions) {
        if (addedTypes.count(task.data->ActionType)) {
            continue;
        }
        addedTypes.insert(task.data->ActionType);

        switch(task.data->ActionType) {
        case genie::Task::Garrison: {
            InterfaceButton garrisonButton;
            garrisonButton.action = Command::Garrison;
            garrisonButton.index = 4;
            currentButtons.push_back(garrisonButton);
            break;
        }
        case genie::Task::Build: {
            InterfaceButton backButton;
            backButton.action = Command::PreviousPage;
            backButton.index = 14;
            backButton.interfacePage = genie::Unit::BuildingsInterface;
            currentButtons.push_back(backButton);
            backButton.interfacePage = genie::Unit::MilitaryBuildingsInterface;
            currentButtons.push_back(backButton);

            InterfaceButton civilianButton;
            civilianButton.action = Command::BuildCivilian;
            civilianButton.index = 0;
            currentButtons.push_back(civilianButton);

            InterfaceButton militaryButton;
            militaryButton.action = Command::BuildMilitary;
            militaryButton.index = 1;
            currentButtons.push_back(militaryButton);

            InterfaceButton repairButton;
            repairButton.action = Command::Repair;
            repairButton.index = 2;
            currentButtons.push_back(repairButton);
            break;
        }
        default:
            break;
        }
    }

    if (!actions.empty()) {
        InterfaceButton stopButton;
        stopButton.action = Command::Stop;
        stopButton.index = 9;
        currentButtons.push_back(stopButton);
    }

    addCreateButtons(unit);
}

void ActionPanel::addCreateButtons(const std::shared_ptr<Unit> &unit)
{
    m_currentPage = 0;
    const std::vector<const genie::Unit *> creatableUnits = unit->creatableUnits();

    if (creatableUnits.empty()) {
        return;
    }

    if (unit->data()->Type >= genie::Unit::BuildingType) {
        InterfaceButton rallypointButton;
        rallypointButton.action = Command::SetRallyPoint;
        rallypointButton.index = 4;
        currentButtons.push_back(rallypointButton);
    }

    bool hasNext = false;
    for (const genie::Unit *creatable : creatableUnits) {
        if (creatable->Creatable.ButtonID > m_buttonOffset + 15) {
            hasNext = true;
            continue;
        }

        InterfaceButton button;
        if (unit->data()->InterfaceKind == genie::Unit::CiviliansInterface) {
            button.type = InterfaceButton::CreateBuilding;
            button.interfacePage = creatable->InterfaceKind;
        } else {
            button.type = InterfaceButton::CreateUnit;
            button.interfacePage = 0;
        }
        button.index = std::max(creatable->Creatable.ButtonID - 1, 0);
        button.targetId = creatable->ID;
        button.iconId = creatable->IconID;

        currentButtons.push_back(button);
    }

    if (hasNext) {
        InterfaceButton rightButton;
        rightButton.action = Command::NextPage;
        rightButton.index = 14;
        currentButtons.push_back(rightButton);
    }
}

void ActionPanel::handleButtonClick(const ActionPanel::InterfaceButton &button)
{
    if (button.type == InterfaceButton::CreateBuilding) {
        m_unitManager->placeBuilding(button.targetId, m_humanPlayer);
        return;
    }

    if (button.type == InterfaceButton::Other) {
        switch(button.action) {
        case Command::BuildMilitary:
            m_currentPage = genie::Unit::MilitaryBuildingsInterface;
            break;
        case Command::BuildCivilian:
            m_currentPage = genie::Unit::BuildingsInterface;
            break;
        case Command::PreviousPage:
            m_currentPage = 0;
            break;
        default:
            break;
        }
    }
}

ScreenPos ActionPanel::buttonPosition(const int index) const
{
    ScreenPos position;
    position.x = index % 5;
    position.x = (position.x) * 50 + 55;
    position.y = index / 5;
    position.y *= 50;
    position.y += m_renderTarget->getSize().height  - 170;
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
