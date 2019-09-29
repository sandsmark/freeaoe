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

#include "SampleGameFactory.h"

#include "AllunitsGameSample.h"
#include "BasicGameSample.h"

class UnitManager;

SampleGameFactory &SampleGameFactory::Inst()
{
    static SampleGameFactory inst;
    return inst;
}

SampleGamePtr SampleGameFactory::createGameSetup(const std::shared_ptr<Map> &map, const std::shared_ptr<UnitManager> &unitManager)
{
    switch (gameSampleId) {
        case GameSampleId::AllUnitsGameSample:
            return std::make_shared<AllunitsGameSample>(map, unitManager);
        case GameSampleId::BasicGameSample:
        default:
            return std::make_shared<BasicGameSample>(map, unitManager);
    }
}

void SampleGameFactory::setSampleFromAlias(const std::string &alias)
{
    if (std::string("basic") == alias) {
        this->gameSampleId = GameSampleId::BasicGameSample;
    } else  if (std::string("all") == alias) {
        this->gameSampleId = GameSampleId::AllUnitsGameSample;
    }
}

