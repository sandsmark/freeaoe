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

#ifndef I_RENDER_TARGET_H
#define I_RENDER_TARGET_H

#include <core/Entity.h>
#include <resource/Graphic.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shape.hpp>
#include "render/Camera.h"

class IRenderTarget
{
public:
    //----------------------------------------------------------------------------
    IRenderTarget() : m_camera(std::make_shared<Camera>()) {}

    //----------------------------------------------------------------------------
    virtual ~IRenderTarget() {}

    //----------------------------------------------------------------------------
    virtual Vector2u getSize(void) const = 0;

    virtual void setSize(const Size size) const = 0;

    //----------------------------------------------------------------------------
//    virtual void draw(res::GraphicPtr graph, ScreenPos pos, int frame = 0,
//                      float angle = 0) = 0;

    //----------------------------------------------------------------------------
    /// TODO: Remove sf:: from api
    virtual void draw(const sf::Image &image, ScreenPos pos) = 0;

    //----------------------------------------------------------------------------
    /// TODO: Remove sf:: from api
    virtual void draw(const sf::Texture &texture, ScreenPos pos) = 0;

    //----------------------------------------------------------------------------
    /// TODO: Remove sf:: from api
    virtual void draw(const sf::Shape &shape) = 0;

    virtual void draw(const ScreenRect &rect, const sf::Color &fillColor, const sf::Color &outlineColor = sf::Color::Transparent, const float outlineSize = 1.) = 0;

    //----------------------------------------------------------------------------
    /// Displays frame.
    //
    virtual void display(void) = 0;

    CameraPtr camera() { return m_camera; }

    ScreenPos absoluteScreenPos(MapPos mpos) {
        const MapPos absoluteMapPos = camera()->getTargetPosition() - mpos;
        ScreenPos spos = absoluteMapPos.toScreen();

        const ScreenPos screenCenter(getSize().x / 2.0, getSize().y / 2.0);
        spos.x = screenCenter.x - spos.x;
        spos.y = screenCenter.y + spos.y;

        return spos;
    }

    MapPos absoluteMapPos(ScreenPos pos) {
        ScreenPos camCenter;
        camCenter.x = getSize().x / 2.0;
        camCenter.y = getSize().y / 2.0;

        pos.y = getSize().y - pos.y;

        // relative map positions (from center)
        MapPos nullCenterMp = camCenter.toMap();

        MapPos nullPos = pos.toMap();

        MapPos relPos;
        relPos.x = nullPos.x - nullCenterMp.x;
        relPos.y = nullPos.y - nullCenterMp.y;

        MapPos absMapPos = camera()->getTargetPosition() + (nullPos - nullCenterMp);

        return absMapPos;

    }

    MapRect absoluteMapRect(const ScreenRect &screenRect) {
        return MapRect(absoluteMapPos(screenRect.topLeft()), absoluteMapPos(screenRect.bottomRight()));
    }

private:
    CameraPtr m_camera;
};

typedef std::shared_ptr<IRenderTarget> IRenderTargetPtr;

#endif // I_RENDER_TARGET_H
