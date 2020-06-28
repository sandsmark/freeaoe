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

#include <functional>

#include "core/Types.h"
#include "mechanics/Unit.h"
#include "mechanics/UnitFactory.h"
#include "mechanics/UnitManager.h"
#include "render/GraphicRender.h"
#include "resource/Sprite.h"
#include "render/Camera.h"

void BasicGameSample::setupMap()
{
    map_->setupBasic();
}

void BasicGameSample::setupActors(const ResourceMap &startingResources)
{
    m_gaiaPlayer = std::make_shared<Player>(UnitManager::GaiaID, 0, startingResources);
    m_gaiaPlayer->playerColor = -1;
    m_humanPlayer = std::make_shared<Player>(1, 1, startingResources);
    m_humanPlayer->playerColor = 0;
    m_enemyPlayer = std::make_shared<Player>(2, 2, startingResources);
    m_enemyPlayer->playerColor = 1;

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
    Unit::Ptr unit = UnitFactory::Inst().createUnit(Unit::TownCenter, m_humanPlayer, *unitManager_);
    unitManager_->add(unit, MapPos(48*2, 48*2, 0));
}

void BasicGameSample::addHumanWalls()
{
    Unit::Ptr unit;
    std::function<void(int, int, float)> addWall = [&](int x, int y, float angle) {
        unit = UnitFactory::Inst().createUnit(Unit::PalisadeWall, m_humanPlayer, *unitManager_);
        unitManager_->add(unit, MapPos(48*x, 48*y, 0));
        unit->setAngle(angle);
    };

//    addWall(4, 4, 0);
//    unit->setAngle(unit->renderer().sprite()->orientationToAngle(0));
//    addWall(5, 4, unit->renderer().sprite()->orientationToAngle(1));
//    addWall(6, 4, unit->renderer().sprite()->orientationToAngle(2));
//    addWall(7, 4, unit->renderer().sprite()->orientationToAngle(3));
//    addWall(8, 4, unit->renderer().sprite()->orientationToAngle(4));
//    addWall(9, 4, unit->renderer().sprite()->orientationToAngle(5));
}

void BasicGameSample::addHumanUnits()
{
    Unit::Ptr unit;

    unit = UnitFactory::Inst().createUnit(Unit::MaleBuilder, m_humanPlayer, *unitManager_);
    unitManager_->add(unit, MapPos(48*2, 48*12, 0));

    // mangonel
//    unit = UnitFactory::Inst().createUnit(280, m_humanPlayer, *unitManager_);
//    unitManager_->add(unit, MapPos(48*9, 48*8, 0));

    // scorpion
//    unit = UnitFactory::Inst().createUnit(279, m_humanPlayer, *unitManager_);
//    unitManager_->add(unit, MapPos(48*13, 48*11, 0));

    unit = UnitFactory::Inst().createUnit(Unit::Archer, m_humanPlayer, *unitManager_);
    unitManager_->add(unit, MapPos(48*15, 48*15, 0));

//    unit = UnitFactory::Inst().createUnit(Unit::ArcheryRange, m_humanPlayer, *unitManager_);
//    unitManager_->add(unit, MapPos(48 * 10, 48 * 5, 0));

//    unit = UnitFactory::Inst().createUnit(827, MapPos(48*10, 48*9, 0), m_humanPlayer, *unitManager_);
//    unitManager_->add(unit);

//    unit = UnitFactory::Inst().createUnit(74, m_humanPlayer, *unitManager_);
//    unitManager_->add(unit, MapPos(48*8, 48*10, 0));
}

void BasicGameSample::addEnemyUnits()
{
    Unit::Ptr unit;
    unit = UnitFactory::Inst().createUnit(74, m_enemyPlayer, *unitManager_);
    unitManager_->add(unit, MapPos(48*5, 48*5, 0));

    unit = UnitFactory::Inst().createUnit(Unit::PalisadeWall, m_enemyPlayer, *unitManager_);
    unitManager_->add(unit, MapPos(48*10, 48*15, 0));
    unit->setAngle(unit->renderer().sprite()->orientationToAngle(0));
}

void BasicGameSample::addGaia()
{
    Unit::Ptr unit = UnitFactory::Inst().createUnit(399, m_gaiaPlayer, *unitManager_); // tree
    m_humanPlayer->visibility->setExplored(1, 18);
    m_humanPlayer->visibility->setExplored(2, 18);
    m_humanPlayer->visibility->setExplored(1, 19);
    m_humanPlayer->visibility->setExplored(2, 19);
    unitManager_->add(unit, MapPos(48 * 2, 48*19, 0));
}
