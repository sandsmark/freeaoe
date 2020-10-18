#include "TextButton.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <utility>

#include "UiScreen.h"
#include "render/SfmlRenderTarget.h"

TextButton::TextButton()
{
    m_text.setCharacterSize(17);
    m_text.setOutlineThickness(1);
    m_text.setFont(SfmlRenderTarget::plainFont());

}

// SFML is fucking shit
void TextButton::drawLine(const ScreenPos &from, const ScreenPos &to, const sf::Color &color, UiScreen *screen)
{
    sf::RectangleShape shape;
    if (from.x != to.x) {
        shape.setSize(Size(to.x - from.x, 1));
    } else {
        shape.setSize(Size(1, to.y - from.y));
    }

    shape.setPosition(from.x, from.y);

    shape.setFillColor(color);
    screen->m_renderWindow->draw(shape);
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

    sf::Color outer1 = screen->m_bevelColor1c;
    sf::Color middle1 = screen->m_bevelColor1b;
    sf::Color inner1 = screen->m_bevelColor1a;

    sf::Color outer2 = screen->m_bevelColor2c;
    sf::Color middle2 =screen->m_bevelColor2b;
    sf::Color inner2 = screen->m_bevelColor2a;
    if (pressed) {
        std::swap(outer1, outer2);
        std::swap(middle1, middle2);
        std::swap(inner1, inner2);
    }

    // top horizontal
    drawLine(rect.topLeft() - ScreenPos(2, 2), rect.topRight() - ScreenPos(-2, 2), inner1, screen);
    drawLine(rect.topLeft() - ScreenPos(1, 1), rect.topRight() - ScreenPos(-1, 1), middle1, screen);
    drawLine(rect.topLeft() - ScreenPos(0, 0), rect.topRight() - ScreenPos(-0, 0), outer1, screen);

    // bottom horizontal
    drawLine(rect.bottomLeft() + ScreenPos(-2, 2), rect.bottomRight() + ScreenPos(2, 2), inner2, screen);
    drawLine(rect.bottomLeft() + ScreenPos(-1, 1), rect.bottomRight() + ScreenPos(1, 1), middle2, screen);
    drawLine(rect.bottomLeft() + ScreenPos(-0, 0), rect.bottomRight() + ScreenPos(0, 0), outer2, screen);

    // left vertical
    drawLine(rect.topLeft() - ScreenPos(2, 2), rect.bottomLeft() - ScreenPos(2, -2), inner2, screen);
    drawLine(rect.topLeft() - ScreenPos(1, 1), rect.bottomLeft() - ScreenPos(1, -1), middle2, screen);
    drawLine(rect.topLeft() - ScreenPos(0, 0), rect.bottomLeft() - ScreenPos(0, -0), outer2, screen);

    // right vertical
    drawLine(rect.topRight() + ScreenPos(-1, -0), rect.bottomRight() + ScreenPos(-1, 0), outer1, screen);
    drawLine(rect.topRight() + ScreenPos( 0, -1), rect.bottomRight() + ScreenPos( 0, 1), middle1, screen);
    drawLine(rect.topRight() + ScreenPos( 1, -2), rect.bottomRight() + ScreenPos( 1, 2), inner1, screen);

    ///////////////
    /// Render text
    m_text.setFillColor(screen->m_textFillColor);
    m_text.setOutlineColor(screen->m_textOutlineColor);
    m_text.setString(text);

    ScreenPos textPosition = rect.center();
    const sf::FloatRect textRect = m_text.getLocalBounds();
    textPosition.x -= textRect.width / 2;
    textPosition.y -= 3 * textRect.height / 4;

    if (pressed) {
        textPosition.x += screen->m_pressOffset;
        textPosition.y += screen->m_pressOffset;
    }

    m_text.setPosition(textPosition);

    screen->m_renderWindow->draw(m_text);
}
