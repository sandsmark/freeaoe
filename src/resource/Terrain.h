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

#pragma once

#include "Resource.h"
#include "mechanics/MapTile.h"
#include "core/Logger.h"

#include <SFML/Graphics/Texture.hpp>
#include <genie/dat/Terrain.h>

#include <genie/resource/SlpFile.h>

#include <unordered_map>

class SlpFile;

class Terrain;
typedef std::shared_ptr<Terrain> TerrainPtr;

class Terrain
{
public:
    const int32_t id;
    //----------------------------------------------------------------------------
    /// @param Id resource id
    //
    Terrain(unsigned int id_) : id(id_) { }
    virtual ~Terrain() = default;

    bool load() noexcept;

    const genie::Terrain &data() noexcept;

    static uint8_t blendMode(const uint8_t ownMode, const uint8_t neighborMode) noexcept;
    const sf::Texture &blendImage(const Blend blends, int tileX, int tileY) noexcept;

    const sf::Texture &slopedImage(const TileSlopes &slopes, const std::vector<genie::Pattern> &patterns, int tileX, int tileY) noexcept;

    uint32_t coordinatesToFrame(int x, int y) noexcept;

    const sf::Texture &texture(const MapTile &tile) noexcept;

private:
    void addOutline(sf::Image &img) noexcept;

    genie::Terrain m_data;
    genie::SlpFilePtr m_slp;

    std::unordered_map<int, sf::Texture> m_images; // TODO Frames?
    std::unordered_map<Blend, sf::Texture> m_blendImages;
    std::unordered_map<TileSlopes, sf::Texture> m_slopeImages;

    std::unordered_map<MapTile, sf::Texture> m_textures;

    bool m_isLoaded = false;
};

