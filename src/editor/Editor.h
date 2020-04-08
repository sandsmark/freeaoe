#pragma once

#include "ui/UiScreen.h"
#include "ui/TextButton.h"

namespace sf
{
class Clock;
class Event;
class RenderWindow;
}

class SfmlRenderTarget;
struct MouseCursor;

class Editor : public UiScreen
{
public:
    Editor();
    virtual ~Editor();

    void render() override;
    bool init() override;
    bool handleMouseEvent(const Window::MouseEvent::Ptr &event) override;

private:
    TextButton m_exitButton;
};
