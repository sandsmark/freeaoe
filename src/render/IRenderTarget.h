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
}

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

    virtual void draw(const ScreenRect &rect, const sf::Color &fillColor, const sf::Color &outlineColor = sf::Color::Transparent, const float outlineSize = 1.) = 0;

    //----------------------------------------------------------------------------
    /// Displays frame.
    //
    virtual void display(void) = 0;

    CameraPtr camera() { return m_camera; }


protected:
    CameraPtr m_camera;
};

typedef std::shared_ptr<IRenderTarget> IRenderTargetPtr;

