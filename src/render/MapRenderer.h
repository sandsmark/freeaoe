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

#ifndef MAP_RENDERER_H
#define MAP_RENDERER_H

#include "IRenderer.h"
#include "mechanics/Map.h"
#include "render/SfmlRenderTarget.h"

class MapRenderer : public IRenderer
{

public:
    MapRenderer();
    virtual ~MapRenderer();

    bool update(Time time) override;

    void display(void) override;

    void setMap(MapPtr map);

private:
    void updateTexture();

    MapPos m_lastCameraPos;
    bool m_camChanged;

    MapPtr m_map;

    int m_xOffset, m_yOffset; //TODO: ScreenPos?
    int m_rRowBegin, m_rRowEnd;
    int m_rColBegin, m_rColEnd;

    sf::RenderTexture m_mapRenderTexture;
    SfmlRenderTarget m_textureTarget;

    sf::Image m_mapImage;

    const int m_elevationHeight;
};

typedef std::shared_ptr<MapRenderer> MapRendererPtr;

#endif // MAP_RENDERER_H
