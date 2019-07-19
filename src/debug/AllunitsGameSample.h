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
#include "mechanics/GameState.h"
#include "ISampleGame.h"

class AllunitsGameSample : public ISampleGame
{
public:
    AllunitsGameSample(const MapPtr &map, const std::shared_ptr<UnitManager> &unitManager)
        : map_(map),  unitManager_(unitManager) {}

    void setupMap() override;
    void setupActors(const ResourceMap &startingResources) override;

    Player::Ptr getGaiaPlayer() override;
    Player::Ptr getHumanPlayer() override;
    Player::Ptr getEnemyPlayer() override;

private:
    void addHumanTownCenter();
    void addHumanWalls();
    void addHumanUnits();
    void addEnemyUnits();
    void addEnemyBuildings();

    MapPtr map_;
    std::shared_ptr<UnitManager> unitManager_;
    Player::Ptr m_gaiaPlayer;
    Player::Ptr m_humanPlayer;
    Player::Ptr m_enemyPlayer;
};
