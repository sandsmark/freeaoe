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
struct BlendMode;
}

namespace genie{
class SlpFrame;
class PalFile;
typedef std::shared_ptr<SlpFrame> SlpFramePtr;
}

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

    float scaleX = 1.f, scaleY = 1.f;

    virtual bool isValid() const = 0;

    virtual ~Image();
protected:
    Image() {}

private:
    friend class IRenderTarget;
};

struct Text
{
    enum Style {
        Plain,
        UI,
        Stylish
    };

    enum Alignment : int {
        AlignLeft = 1 << 0,
        AlignRight = 1 << 1,
        AlignVCenter = 1 << 2,
        AlignTop = 1 << 3,
        AlignBottom = 1 << 4,
        AlignHCenter = 1 << 5,
        AlignCenter =  AlignVCenter | AlignHCenter,
    } alignment = Alignment(AlignLeft | AlignTop);

    void setAlignment(int align) { alignment = Alignment(align); }

    typedef std::shared_ptr<Text> Ptr;

    ScreenPos position;
    std::string string;
    float pointSize = 12.;
    Color color = Black;
    Color outlineColor = Transparent;

    virtual float lineSpacing() = 0;

    virtual Size size() = 0;

    virtual ~Text();

protected:
    Text() {}

private:
    friend class IRenderTarget;
};

} //namespace Drawable

class IRenderTarget
{
public:
    //----------------------------------------------------------------------------
    IRenderTarget();

    //----------------------------------------------------------------------------
    virtual ~IRenderTarget();

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
    virtual void draw(const std::shared_ptr<IRenderTarget> &renderTarget, const sf::BlendMode &blendMode) = 0;

    //----------------------------------------------------------------------------
    /// Displays frame.
    //
    virtual void display(void) = 0;

    CameraPtr camera() { return m_camera; }

    virtual void draw(const Drawable::Rect &rect) = 0;
    virtual void draw(const Drawable::Circle &circle) = 0;
    virtual void draw(const std::shared_ptr<IRenderTarget> &renderTarget, const ScreenPos &pos = ScreenPos(0, 0)) = 0;

    virtual Drawable::Image::Ptr createImage(const Size &size, const uint8_t *pixels) const = 0;
    Drawable::Image::Ptr convertFrameToImage(const genie::SlpFramePtr &frame) const;
    Drawable::Image::Ptr convertFrameToImage(const genie::SlpFramePtr &frame, const genie::PalFile &palette, const int playerId = -1) const;
    virtual Drawable::Image::Ptr loadImage(const uint8_t *data, const size_t dataSize) const = 0;

    virtual void draw(const Drawable::Image::Ptr &image, const ScreenPos &position) = 0;

    virtual std::shared_ptr<IRenderTarget> createTextureTarget(const Size &size) const = 0;

    virtual Drawable::Text::Ptr createText(const Drawable::Text::Style style = Drawable::Text::Plain) const = 0;
    virtual void draw(const Drawable::Text::Ptr &text) = 0;

    virtual void clear(const Drawable::Color &color = Drawable::Color(0, 0, 0, 255)) = 0;

protected:
    CameraPtr m_camera;
};

namespace Drawable {
struct Window
{
    virtual ~Window() = default;

    std::unique_ptr<IRenderTarget> renderTarget;

    virtual bool isOpen() const = 0;
    virtual void close() = 0;

    //----------------------------------------------------------------------------
    /// Displays frame.
    //
    virtual void display(void) = 0;
protected:
    Window() = default;
};
}//namespace Drawable

typedef std::shared_ptr<IRenderTarget> IRenderTargetPtr;

