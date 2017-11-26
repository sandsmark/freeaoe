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

class IRenderTarget
{
public:
    //----------------------------------------------------------------------------
    IRenderTarget() {}

    //----------------------------------------------------------------------------
    virtual ~IRenderTarget() {}

    //----------------------------------------------------------------------------
    virtual Vector2u getSize(void) = 0;

    //----------------------------------------------------------------------------
    virtual void draw(EntityForm &form) = 0;

    //----------------------------------------------------------------------------
    virtual void draw(res::GraphicPtr graph, ScreenPos pos, int frame = 0,
                      int angle = 0) = 0;

    //----------------------------------------------------------------------------
    /// TODO: Remove sf:: from api
    virtual void draw(const sf::Image &image, ScreenPos pos) = 0;

    //----------------------------------------------------------------------------
    /// TODO: Remove sf:: from api
    virtual void draw(const sf::Texture &texture, ScreenPos pos) = 0;

    //----------------------------------------------------------------------------
    /// Displays frame.
    //
    virtual void display(void) = 0;
};

typedef std::shared_ptr<IRenderTarget> IRenderTargetPtr;

#endif // I_RENDER_TARGET_H
