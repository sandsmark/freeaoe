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

#include <genie/resource/Slope.h>
#include <genie/resource/TileSpan.h>
#include <memory>
#include <unordered_map>

#include "IRenderer.h"
#include "core/Types.h"
#include "mechanics/Map.h"
#include "render/IRenderTarget.h"

namespace sf {
class Texture;
}  // namespace sf
struct VisibilityMap;

class MapRenderer : public IRenderer
{

public:
    MapRenderer();
    virtual ~MapRenderer();

    bool update(Time time) override;

    void display() override;

    void setMap(const MapPtr &map);
    void setVisibilityMap(const std::shared_ptr<VisibilityMap> &visibilityMap);

    int firstVisibleRow() { return m_rRowBegin; }
    int lastVisibleRow() { return m_rRowEnd; }
    int firstVisibleColumn() { return m_rColBegin; }
    int lastVisibleColumn() { return m_rColEnd; }

private:
    void updateTexture();

    Drawable::Image::Ptr drawTileSpans(const std::vector<genie::TileSpan> &tileSpans, const uint32_t color) const;
    Drawable::Image::Ptr shadowMask(const genie::Slope slope, const int edges);
    Drawable::Image::Ptr unexploredMask(const genie::Slope slope, const int edges);

    MapPos m_lastCameraPos;
    bool m_camChanged;
    std::shared_ptr<VisibilityMap> m_visibilityMap;

    MapPtr m_map;

    int m_xOffset, m_yOffset; //TODO: ScreenPos?
    int m_rRowBegin, m_rRowEnd;
    int m_rColBegin, m_rColEnd;

    std::unordered_map<int, sf::Texture> m_shadowCaches;
    std::unordered_map<int, sf::Texture> m_unexploredMaskCache;

    IRenderTargetPtr m_textureTarget;

    const int m_elevationHeight;
};

typedef std::shared_ptr<MapRenderer> MapRendererPtr;

