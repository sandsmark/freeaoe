#ifndef DIALOG_H
#define DIALOG_H

#include "TextButton.h"

#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <memory>

#include "render/IRenderTarget.h"

struct TextButton;

namespace sf {
class Event;
}

class IRenderTarget;

class UiScreen;

struct Dialog
{
    enum Choice {
        Invalid = -1,
        Quit,
        Achievements,
        Save,
        Options,
        About,
        Cancel,
        ChoicesCount
    };

    Dialog(UiScreen *screen);

    void render(const std::shared_ptr<Window> &window, const std::shared_ptr<IRenderTarget> &renderTarget);
    Choice handleEvent(const std::shared_ptr<Window::Event> &event);

    sf::Texture background;
    UiScreen *m_screen;

private:
    std::array<TextButton, ChoicesCount> m_buttons;
    Choice m_pressedButton = Invalid;
};

#endif // DIALOG_H
