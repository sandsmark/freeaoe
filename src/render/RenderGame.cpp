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

#include "RenderGame.h"
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>
#include <mechanics/Unit.h>
#include <resource/ResourceManager.h>
#include <file/SlpFrame.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

RenderGame::RenderGame(sf::RenderTarget *render_target) :
            render_target_(render_target)
{

}

RenderGame::RenderGame(const RenderGame& other)
{

}

RenderGame::~RenderGame()
{

}

//------------------------------------------------------------------------------
void RenderGame::addUnit(Unit* unit)
{
  render_units_.push_back(new RenderUnit(unit, render_target_));
}

// TODO: layers, map
void RenderGame::draw()
{
  for( std::vector<RenderUnit *>::iterator it = render_units_.begin(); 
       it != render_units_.end(); it ++)
  {
    (*it)->update();
    (*it)->draw();
  }
  
  //test:
  sf::Texture text;
  text.LoadFromImage(*ResourceManager::Inst()->getSlp(15001)->getFrame(0)->getImage());
  
  sf::Sprite spr;
  spr.SetTexture(text);
  spr.SetPosition(100,100);
  render_target_->Draw(spr);
}

//------------------------------------------------------------------------------
std::vector<Unit *> RenderGame::getUnitsAt(sf::Uint32 x, sf::Uint32 y)
{
  std::vector<Unit *> units_at;
  
  for( std::vector<RenderUnit *>::iterator it = render_units_.begin(); 
       it != render_units_.end(); it ++)
  {
    if ((*it)->coversPos(x, y))
    {
      units_at.push_back((*it)->getUnit());
    }
  }
  
  return units_at;
}
