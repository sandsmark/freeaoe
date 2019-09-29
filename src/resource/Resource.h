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

#include <SFML/Graphics/Image.hpp>

#include <memory>

namespace genie {
class PalFile;
class SlpFrame;
using SlpFramePtr = std::shared_ptr<SlpFrame>;
}

namespace genie {
class PalFile;
}  // namespace genie

//------------------------------------------------------------------------------
/// Resource is the basic class of resources managed by the AssetManager.
//
class Resource
{

public:
    static sf::Image convertFrameToImage(const genie::SlpFramePtr &frame);
    static sf::Image convertFrameToImage(const genie::SlpFramePtr &frame, const genie::PalFile &palette,
                                         const int playerId = -1);
};

