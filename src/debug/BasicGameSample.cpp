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

#include "BasicGameSample.h"

#include "mechanics/UnitFactory.h"
#include "mechanics/UnitManager.h"

void BasicGameSample::setupMap()
{
    map_->setupBasic();
}

void BasicGameSample::setupActors(const ResourceMap &startingResources)
{
    m_gaiaPlayer = std::make_shared<Player>(UnitManager::GaiaID, 0, startingResources);
    m_humanPlayer = std::make_shared<Player>(1, 1, startingResources);
    m_enemyPlayer = std::make_shared<Player>(2, 2, startingResources);

    addHumanTownCenter();
    addHumanWalls();
    addHumanUnits();

    addEnemyUnits();
    addGaia();
}

Player::Ptr BasicGameSample::getGaiaPlayer()
{
    return m_gaiaPlayer;
}

Player::Ptr BasicGameSample::getHumanPlayer()
{
    return m_humanPlayer;
}

Player::Ptr BasicGameSample::getEnemyPlayer()
{
    return m_enemyPlayer;
}

void BasicGameSample::addHumanTownCenter()
{
    Unit::Ptr unit = UnitFactory::Inst().createUnit(Unit::TownCenter, MapPos(48*2, 48*2, 0), m_humanPlayer, *unitManager_);
    unitManager_->add(unit);
}

void BasicGameSample::addHumanWalls()
{
    Unit::Ptr unit;
    auto addWall = [&](int x, int y, float angle) {
        unit = UnitFactory::Inst().createUnit(Unit::StoneWall, MapPos(48*x, 48*y, 0), m_humanPlayer, *unitManager_);
        unitManager_->add(unit);
        unit->setAngle(angle);
    };

    addWall(4, 4, 0);
    unit->setAngle(unit->renderer().graphic()->orientationToAngle(0));
    addWall(5, 4, unit->renderer().graphic()->orientationToAngle(1));
    addWall(6, 4, unit->renderer().graphic()->orientationToAngle(2));
    addWall(7, 4, unit->renderer().graphic()->orientationToAngle(3));
    addWall(8, 4, unit->renderer().graphic()->orientationToAngle(4));
    addWall(9, 4, unit->renderer().graphic()->orientationToAngle(5));
}

void BasicGameSample::addHumanUnits()
{
    Unit::Ptr unit;

    unit = UnitFactory::Inst().createUnit(Unit::MaleBuilder, MapPos(48*2, 48*12, 0), m_humanPlayer, *unitManager_);
    unitManager_->add(unit);

    unit = UnitFactory::Inst().createUnit(280, MapPos(48*11, 48*10, 0), m_humanPlayer, *unitManager_);
    unitManager_->add(unit);

    unit = UnitFactory::Inst().createUnit(279, MapPos(48*13, 48*11, 0), m_humanPlayer, *unitManager_);
    unitManager_->add(unit);

    unit = UnitFactory::Inst().createUnit(Unit::Mill, MapPos(48*15, 48*15, 0), m_humanPlayer, *unitManager_);
    unitManager_->add(unit);

    unit = UnitFactory::Inst().createUnit(827, MapPos(48*10, 48*9, 0), m_humanPlayer, *unitManager_);
    unitManager_->add(unit);

    unit = UnitFactory::Inst().createUnit(74, MapPos(48*8, 48*9, 0), m_humanPlayer, *unitManager_);
    unitManager_->add(unit);
}

void BasicGameSample::addEnemyUnits()
{
    Unit::Ptr unit = UnitFactory::Inst().createUnit(74, MapPos(48*8, 48*8, 0), m_enemyPlayer, *unitManager_);
    unitManager_->add(unit);
}

void BasicGameSample::addGaia()
{
    Unit::Ptr unit = UnitFactory::Inst().createUnit(399, MapPos(48 * 2, 48*19, 0), m_gaiaPlayer, *unitManager_); // tree
    m_humanPlayer->visibility->setExplored(1, 18);
    m_humanPlayer->visibility->setExplored(2, 18);
    m_humanPlayer->visibility->setExplored(1, 19);
    m_humanPlayer->visibility->setExplored(2, 19);
    unitManager_->add(unit);
}
