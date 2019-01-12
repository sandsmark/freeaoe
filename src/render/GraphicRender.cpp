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

#include <resource/AssetManager.h>
#include <resource/DataManager.h>
#include <SFML/Graphics/Sprite.hpp>
#include "IRenderTarget.h"

#include "MapRenderer.h"
#include "mechanics/Entity.h"

const sf::Texture GraphicRender::nullImage;

GraphicRender::GraphicRender()
{
    m_currentFrame = 0;
    m_lastFrameTime = 0;
}

GraphicRender::~GraphicRender()
{
}

bool GraphicRender::update(Time time)
{
    bool updated = false;
    for (GraphicDelta &delta : m_deltas) {
        if (delta.angleToDrawOn >= 0 && delta.graphic->m_graphic->angleToOrientation(m_angle) != delta.angleToDrawOn) {
            continue;
        }
        updated = delta.graphic->update(time) || updated;
    }

    if (!m_graphic) {
        return updated;
    }
    if (!m_graphic->getFrameRate()) {
        return updated;
    }

    if (m_graphic->runOnce() && m_currentFrame >= m_graphic->frameCount() - 1) {
        return updated;
    }

    int newFrame = m_currentFrame;

    Time elapsed = time - m_lastFrameTime;

    if (newFrame >= m_graphic->frameCount() - 1 && elapsed < m_graphic->replayDelay() / 0.0015) {
        return updated;
    }

    if (m_lastFrameTime == 0) {
        m_lastFrameTime = time;
        newFrame = 0;
    } else {
        float framerate = m_graphic->getFrameRate();

        if (elapsed > framerate / 0.0015) {
            if (newFrame < m_graphic->frameCount() - 1) {
                newFrame++;
            } else {
                newFrame = 0;
            }

            m_lastFrameTime = time;
        }
    }

    if (newFrame != m_currentFrame) {
        updated = true;
    }

    m_currentFrame = newFrame;

    return updated;
}

void GraphicRender::render(sf::RenderTarget &renderTarget, const ScreenPos screenPos, const RenderType renderpass)
{
    for (const GraphicDelta &delta : m_deltas) {
        if (delta.angleToDrawOn >= 0 && delta.graphic->m_graphic->angleToOrientation(m_angle) != delta.angleToDrawOn) {
            continue;
        }

        delta.graphic->render(renderTarget, screenPos + delta.offset, renderpass);
    }

    if (m_graphic && m_graphic->isValid()) {
        sf::Sprite sprite;
        sf::BlendMode blendMode;

        switch(renderpass) {
        case RenderType::Base:
            sprite.setTexture(m_graphic->texture(m_currentFrame, m_angle, m_playerId, ImageType::Base));
            break;
        case RenderType::BuildingAlpha:
            sprite.setTexture(m_graphic->texture(m_currentFrame, m_angle, m_playerId, ImageType::Base));
            blendMode = sf::BlendAlpha;
            blendMode.alphaSrcFactor = sf::BlendMode::SrcAlpha;
            blendMode.colorDstFactor = sf::BlendMode::DstColor;
            blendMode.colorSrcFactor = sf::BlendMode::DstColor;
            break;
        case RenderType::Outline:
            sprite.setTexture(m_graphic->texture(m_currentFrame, m_angle, m_playerId, ImageType::Outline));
            blendMode = sf::BlendAlpha;
            blendMode.alphaSrcFactor = sf::BlendMode::DstAlpha;
            break;
        case RenderType::ConstructAvailable:
            sprite.setTexture(m_graphic->texture(m_currentFrame, m_angle, m_playerId, ImageType::Construction));
            break;
        case RenderType::Shadow:
            sprite.setTexture(m_graphic->texture(m_currentFrame, m_angle, m_playerId, ImageType::Shadow));
            break;
        case RenderType::ConstructUnavailable:
            sprite.setTexture(m_graphic->texture(m_currentFrame, m_angle, m_playerId, ImageType::ConstructionUnavailable));
            break;
        }

        sprite.setPosition(screenPos - m_graphic->getHotspot(m_currentFrame, m_angle));
        renderTarget.draw(sprite, blendMode);
    }

}

bool GraphicRender::setGraphic(const GraphicPtr &graphic)
{
    m_graphic = graphic;
    m_currentFrame = 0;
    m_deltas.clear();

    if (!graphic) {
        WARN << "no graphic";
        return false;
    }

    for (const genie::GraphicDelta &deltaData : graphic->deltas()) {
        if (deltaData.GraphicID < 0) {
            continue;
        }

        GraphicDelta delta;
        delta.graphic = std::make_shared<GraphicRender>();

        // Don't use setGraphic, to avoid recursive adding of deltas
        delta.graphic->m_graphic =  AssetManager::Inst()->getGraphic(deltaData.GraphicID);
        if (!delta.graphic->m_graphic->isValid()) {
            continue;
        }
        delta.angleToDrawOn = deltaData.DisplayAngle;

        delta.offset = ScreenPos(deltaData.OffsetX, deltaData.OffsetY);

        m_deltas.push_back(delta);
    }
//    if (!m_deltas.empty()) {
//        std::reverse(m_deltas.begin(), m_deltas.end());
//    }
    return true;
}

ScreenRect GraphicRender::rect() const
{
    if (!m_graphic || !m_graphic->isValid()) {
        return ScreenRect();
    }

    ScreenRect ret;
    const ScreenPos hotspot = m_graphic->getHotspot(m_currentFrame, m_angle);
    ret.x = -hotspot.x;
    ret.y = -hotspot.y;
    const sf::Vector2u size = m_graphic->size(m_currentFrame, m_angle);
    ret.width = size.x;
    ret.height = size.y;

    for (const GraphicDelta &delta : m_deltas) {
        if (delta.angleToDrawOn >= 0 && delta.graphic->m_graphic->angleToOrientation(m_angle) != delta.angleToDrawOn) {
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

void GraphicRender::setCurrentFrame(int frame)
{
    if (frame == m_currentFrame) {
        return;
    }

    if (frame >= frameCount()) {
        frame = frameCount() - 1;
    }
    if (frame < 0) {
        frame = 0;
    }

    m_currentFrame = frame;
}
