#include "NumberLabel.h"

#include "render/SfmlRenderTarget.h"

NumberLabel::NumberLabel(const int right, const int top) :
    m_right(right),
    m_top(top)
{
    text.setFont(SfmlRenderTarget::defaultFont());
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(16);
}

void NumberLabel::setValue(const int value)
{
    if (value == m_value) {
        return;
    }
    m_value = value;
    updateText();
}

void NumberLabel::setMaxValue(const int maxValue)
{
    if (maxValue == m_maxValue) {
        return;
    }
    m_maxValue = maxValue;
    updateText();
}

void NumberLabel::updatePosition()
{
    text.setPosition(sf::Vector2f(m_right - text.getLocalBounds().width, m_top));
}

void NumberLabel::updateText()
{
    std::string string = std::to_string(m_value);
    if (m_maxValue) {
        string += '/';
        string += std::to_string(m_maxValue);
    }
    text.setString(string);
    updatePosition();
}
