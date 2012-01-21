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

#include <global/Types.h>
#include <geniedat/Graphic.h>
#include <global/Logger.h>
#include <resource/Graphic.h>

class SlpFile;

//TODO: Obsolete!
class RenderGraphic
{

public:
  RenderGraphic(Uint32 graph_id, sf::RenderTarget *render_target);
  virtual ~RenderGraphic();

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
  
  void setPos(ScreenPos pos);
  
  //----------------------------------------------------------------------------
  /// Sets the angle of a unit, starting with 0 pointing to south and continues
  /// counter clockwise.
  //
  void setAngle(Uint32 angle);
  
  void update();

  void draw();
  
  //----------------------------------------------------------------------------
  /// Checks if current image covers given point.
  //
  bool coversPos(sf::Uint32 x, sf::Uint32 y);

private:
  static Logger &log;
  
  res::GraphicPtr graph_;
  
  ScreenPos pos_;

  sf::RenderTarget *render_target_;
  sf::Sprite sprite_;
  //sf::Texture textr_;

  Uint32 current_frame_;
  float time_last_frame_;
  
  Uint8 current_angle_;
  Uint32 angle_diff_;  
  
  bool mirror_frame_;
  
  Uint32 getCurrentFrame(void);
};

#endif // RENDERGRAPHIC_H
