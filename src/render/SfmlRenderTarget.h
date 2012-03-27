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


#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include <core/Entity.h>
#include <resource/Graphic.h>
#include <SFML/Graphics/Texture.hpp>
#include "IRenderTarget.h"

namespace sf {
class RenderTarget;
}

class SfmlRenderTarget : public IRenderTarget
{

public:
  SfmlRenderTarget(sf::RenderTarget &render_target);
  virtual ~SfmlRenderTarget();
  
  //----------------------------------------------------------------------------
  void draw(EntityForm &form);
  
  //----------------------------------------------------------------------------
  void draw(res::GraphicPtr graph, ScreenPos pos, int frame=0, int angle=0);
  
  //----------------------------------------------------------------------------
  void draw(const sf::Image &image, ScreenPos pos);
  
  //----------------------------------------------------------------------------
  void draw(const sf::Texture &texture, ScreenPos pos);
  
  //----------------------------------------------------------------------------
  /// Displays frame.
  //
  void display(void);
  
private:
  sf::RenderTarget *render_target_;
};

#endif // GAMERENDERER_H
