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


#ifndef RENDERGRAPHIC_H
#define RENDERGRAPHIC_H
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <data/GenieGraphic.h>

class SlpFile;

class RenderGraphic
{

public:
  RenderGraphic(GenieGraphic data, sf::RenderTarget *render_target);
  RenderGraphic(const RenderGraphic& other);
  virtual ~RenderGraphic();
  virtual RenderGraphic& operator=(const RenderGraphic& other);

  //TODO: direction

  //----------------------------------------------------------------------------
  /// Sets X position of the hotspot.
  ///
  /// @param x x pos
  //
  void setX(float x);

  //----------------------------------------------------------------------------
  /// Sets Y position of the hotspot.
  ///
  /// @param y y pos
  //
  void setY(float y);
  
  void update();

  void draw();

private:
  GenieGraphic data_;
  SlpFile *slp_file_;

  float x_, y_;

  sf::RenderTarget *render_target_;
  sf::Sprite sprite_;
  //sf::Texture textr_;

  unsigned int current_frame_;
  float time_last_frame_;
};

#endif // RENDERGRAPHIC_H
