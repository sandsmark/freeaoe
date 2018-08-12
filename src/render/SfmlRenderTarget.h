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

#include <core/Entity.h>
#include <resource/Graphic.h>
#include <SFML/Graphics/Texture.hpp>
#include "IRenderTarget.h"

namespace sf {
class RenderTarget;
class Font;
}

class SfmlRenderTarget : public IRenderTarget
{

public:
    static const sf::Font &defaultFont();

    SfmlRenderTarget(sf::RenderTarget &render_target);
    virtual ~SfmlRenderTarget();

    //----------------------------------------------------------------------------
    Size getSize() const override;
    void setSize(const Size size) const override;

    //----------------------------------------------------------------------------
    void draw(const sf::Image &image, ScreenPos pos) override;

    //----------------------------------------------------------------------------
    void draw(const sf::Texture &texture, ScreenPos pos) override;

    //----------------------------------------------------------------------------
    void draw(const sf::Drawable &shape) override;

    void draw(const ScreenRect &rect, const sf::Color &fillColor, const sf::Color &outlineColor = sf::Color::Transparent, const float outlineSize = 1.) override;

    //----------------------------------------------------------------------------
    /// Displays frame.
    //
    void display() override;

    sf::RenderTarget *renderTarget_;
private:
};

