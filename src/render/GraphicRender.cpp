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

bool GraphicRender::update(Time time)
{
    int newFrame = current_frame_;

    if (time_last_frame_ == 0) {
        time_last_frame_ = time;
        newFrame = 0;
    } else {
        Time elapsed = time - time_last_frame_;
        float framerate = 10;
        if (map_object_->moving_ && m_movingGraphic) {
           framerate = m_movingGraphic->getFrameRate();
        } else {
           framerate = graphic_->getFrameRate();
        }

        if (elapsed > framerate / 0.0015) {
            if (newFrame < graphic_->getFrameCount() - 1) {
                newFrame++;
            } else {
                newFrame = 0;
            }

            time_last_frame_ = time;
        }
    }

    bool updated = false;
    if (newFrame != current_frame_) {
        updated = true;
    }

    current_frame_ = newFrame;

    return updated;
}

void GraphicRender::drawOn(IRenderTarget &renderer)
{
    screen_pos_ = renderer.absoluteScreenPos(map_object_->getPos());

    //, map_object_->angle_
    if (map_object_->moving_ && m_movingGraphic) {
        renderer.draw(m_movingGraphic, screen_pos_, current_frame_, map_object_->angle_);
    } else {
        renderer.draw(graphic_, screen_pos_, current_frame_, map_object_->angle_);
    }
}

sf::Image GraphicRender::image()
{
    if (!graphic_) {
        return sf::Image();
    }
    if (!map_object_) {
        return sf::Image();
    }

    if (map_object_->moving_ && m_movingGraphic) {
        return m_movingGraphic->getImage(current_frame_, map_object_->angle_);
    } else {
        return graphic_->getImage(current_frame_, map_object_->angle_);
    }
}

sf::Image GraphicRender::overlay()
{
    if (!graphic_) {
        return sf::Image();
    }
    if (!map_object_) {
        return sf::Image();
    }

    if (map_object_->moving_ && m_movingGraphic) {
        return m_movingGraphic->overlayImage(current_frame_, map_object_->angle_, 2);
    } else {
        return graphic_->overlayImage(current_frame_, map_object_->angle_, 2);
    }
}

void GraphicRender::setMapObject(MapObjectPtr map_object)
{
    map_object_ = map_object;
}

void GraphicRender::setMovingGraphic(unsigned graphic_id)
{
    m_movingGraphic = ResourceManager::Inst()->getGraphic(graphic_id);
}

GraphicPtr GraphicRender::create(unsigned int graphic_id)
{
    comp::GraphicPtr ptr(new comp::GraphicRender());

    ptr->graphic_ = ResourceManager::Inst()->getGraphic(graphic_id);
    ptr->screen_pos_ = ScreenPos(100, 100);

    return ptr;
}
}
