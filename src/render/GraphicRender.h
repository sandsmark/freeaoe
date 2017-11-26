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
#include <mechanics/CompMapObject.h>
#include "IRenderableComponent.h"

namespace comp {

const std::string GRAPHIC_RENDER("comp_graphic");

class GraphicRender;

typedef std::shared_ptr<GraphicRender> GraphicPtr;

/// Draws and manages Graphics for EntityForm objects.
class GraphicRender : public IRenderableComponent
{

public:
    GraphicRender();
    virtual ~GraphicRender();

    virtual void update(Time time);

    virtual void drawOn(IRenderTarget &renderer);

    void setGraphic(res::GraphicPtr graphic);

    void setMapObject(MapObjectPtr map_object);

    static comp::GraphicPtr create(unsigned int graphic_id);

private:
    res::GraphicPtr graphic_;

    MapObjectPtr map_object_;

    ScreenPos screen_pos_;

    unsigned int current_frame_;
    Time time_last_frame_;

    bool replay_delay_;

    uint16_t current_angle_;
    unsigned int angle_diff_;

    bool mirror_frame_;
};
}

#endif // GRAPHIC_RENDER_H
