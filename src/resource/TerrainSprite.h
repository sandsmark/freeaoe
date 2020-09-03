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

#include "render/IRenderTarget.h"
#include "mechanics/MapTile.h"

#if PNG_TERRAIN_TEXTURES
#include <SFML/Graphics/Sprite.hpp>
#endif

#include <memory>
#include <string>
#include <unordered_map>

class TerrainSprite;
typedef std::shared_ptr<TerrainSprite> TerrainPtr;

namespace genie {
class SlpFile;
using SlpFilePtr = std::shared_ptr<SlpFile>;
}

#define PNG_TERRAIN_TEXTURES 1

class TerrainSprite
{
public:
    const int32_t id;
    //----------------------------------------------------------------------------
    /// @param Id resource id
    //
    TerrainSprite(unsigned int id_);
    ~TerrainSprite();

#if PNG_TERRAIN_TEXTURES
    inline int coordinatesToFrame(int x, int y) const noexcept {
        if (IS_UNLIKELY(!m_slp && !m_isPng)) {
            return -1;
        }
        if (m_isPng) {
            const int tileSquareCount = sqrt(4 * 4); // IDK, HD is fucked anyways
            return (y % tileSquareCount) + (x % tileSquareCount) * tileSquareCount;
        } else {
            const int tileSquareCount = m_tileSquareCount;
            return (y % tileSquareCount) + (x % tileSquareCount) * tileSquareCount;
        }
    }
    const Drawable::Image::Ptr &pngTexture(const MapTile &tile, const IRenderTargetPtr &renderer);

    const Drawable::Image::Ptr &texture(const MapTile &tile, const IRenderTargetPtr &renderer);
#else
    inline int coordinatesToFrame(int x, int y) const noexcept {
        return (y % m_tileSquareCount) + (x % m_tileSquareCount) * m_tileSquareCount;
    }

#endif

    bool isValid() const noexcept;

    size_t cacheSize() const { return m_textures.size(); }

private:
    void addOutline(uint32_t *pixels, const int width, const int height) noexcept;

    genie::SlpFilePtr m_slp;

    int m_tileSquareCount = 1;

    std::unordered_map<MapTile, Drawable::Image::Ptr> m_textures;

#if PNG_TERRAIN_TEXTURES
    bool m_isPng = false;
    std::string m_pngPath;
#endif
};

