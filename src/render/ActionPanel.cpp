#include "ActionPanel.h"
#include "mechanics/EntityManager.h"
#include "SfmlRenderTarget.h"
#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>

ActionPanel::ActionPanel(const std::shared_ptr<SfmlRenderTarget> &renderTarget) :
    m_renderTarget(renderTarget)
{
}


bool ActionPanel::init()
{
    return m_entityManager != nullptr;
}

void ActionPanel::handleEvent(sf::Event event)
{
    if (event.type != sf::Event::MouseButtonPressed && event.type != sf::Event::MouseButtonReleased) {
        return;
    }

    const Size screenSize = m_renderTarget->getSize();
    for (EntityManager::InterfaceButton &button : m_entityManager->currentButtons) {
        if (!button.rect(screenSize).contains(ScreenPos(event.mouseButton.x, event.mouseButton.y))) {
            button.pressed = false;
            continue;
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            button.pressed = true;
        } else {
            if (button.pressed) {
                std::cout << "pressed button " << button.index << std::endl;
            }
            button.pressed = false;
        }
    }
}

bool ActionPanel::update(Time /*time*/)
{
    return false;
}

void ActionPanel::draw()
{
    const Size screenSize = m_renderTarget->getSize();
    for (const EntityManager::InterfaceButton &button : m_entityManager->currentButtons) {
        sf::RectangleShape bevelRect(Size(40, 40));
        sf::RectangleShape shadowRect(Size(38, 38));

        bevelRect.setPosition(button.position(screenSize) - ScreenPos(2, 2));
        shadowRect.setPosition(button.position(screenSize));

        if (button.pressed) {
            bevelRect.setFillColor(sf::Color(64, 64, 64));
            shadowRect.setFillColor(sf::Color(192, 192, 192));
        } else {
            bevelRect.setFillColor(sf::Color(192, 192, 192));
            shadowRect.setFillColor(sf::Color(64, 64, 64));
        }

        m_renderTarget->draw(bevelRect);
        m_renderTarget->draw(shadowRect);

        m_renderTarget->draw(button.tex, button.position(screenSize));
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
    for (EntityManager::InterfaceButton &button : m_entityManager->currentButtons) {
        button.pressed = false;
    }
}
