#pragma once

#include <SFML/Graphics/Text.hpp>

#include <memory>

class IRenderTarget;
struct ScreenPos;

struct NumberLabel
{
    NumberLabel(std::shared_ptr<IRenderTarget> renderTarget);

    bool setValue(const int value);
    bool setMaxValue(const int maxValue);
    void setPosition(const ScreenPos &pos);

    void render();

private:
    void updatePosition();

    void updateText();

    int m_maxValue = 0;
    int m_value = 0;

    int m_right = 0;
    int m_top = 0;
    sf::Text m_text;

    std::shared_ptr<IRenderTarget> m_renderTarget;
};
