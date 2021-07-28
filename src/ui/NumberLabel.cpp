#include "NumberLabel.h"

#include "render/IRenderTarget.h"
#include "render/SfmlRenderTarget.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>

NumberLabel::NumberLabel(std::shared_ptr<IRenderTarget> renderTarget) :
    m_renderTarget(std::move(renderTarget))
{
    m_text.setFont(SfmlRenderTarget::uiFont());
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setOutlineThickness(1);
    m_text.setFillColor(sf::Color::White);
    m_text.setCharacterSize(16);
}

bool NumberLabel::setValue(const int value)
{
    if (value == m_value) {
        return false;
    }
    m_value = value;
    updateText();
    return true;
}

bool NumberLabel::setMaxValue(const int maxValue)
{
    if (maxValue == m_maxValue) {
        return false;
    }
    m_maxValue = maxValue;
    updateText();
    return true;
}

void NumberLabel::setPosition(const ScreenPos &pos)
{
    m_top = pos.y;
    m_right = pos.x;
}

void NumberLabel::render()
{
    m_renderTarget->draw(m_text);
}

void NumberLabel::updatePosition()
{
    m_text.setPosition(sf::Vector2f(m_right - m_text.getLocalBounds().width, m_top));
}

void NumberLabel::updateText()
{
    std::string string = std::to_string(m_value);
    if (m_maxValue) {
        string += '/';
        string += std::to_string(m_maxValue);
    }
    m_text.setString(string);
    updatePosition();
}
