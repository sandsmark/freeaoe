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
#include <SFML/Graphics/Sprite.hpp>
#include "IRenderTarget.h"

#include "MapRenderer.h"
#include "core/Entity.h"

namespace comp {

const sf::Texture GraphicRender::nullImage;

GraphicRender::GraphicRender()
{
    current_frame_ = 0;
    time_last_frame_ = 0;
}

GraphicRender::~GraphicRender()
{
}

bool GraphicRender::update(Time time)
{
    bool updated = false;
    for (GraphicDelta &delta : m_deltas) {
        if (delta.angleToDrawOn >= 0 && delta.graphic->graphic_->angleToOrientation(m_angle) != delta.angleToDrawOn) {
            continue;
        }
        updated = delta.graphic->update(time) || updated;
    }

    if (!graphic_) {
        return updated;
    }
    if (!graphic_->getFrameRate()) {
        return updated;
    }

    if (graphic_->runOnce() && current_frame_ >= graphic_->data_.FrameCount - 1) {
        return updated;
    }

    int newFrame = current_frame_;

    Time elapsed = time - time_last_frame_;


    if (newFrame >= graphic_->data_.FrameCount - 1 && elapsed < graphic_->data_.ReplayDelay / 0.0015) {
        return updated;
    }

    if (time_last_frame_ == 0) {
        time_last_frame_ = time;
        newFrame = 0;
    } else {
        float framerate = graphic_->getFrameRate();

        if (elapsed > framerate / 0.0015) {
            if (newFrame < graphic_->data_.FrameCount - 1) {
                newFrame++;
            } else {
                newFrame = 0;
            }

            time_last_frame_ = time;
        }
    }

    if (newFrame != current_frame_) {
        updated = true;
    }

    current_frame_ = newFrame;

    return updated;
}

void GraphicRender::render(sf::RenderTarget &renderTarget, const ScreenPos screenPos, const RenderType renderpass)
{
    for (const GraphicDelta &delta : m_deltas) {
        if (delta.angleToDrawOn >= 0 && delta.graphic->graphic_->angleToOrientation(m_angle) != delta.angleToDrawOn) {
            continue;
        }

        delta.graphic->render(renderTarget, screenPos + delta.offset, renderpass);
    }

    if (graphic_ && graphic_->isValid()) {
        sf::Sprite sprite;
        sf::BlendMode blendMode;

        switch(renderpass) {
        case RenderType::Base:
            sprite.setTexture(graphic_->texture(current_frame_, m_angle, m_playerId, res::ImageType::Base));
            break;
        case RenderType::Outline:
            sprite.setTexture(graphic_->texture(current_frame_, m_angle, m_playerId, res::ImageType::Outline));
            blendMode = sf::BlendAlpha;
            blendMode.alphaSrcFactor = sf::BlendMode::DstAlpha;
            break;
        case RenderType::ConstructAvailable:
            sprite.setTexture(graphic_->texture(current_frame_, m_angle, m_playerId, res::ImageType::Construction));
            break;
        case RenderType::Shadow:
        case RenderType::ConstructUnavailable:
            break;
        }

        sprite.setPosition(screenPos - graphic_->getHotspot(current_frame_, m_angle));
        renderTarget.draw(sprite, blendMode);
    }

}

void GraphicRender::setGraphic(res::GraphicPtr graphic)
{
    graphic_ = graphic;
    current_frame_ = 0;
    m_deltas.clear();

    if (!graphic) {
        return;
    }

    for (const genie::GraphicDelta &deltaData : graphic->deltas()) {
        if (deltaData.GraphicID < 0) {
            continue;
        }

        GraphicDelta delta;
        delta.graphic = std::make_shared<GraphicRender>();

        // Don't use setGraphic, to avoid recursive adding of deltas
        delta.graphic->graphic_ =  ResourceManager::Inst()->getGraphic(deltaData.GraphicID);
        if (!delta.graphic->graphic_->isValid()) {
            continue;
        }
        delta.angleToDrawOn = deltaData.DisplayAngle;

        delta.offset = ScreenPos(deltaData.OffsetX, deltaData.OffsetY);

        m_deltas.push_back(delta);
    }
//    if (!m_deltas.empty()) {
//        std::reverse(m_deltas.begin(), m_deltas.end());
//    }
}

ScreenRect GraphicRender::rect() const
{
    ScreenRect ret;
    const ScreenPos hotspot = graphic_->getHotspot(current_frame_, m_angle);
    ret.x = -hotspot.x;
    ret.y = -hotspot.y;
    const sf::Vector2u size = graphic_->size(current_frame_, m_angle);
    ret.width = size.x;
    ret.height = size.y;

    for (const GraphicDelta &delta : m_deltas) {
        if (delta.angleToDrawOn >= 0 && delta.graphic->graphic_->angleToOrientation(m_angle) != delta.angleToDrawOn) {
            continue;
        }

        ret += (delta.graphic->rect() + delta.offset);
    }

    return ret;
}

void GraphicRender::setAngle(float angle)
{
    m_angle = angle;

    for (GraphicDelta &delta : m_deltas) {
        delta.graphic->setAngle(angle);
    }
}

}
