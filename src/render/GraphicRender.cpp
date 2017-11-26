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

#include "GraphicRender.h"

#include <resource/ResourceManager.h>
#include <resource/DataManager.h>
#include <mechanics/CompMapObject.h>
#include "IRenderTarget.h"

#include "MapRenderer.h"

namespace comp {

GraphicRender::GraphicRender() :
    screen_pos_(0, 0)
{
    current_frame_ = 0;
    time_last_frame_ = 0;
    current_angle_ = 0;
    angle_diff_ = 0;
    mirror_frame_ = false;
    replay_delay_ = false;
}

GraphicRender::~GraphicRender()
{
}

void GraphicRender::update(Time time)
{

    if (time_last_frame_ == 0) {
        time_last_frame_ = time;
        current_frame_ = 0;
    } else {
        Time frame_rate = graphic_->getFrameRate() * 1000;

        if (replay_delay_)
            frame_rate += replay_delay_ * 1000;

        if ((time - time_last_frame_) > frame_rate) {
            if (current_frame_ < graphic_->getFrameCount() - 1) {
                current_frame_++;
                replay_delay_ = false;
            } else {
                current_frame_ = 0;
                replay_delay_ = true;
            }

            time_last_frame_ = time;
        }
    }
}

void GraphicRender::drawOn(IRenderTarget &renderer)
{

    screen_pos_ = MapRenderer::mapToScreenPos(map_object_->getPos());

    renderer.draw(graphic_, screen_pos_, current_frame_);
}

void GraphicRender::setMapObject(MapObjectPtr map_object)
{
    map_object_ = map_object;
}

GraphicPtr GraphicRender::create(unsigned int graphic_id)
{
    comp::GraphicPtr ptr(new comp::GraphicRender());

    ptr->graphic_ = ResourceManager::Inst()->getGraphic(graphic_id);
    ptr->screen_pos_ = ScreenPos(100, 100);

    return ptr;
}
}
