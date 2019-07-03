#include "Dialog.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

Dialog::Dialog(UiScreen *screen) :
    m_screen(screen)
{
    m_buttons[Quit].text = "Quit";
    m_buttons[Achievements].text = "Achivements (TODO)";
    m_buttons[Save].text = "Save (TODO)";
    m_buttons[Options].text = "Options (TODO)";
    m_buttons[About].text = "About (TODO)";
    m_buttons[Cancel].text = "Cancel";

}

void Dialog::render(std::shared_ptr<sf::RenderWindow> &renderTarget)
{
    Size windowSize = renderTarget->getSize();
    Size textureSize(295, 300); //background.getSize(); can't use the actual size, because of the shadow...
    const ScreenPos windowCenter(windowSize.width / 2, windowSize.height / 2);
    ScreenPos position(windowCenter.x - textureSize.width/2, windowCenter.y - textureSize.height/2);
    sf::Sprite sprite;
    sprite.setPosition(position);
    sprite.setTexture(background);
    renderTarget->draw(sprite);

    const int buttonWidth = textureSize.width - 80;
    const int buttonHeight = 30;
    const int buttonMargin = 10;

    const int allButtonsHeight = ChoicesCount * (buttonHeight + buttonMargin);


    const int x = windowCenter.x - buttonWidth/2;
    int y = windowCenter.y - allButtonsHeight / 2;

    for (int i=0; i<ChoicesCount; i++) {
        m_buttons[i].rect.x = x;
        m_buttons[i].rect.y = y;

        m_buttons[i].rect.height = buttonHeight;
        m_buttons[i].rect.width = buttonWidth;
        y += buttonHeight + buttonMargin;

        m_buttons[i].render(m_screen);
    }
}

Dialog::Choice Dialog::handleEvent(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonReleased) {
        const ScreenPos mousePos(event.mouseButton.x, event.mouseButton.y);
        Choice choice = Invalid;
        for (int i=0; i<ChoicesCount; i++) {
            m_buttons[i].pressed = false;

            if (m_buttons[i].rect.contains(mousePos)) {
                choice = Choice(i);
            }
        }

        if (choice != m_pressedButton) {
            m_pressedButton = Invalid;

        }

        return m_pressedButton;
    }
    if (event.type != sf::Event::MouseButtonPressed) {
        return Invalid;
    }
    const ScreenPos mousePos(event.mouseButton.x, event.mouseButton.y);
    for (int i=0; i<ChoicesCount; i++) {
        if (m_buttons[i].rect.contains(mousePos)) {
            m_pressedButton = Choice(i);
            m_buttons[i].pressed = true;
        } else {
            m_buttons[i].pressed = false;
        }
    }

    return Invalid;
}
