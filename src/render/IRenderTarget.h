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

#include "render/Camera.h"
#include <SFML/Graphics/Color.hpp>

namespace sf {
class Sprite;
class Drawable;
class Texture;
class Shape;
class Image;
}

namespace sf {
class Sprite;
class Image;
class Texture;
class Drawable;
class Color;
}

namespace genie{
class SlpFrame;
class PalFile;
typedef std::shared_ptr<SlpFrame> SlpFramePtr;
}

namespace Drawable {
struct Color {
    Color() = default;
    Color(const uint8_t r_, const uint8_t g_, const uint8_t b_, const uint8_t a_ = 255) :
        r(r_), g(g_), b(b_), a(a_) {}

    uint8_t r = 0, g = 0, b = 0, a = 0;

};
static const Color Red(255, 0, 0);
static const Color Green(0, 255, 0);
static const Color Blue(0, 0, 255);
static const Color Transparent(0, 0, 0, 0);
static const Color White(255, 255, 255);
static const Color Black;

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
    ScreenRect boundingRect;

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

protected:
    Text() {}

private:
    friend class IRenderTarget;
};

}

struct Window
{

};

struct TextureTarget
{

};

class IRenderTarget
{
public:
    //----------------------------------------------------------------------------
    IRenderTarget() : m_camera(std::make_shared<Camera>()) {}

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

//    virtual void draw(const ScreenRect &rect, const sf::Color &fillColor, const sf::Color &outlineColor = sf::Color::Transparent, const float outlineSize = 1.) = 0;
    virtual void draw(const ScreenRect &rect, const Drawable::Color &fillColor, const Drawable::Color &outlineColor = Drawable::Transparent, const float outlineSize = 1.) = 0;

    //----------------------------------------------------------------------------
    /// Displays frame.
    //
    virtual void display(void) = 0;

    CameraPtr camera() { return m_camera; }

    virtual void draw(const Drawable::Rect &rect) = 0;
    virtual void draw(const Drawable::Circle &circle) = 0;
    virtual void draw(const std::shared_ptr<IRenderTarget> &renderTarget) = 0;

    virtual Drawable::Image::Ptr createImage(const Size &size, const uint8_t *pixels) = 0;
    Drawable::Image::Ptr convertFrameToImage(const genie::SlpFramePtr &frame);
    Drawable::Image::Ptr convertFrameToImage(const genie::SlpFramePtr &frame, const genie::PalFile &palette, const int playerId = -1);
    virtual void draw(const Drawable::Image::Ptr &image, const ScreenPos &position) = 0;

    virtual std::shared_ptr<IRenderTarget> createTextureTarget(const Size &size) = 0;

    virtual Drawable::Text::Ptr createText() = 0;
    virtual void draw(const Drawable::Text::Ptr &text) = 0;

    virtual void clear() = 0;


protected:
    CameraPtr m_camera;
};

typedef std::shared_ptr<IRenderTarget> IRenderTargetPtr;

