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

#include "core/Utility.h"
#include "render/IRenderTarget.h"
#include "Resource.h"
#include "mechanics/MapTile.h"

#include <genie/dat/Terrain.h>
#include <genie/resource/SlpFile.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>
#include <unordered_map>

#include <math.h>
#include <stddef.h>
#include <stdint.h>

namespace sf {
class Texture;
}  // namespace sf
class TerrainSprite;
typedef std::shared_ptr<TerrainSprite> TerrainPtr;

class TerrainSprite
{
public:
    const int32_t id;
    //----------------------------------------------------------------------------
    /// @param Id resource id
    //
    TerrainSprite(unsigned int id_) : id(id_) { }
    virtual ~TerrainSprite();

    bool load() noexcept;

    const genie::Terrain &data() noexcept;

    static uint8_t blendMode(const uint8_t ownMode, const uint8_t neighborMode) noexcept;

    inline int coordinatesToFrame(int x, int y) noexcept {
        if (IS_UNLIKELY(!m_slp && !m_isPng)) {
            return -1;
        }
        if (m_isPng) {
            const int tileSquareCount = sqrt(4 * 4); // IDK, HD is fucked anyways
            return (y % tileSquareCount) + (x % tileSquareCount) * tileSquareCount;
        } else {
            const int tileSquareCount = sqrt(m_slp->getFrameCount());
            return (y % tileSquareCount) + (x % tileSquareCount) * tileSquareCount;
        }
    }

#if PNG_TERRAIN_TEXTURES
    sf::Sprite sprite(const MapTile &tile, const IRenderTargetPtr &renderer) noexcept;
#endif

    bool isValid() const noexcept;

    size_t cacheSize() const { return m_textures.size(); }

    const Drawable::Image::Ptr &texture(const MapTile &tile, const IRenderTargetPtr &renderer);

private:
    void addOutline(uint32_t *pixels, const int width, const int height) noexcept;

    genie::Terrain m_data;
    genie::SlpFilePtr m_slp;

    std::unordered_map<MapTile, Drawable::Image::Ptr> m_textures;

    bool m_isLoaded = false;

    bool m_isPng = false;
    std::string m_pngPath;
};

