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


#include "EntityFormManager.h"

EntityFormManager::EntityFormManager() 
{

}

EntityFormManager::~EntityFormManager()
{

}

void EntityFormManager::setGameRenderer(boost::shared_ptr< GameRenderer > renderer)
{
  game_renderer_ = renderer;
}

void EntityFormManager::add(EntityForm& form)
{
  forms_.push_back(form);
}

void EntityFormManager::draw()
{
  for (EFVector::iterator it = forms_.begin(); it != forms_.end(); it++)
    game_renderer_->draw(*it);
}
