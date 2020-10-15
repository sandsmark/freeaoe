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

#include "core/Types.h"

#include <memory>

struct Player;
struct Unit;
struct DecayingEntity;
struct DopplegangerEntity;
class UnitManager;

struct Task;

class UnitFactory
{
public:
    static UnitFactory &Inst();

    static std::shared_ptr<Unit> duplicateUnit(const std::shared_ptr<Unit> &other);
    static std::shared_ptr<Unit> createUnit(const int ID, const std::shared_ptr<Player> &owner, UnitManager &unitManager);
    static std::shared_ptr<DecayingEntity> createCorpseFor(const std::shared_ptr<DopplegangerEntity> &unit);
    static std::shared_ptr<DecayingEntity> createCorpseFor(const std::shared_ptr<Unit> &unit);
    static std::shared_ptr<DopplegangerEntity> createDopplegangerFor(const std::shared_ptr<Unit> &unit);

private:
    UnitFactory() = default;

    static void handleDefaultAction(const std::shared_ptr<Unit> &unit, const Task &task);
};

