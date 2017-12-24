/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

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

#ifndef FREEAOE_TERRAIN_H
#define FREEAOE_TERRAIN_H

//#include "Resource.h"
#include "ResourcePtr.h"
#include <SFML/Graphics/Texture.hpp>
#include <genie/dat/Terrain.h>
#include <global/Logger.h>

#include <genie/resource/SlpFile.h>

#include <unordered_map>

class SlpFile;

namespace res {

class Terrain : public Resource
{
public:
    //----------------------------------------------------------------------------
    /// @param Id resource id
    //
    Terrain(unsigned int Id);
    virtual ~Terrain();

    const sf::Texture &image(int x, int y);

    virtual bool load();

private:
    static Logger &log;

    genie::Terrain m_data;
    genie::SlpFilePtr m_slp;

    std::unordered_map<int, sf::Texture> m_images; // TODO Frames?
};

typedef ResourcePtr<Terrain> TerrainPtr;
}

#endif // FREEAOE_TERRAIN_H
