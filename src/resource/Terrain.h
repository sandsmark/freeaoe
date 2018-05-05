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

#include "Resource.h"
#include <SFML/Graphics/Texture.hpp>
#include <genie/dat/Terrain.h>
#include <global/Logger.h>

#include <genie/resource/SlpFile.h>

#include <unordered_map>

class SlpFile;

namespace res {

class Terrain;
typedef std::shared_ptr<Terrain> TerrainPtr;

struct TileSlopes
{
    enum Slope {
        Flat = 0,
        SouthUp = 1,
        NorthUp     = 2,
        WestUp      = 3,
        EastUp      = 4,
        SouthWestUp = 5,
        NorthWestUp = 6,
        SouthEastUp = 7,
        NorthEastUp = 8,

        NorthDown   = 13,
        SouthDown   = 14,
        WestDown    = 15,
        EastDown    = 16,

        SouthWestEastUp,
        NorthWestEastUp,

        NorthSouthEastUp,
        NorthSouthWestUp,
    };
    Slope self = Flat;

    Slope north = Flat;
    Slope south = Flat;

    Slope west = Flat;
    Slope east = Flat;

    Slope southWest = Flat;
    Slope southEast = Flat;

    Slope northWest = Flat;
    Slope northEast = Flat;

    static genie::Slope genieSlope(const Slope s) {
        if (s < SouthWestEastUp) {
            return genie::Slope(s);
        }

        switch (s) {
        case SouthWestEastUp:
            return genie::SlopeSouthWestEastUp;
        case NorthWestEastUp:
            return genie::SlopeNorthWestEastUp;
        case NorthSouthEastUp:
            return genie::SlopeWestDown;
        case NorthSouthWestUp:
            return genie::SlopeEastDown;
        default:
            return genie::SlopeInvalid;
        }
    }
    bool operator==(const TileSlopes &other) const {
        return self == other.self &&
               north == other.north &&
               south == other.south &&
               west == other.west &&
               east == other.east &&
               southWest == other.southWest &&
               southEast == other.southEast &&
               northWest == other.northWest &&
               northEast == other.northEast;
    }
};

struct Blend  {
    enum BlendTile {
        LowerLeft1 = 0,
        UpperLeft1 = 4,
        LowerRight1 = 8,
        UpperRight1 = 12,

        Right = 16,
        Down = 17,
        Up = 18,
        Left = 19,

        UpperRightAndLowerLeft = 20,
        UpperLeftAndLowerRight = 21,

        OnlyRight = 22,
        OnlyDown = 23,
        OnlyUp = 24,
        OnlyLeft = 25,

        KeepUpperLeft = 26,
        KeepUpperRight = 27,
        KeepLowerRight = 28,
        KeepLowerLeft = 29,

        All = 30,

        BlendTileCount
    };

    inline void addBlend(const BlendTile blend)
    {
        bits |= 1 << blend;
    }

    inline bool operator ==(const Blend other) const { return bits == other.bits; }

    uint32_t bits = 0;
    uint8_t blendMode = 0;
};
}

namespace std {

template<> struct hash<res::TileSlopes>
{
    size_t operator()(const res::TileSlopes s) const {
        return hash<int8_t>()(s.self) ^
               hash<int8_t>()(s.north) ^
               hash<int8_t>()(s.south) ^
               hash<int8_t>()(s.west) ^
               hash<int8_t>()(s.east) ^
               hash<int8_t>()(s.southWest) ^
               hash<int8_t>()(s.southEast) ^
               hash<int8_t>()(s.northWest) ^
               hash<int8_t>()(s.northEast);
    }
};

template<> struct hash<res::Blend>
{
    size_t operator()(const res::Blend b) const {
        return hash<uint32_t>()(b.bits) ^ hash<uint8_t>()(b.blendMode);
    }
};
}

namespace res {
class Terrain : public Resource
{
public:
    enum Slope {
        Flat = 0x0,
        North = 0x1,
        East = 0x2,
        West = 0x4,
        South = 0x8
    };

    //----------------------------------------------------------------------------
    /// @param Id resource id
    //
    Terrain(unsigned int Id);
    virtual ~Terrain();

    const sf::Texture &texture(int x, int y);
    const sf::Image image(int x, int y);

    virtual bool load();

    const genie::Terrain &data();

    static uint8_t blendMode(const uint8_t ownMode, const uint8_t neighborMode);
    const sf::Texture &blendImage(const Blend blends, int tileX, int tileY);

    const sf::Texture &slopedImage(const TileSlopes &slopes, int tileX, int tileY);

private:
    static Logger &log;

    genie::Terrain m_data;
    genie::SlpFilePtr m_slp;

    std::unordered_map<int, sf::Texture> m_images; // TODO Frames?
    std::unordered_map<Blend, sf::Texture> m_blendImages;
    std::unordered_map<TileSlopes, sf::Texture> m_slopeImages;
};

}

#endif // FREEAOE_TERRAIN_H
