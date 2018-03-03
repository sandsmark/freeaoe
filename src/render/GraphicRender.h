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

#ifndef GRAPHIC_RENDER_H
#define GRAPHIC_RENDER_H

#include <core/IComponent.h>
#include <resource/Graphic.h>
#include <resource/ResourceManager.h>
#include <SFML/Graphics/Texture.hpp>
#include "IRenderableComponent.h"

struct Entity;

namespace comp {

const std::string GRAPHIC_RENDER("comp_graphic");

class GraphicRender;


typedef std::shared_ptr<GraphicRender> GraphicPtr;

/// Draws and manages Graphics for EntityForm objects.
class GraphicRender
{
    static const sf::Texture nullImage;

public:
    GraphicRender();
    virtual ~GraphicRender();

    bool update(Time time);

    void drawOn(sf::RenderTarget &renderTarget, const ScreenPos screenPos);
    void drawOutlineOn(sf::RenderTarget &renderer, ScreenPos screenPos);

    const sf::Texture &image();
    const sf::Texture &outline();

    void setPlayerId(int playerId);

    void setGraphic(res::GraphicPtr graphic);

    ScreenRect rect();

    void setAngle(float angle);

    res::GraphicPtr graphic_;

    unsigned int current_frame_;

private:
    struct GraphicDelta {
        GraphicPtr graphic;
        ScreenPos offset;
    };

    Time time_last_frame_;
    std::vector<GraphicDelta> m_deltas;

    int m_playerId = 2;

    float m_angle = 0;
};
}

#endif // GRAPHIC_RENDER_H
