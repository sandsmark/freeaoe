#include "TextButton.h"

#include "render/IRenderTarget.h"
#include "render/SfmlRenderTarget.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "UiScreen.h"

TextButton::TextButton()
{
    m_text.setCharacterSize(17);
    m_text.setOutlineThickness(1);
    m_text.setFont(SfmlRenderTarget::defaultFont());
}

void TextButton::render(UiScreen *screen)
{
    /////////////////////////////////
    /// Render background and borders
    sf::RectangleShape background;
    background.setFillColor(sf::Color(0, 0, 0, screen->m_buttonOpacity * 255));
    background.setSize(rect.size());
    background.setPosition(rect.topLeft());
    screen->m_renderWindow->draw(background);

    const ScreenPos borderOffset(1, 1);
    const int borderWidth = 3;

    sf::RectangleShape horizontalBorder;
    horizontalBorder.setSize(Size(302, borderWidth));

    sf::RectangleShape verticalBorder;
    verticalBorder.setSize(Size(borderWidth, 42));

    horizontalBorder.setFillColor(screen->m_bevelColor1);
    verticalBorder.setFillColor(screen->m_bevelColor2);
    verticalBorder.setPosition(rect.topLeft() - ScreenPos(1, 1));
    screen->m_renderWindow->draw(verticalBorder);
    horizontalBorder.setPosition(rect.topLeft() - ScreenPos(1, 1));
    screen->m_renderWindow->draw(horizontalBorder);

    horizontalBorder.setFillColor(screen->m_bevelColor2);
    horizontalBorder.setPosition(rect.bottomLeft() + ScreenPos(-1, 1 - borderWidth));
    screen->m_renderWindow->draw(horizontalBorder);
    verticalBorder.setFillColor(screen->m_bevelColor1);
    verticalBorder.setPosition(rect.topRight() + ScreenPos(1 - borderWidth, -1));
    screen->m_renderWindow->draw(verticalBorder);



    ///////////////
    /// Render text
    m_text.setFillColor(screen->m_textFillColor);
    m_text.setOutlineColor(screen->m_textOutlineColor);
    m_text.setString(text);

    ScreenPos textPosition = rect.center();
    const sf::FloatRect textRect = m_text.getLocalBounds();
    textPosition.x -= textRect.width / 2;
    textPosition.y -= 3 * textRect.height / 4;
    m_text.setPosition(textPosition);

    screen->m_renderWindow->draw(m_text);
}
