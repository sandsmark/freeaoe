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

#include "mechanics/IState.h"
#include "mechanics/Player.h"

class ISampleGame
{
public:
    virtual ~ISampleGame() {}
    virtual void setupMap() = 0;
    virtual void setupActors(const std::vector<Civilization::Ptr> &civilizations, const ResourceMap &startingResources) = 0;
    virtual Player::Ptr getGaiaPlayer() = 0;
    virtual Player::Ptr getHumanPlayer() = 0;
    virtual Player::Ptr getEnemyPlayer() = 0;
};
