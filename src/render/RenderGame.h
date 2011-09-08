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


#ifndef RENDERGAME_H
#define RENDERGAME_H
#include <vector>
#include "RenderUnit.h"
#include <SFML/Config.hpp>

class Unit;
class RenderGame
{

public:
  RenderGame(sf::RenderTarget *render_target);
  virtual ~RenderGame();
  
  //----------------------------------------------------------------------------
  /// Adds a unit that needs to be rendered.
  //
  void addUnit(Unit *unit);
  
  //----------------------------------------------------------------------------
  void draw();
  
  //----------------------------------------------------------------------------
  /// Returns a list of units at given point on the screen
  /// 
  /// @param x x position on screen
  /// @param y y position on screen
  /// @return Units on given position
  //
  std::vector<Unit *> getUnitsAt(sf::Uint32 x, sf::Uint32 y);
    
private:
  RenderGame(const RenderGame& other);
  
  sf::RenderTarget *render_target_;
  
  std::vector<RenderUnit *> render_units_;
};

#endif // RENDERGAME_H
