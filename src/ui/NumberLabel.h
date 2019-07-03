#pragma once

#include <SFML/Graphics/Text.hpp>

struct NumberLabel
{
    NumberLabel(const int right, const int top);

    void setValue(const int value);

    void setMaxValue(const int maxValue);

    sf::Text text;

private:
    void updatePosition();

    void updateText();

    int m_maxValue = 0;
    int m_value = 0;

    const int m_right = 0;
    const int m_top = 0;
};
