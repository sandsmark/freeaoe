/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "core/Types.h"

#include <memory>

namespace sf {
class Sprite;
class Drawable;
class Texture;
class Shape;
class Image;
class Color;
class BlendMode; // TODO kill me
}

namespace genie{
class SlpFrame;
class PalFile;
typedef std::shared_ptr<SlpFrame> SlpFramePtr;
}

class IRenderTarget;

struct Camera;
using CameraPtr = std::shared_ptr<Camera>;

namespace Drawable {
struct Color {
    Color() = default;
    constexpr Color(const uint8_t r_, const uint8_t g_, const uint8_t b_, const uint8_t a_ = 255) :
        r(r_), g(g_), b(b_), a(a_) {}

    uint8_t r = 0, g = 0, b = 0, a = 255;

};
static constexpr Color Red(255, 0, 0);
static constexpr Color Green(0, 255, 0);
static constexpr Color Blue(0, 0, 255);
static constexpr Color Transparent(0, 0, 0, 0);
static constexpr Color White(255, 255, 255);
static constexpr Color Black;

struct Shape
{
    Color borderColor;
    float borderSize = 1;

    Color fillColor;

    bool filled = false;
};

struct Rect : public Shape
{
    ScreenRect rect;
};

struct Circle : public Shape
{
    int pointCount = 0;
    ScreenPos center;
    float radius = 0.f;
    float aspectRatio = 1.f;
};

struct Image
{
    typedef std::shared_ptr<Image> Ptr;
    static Ptr null;

    Size size;

    virtual bool isValid() const = 0;

protected:
    Image() {}

private:
    friend class IRenderTarget;
};

struct Text
{
    enum Alignment {
        AlignLeft, AlignRight
    } alignment = AlignLeft;

    typedef std::shared_ptr<Text> Ptr;

    ScreenPos position;
    std::string string;
    float pointSize = 12.;
    Color color = Black;
    Color outlineColor = Transparent;

    virtual float lineSpacing() = 0;

    virtual Size size() = 0;

    virtual ~Text() = default;

protected:
    Text() {}

private:
    friend class IRenderTarget;
};

}//namespace Drawable

struct TextureTarget
{

};

class IRenderTarget
{
public:
    //----------------------------------------------------------------------------
    IRenderTarget();

    //----------------------------------------------------------------------------
    virtual ~IRenderTarget() {}

    //----------------------------------------------------------------------------
    virtual Size getSize(void) const = 0;

    virtual void setSize(const Size size) const = 0;

    //----------------------------------------------------------------------------
    /// TODO: Remove sf:: from api
    virtual void draw(const sf::Image &image, ScreenPos pos) = 0;

    //----------------------------------------------------------------------------
    /// TODO: Remove sf:: from api
    virtual void draw(const sf::Texture &texture, ScreenPos pos) = 0;

    //----------------------------------------------------------------------------
    /// TODO: Remove sf:: from api
    virtual void draw(const sf::Drawable &shape) = 0;
    virtual void draw(const sf::Sprite &sprite) = 0;
    virtual void draw(const sf::Sprite &sprite, const sf::BlendMode &blendMode) = 0;

//    virtual void draw(const ScreenRect &rect, const sf::Color &fillColor, const sf::Color &outlineColor = sf::Color::Transparent, const float outlineSize = 1.) = 0;
    virtual void draw(const ScreenRect &rect, const Drawable::Color &fillColor, const Drawable::Color &outlineColor = Drawable::Transparent, const float outlineSize = 1.) = 0;

    //----------------------------------------------------------------------------
    /// Displays frame.
    //
    virtual void display(void) = 0;

    CameraPtr camera() { return m_camera; }

    virtual void draw(const Drawable::Rect &rect) = 0;
    virtual void draw(const Drawable::Circle &circle) = 0;
    virtual void draw(const std::shared_ptr<IRenderTarget> &renderTarget, const ScreenPos &pos = ScreenPos(0, 0)) = 0;
    virtual void draw(const std::shared_ptr<IRenderTarget> &renderTarget, const sf::BlendMode &blendMode) = 0;

    virtual Drawable::Image::Ptr createImage(const Size &size, const uint8_t *pixels) = 0;
    Drawable::Image::Ptr convertFrameToImage(const genie::SlpFramePtr &frame);
    Drawable::Image::Ptr convertFrameToImage(const genie::SlpFramePtr &frame, const genie::PalFile &palette, const int playerId = -1);
    virtual void draw(const Drawable::Image::Ptr &image, const ScreenPos &position) = 0;

    virtual std::shared_ptr<IRenderTarget> createTextureTarget(const Size &size) = 0;

    virtual Drawable::Text::Ptr createText() = 0;
    virtual void draw(const Drawable::Text::Ptr &text) = 0;

    virtual void clear(const Drawable::Color &color = Drawable::Color(0, 0, 0, 255)) = 0;


protected:
    CameraPtr m_camera;
};
using IRenderTargetPtr = std::shared_ptr<IRenderTarget>;

struct Window
{
    struct KeyEvent;
    struct MouseEvent;
    struct MouseScrollEvent;

    struct Event {
        using Ptr = std::shared_ptr<Event>;

        const enum Type {
            Invalid = -1,
            Quit,
            KeyPressed,
            KeyReleased,
            MousePressed,
            MouseReleased,
            MouseMoved,
            MouseScroll,
        } type = Invalid;

        bool isMouseEvent() const {
            return (type == MousePressed || type == MouseReleased || type == MouseMoved);
        }
        bool isKeyboardEvent() const {
            return (type == KeyPressed || type == KeyReleased);
        }
        bool isScrollEVent() const {
            return (type == MouseScroll);
        }

        static std::shared_ptr<KeyEvent> asKeyboardEvent(const std::shared_ptr<Event> &event) {
            if (!event || !event->isKeyboardEvent()) {
                return nullptr;
            }
            return static_pointer_cast<KeyEvent>(event);
        }
        static std::shared_ptr<MouseEvent> asMouseEvent(const std::shared_ptr<Event> &event) {
            if (!event || !event->isMouseEvent()) {
                return nullptr;
            }
            return static_pointer_cast<MouseEvent>(event);
        }
        static std::shared_ptr<MouseScrollEvent> asScrollEvent(const std::shared_ptr<Event> &event) {
            if (!event || !event->isScrollEVent()) {
                return nullptr;
            }
            return static_pointer_cast<MouseScrollEvent>(event);
        }


    protected:
        Event(const Type _type) : type(_type) {}
    };

    struct KeyEvent : public Event {
        using Ptr = std::shared_ptr<KeyEvent>;

        const enum Key {
            Invalid = -1,
            Left,
            Right,
            Up,
            Down
        } key;
        const bool isPressed = false;

    private:
        friend struct Window;

        KeyEvent(const Event::Type type, const Key key_) : Event(type),
            key(key_)
        {}
    };

    struct MouseEvent : public Event {
        using Ptr = std::shared_ptr<MouseEvent>;

        ScreenPos position;

        const enum Modifier {
            NoModifier = 0,
            Alt = 1 << 0,
            Ctrl = 1 << 1,
            Shift = 1 << 2
        } modifiers;
        const enum Button {
            NoButton = 0,
            LeftButton = 1 << 0,
            RightButton = 1 << 1,
            MiddleButton = 1 << 2
        } button;

    private:
        friend struct Window;
        MouseEvent(const Event::Type type_, const ScreenPos pos, const Modifier modifiers_, const Button button_) : Event(type_),
            position(pos),
            modifiers(modifiers_),
            button(button_)
        { }
    };

    struct MouseScrollEvent : public Event {
        using Ptr = std::shared_ptr<MouseScrollEvent>;

        const ScreenPos position;
        const int amount;
    private:
        friend struct Window;

        MouseScrollEvent(const ScreenPos pos, const int amount_) : Event(Event::MouseScroll),
          position(pos),
          amount(amount_)
        { }
    };

    static std::shared_ptr<Window> createWindow(const Size size, const std::string &title);

    virtual Size size() = 0;
    virtual void resize(const Size newSize) = 0;
    virtual std::shared_ptr<IRenderTarget> createRenderTarget() = 0;

    virtual bool isOpen() const = 0;
    virtual void close() = 0;
    virtual void update() = 0;

    virtual ScreenPos mapToLocal(const ScreenPos pos) = 0;

    virtual std::shared_ptr<Event> waitEvent() = 0;
    virtual std::shared_ptr<Event> pollEvent() = 0;
};
