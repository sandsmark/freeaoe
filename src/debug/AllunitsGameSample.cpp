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

#include "AllunitsGameSample.h"

#include "mechanics/UnitFactory.h"

void AllunitsGameSample::setupMap()
{
    map_->setupAllunitsMap();
}

void AllunitsGameSample::setupActors(const std::vector<Civilization::Ptr> &civilizations, const ResourceMap &startingResources)
{
    m_humanPlayer = std::make_shared<Player>(0, civilizations[1], startingResources);
    m_enemyPlayer = std::make_shared<Player>(1, civilizations[2], startingResources);

    addHumanTownCenter();
    addHumanUnits();
    addEnemyBuildings();
    addEnemyUnits();
}

Player::Ptr AllunitsGameSample::getHumanPlayer()
{
    return m_humanPlayer;
}

Player::Ptr AllunitsGameSample::getEnemyPlayer()
{
    return m_enemyPlayer;
}

void AllunitsGameSample::addHumanTownCenter()
{
    Unit::Ptr unit = UnitFactory::Inst().createUnit(Unit::TownCenter, MapPos(48*2, 48*2, 0), m_humanPlayer, *unitManager_);
    unitManager_->add(unit);
}

void AllunitsGameSample::addHumanUnits()
{
    const int dx = 115;
    const int dy = 115;
    const int baseX = dx * 2;
    const int baseY = dy * 3;

    std::vector<int> units{4, 7, 74, 280, 279, 358, 440, 725, 751, 765};

    int pos = 0;

    for (int i = 0; i< units.size(); i++)
    {
        int unitID = units.at(i);

        int x = (pos % 5) * dx + baseX;
        int y = (pos / 5) * dy + baseY;

        WARN << "::::: createUnit" << unitID;
        Unit::Ptr unit = UnitFactory::Inst().createUnit(unitID, MapPos(x, y, 0), m_humanPlayer, *unitManager_);
        unitManager_->add(unit);

        pos++;
    }
}

void AllunitsGameSample::addEnemyUnits()
{
    Unit::Ptr unit;

    unit = UnitFactory::Inst().createUnit(74, MapPos(48*12, 48*20, 0), m_enemyPlayer, *unitManager_);
    unitManager_->add(unit);
    unit = UnitFactory::Inst().createUnit(74, MapPos(48*11, 48*20, 0), m_enemyPlayer, *unitManager_);
    unitManager_->add(unit);

    unit = UnitFactory::Inst().createUnit(358, MapPos(48*9, 48*20, 0), m_enemyPlayer, *unitManager_);
    unitManager_->add(unit);
}

void AllunitsGameSample::addEnemyBuildings()
{
    Unit::Ptr unit = UnitFactory::Inst().createUnit(Unit::Dock, MapPos(48*15, 48*20, 0), m_enemyPlayer, *unitManager_);
    unitManager_->add(unit);
}
