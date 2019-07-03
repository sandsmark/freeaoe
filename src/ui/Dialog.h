#ifndef DIALOG_H
#define DIALOG_H

#include "TextButton.h"

namespace sf {
class Event;
class RenderWindow;
}

struct UiScreen;

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

    void render(std::shared_ptr<sf::RenderWindow> &renderTarget);
    Choice handleEvent(const sf::Event &event);

    sf::Texture background;
    UiScreen *m_screen;

private:
    std::array<TextButton, ChoicesCount> m_buttons;
    Choice m_pressedButton = Invalid;
};

#endif // DIALOG_H
