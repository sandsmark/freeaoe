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
    if (!graphic_) {
        return false;
    }
    if (!graphic_->getFrameRate()) {
        return false;
    }

    if (graphic_->runOnce() && current_frame_ >= graphic_->getFrameCount() - 1) {
        return false;
    }

    int newFrame = current_frame_;

    if (time_last_frame_ == 0) {
        time_last_frame_ = time;
        newFrame = 0;
    } else {
        Time elapsed = time - time_last_frame_;
        float framerate = 10;
        framerate = graphic_->getFrameRate();

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

//    for (GraphicDelta &delta : m_deltas) {
//        updated = delta->update(time) || updated;
//    }

    return updated;
}

void GraphicRender::drawOn(sf::RenderTarget &renderTarget, const ScreenPos screenPos)
{
    if (!graphic_ || !graphic_->isValid()) {
        return;
    }

    sf::Sprite sprite;
    sprite.setTexture(image());
    sprite.setPosition(screenPos - graphic_->getHotspot(current_frame_, angle));
    renderTarget.draw(sprite);

    for (const GraphicDelta &delta : m_deltas) {
        sf::Sprite sprite;
        sprite.setTexture(delta.graphic->getImage());
        sprite.setPosition(screenPos - delta.graphic->getHotspot(0, 0) - delta.offset);
        renderTarget.draw(sprite);
    }
}

void GraphicRender::drawOutlineOn(sf::RenderTarget &renderTarget, ScreenPos screenPos)
{
    if (!graphic_ || !graphic_->isValid()) {
        return;
    }

    sf::Sprite sprite;
    sprite.setTexture(outline());
    sprite.setPosition(screenPos - graphic_->getHotspot(current_frame_, angle));
    sf::BlendMode blendMode = sf::BlendAlpha;
    blendMode.alphaSrcFactor = sf::BlendMode::DstAlpha;
    renderTarget.draw(sprite, blendMode);
}

const sf::Texture &GraphicRender::image()
{
    if (!graphic_) {
        return nullImage;
    }
    return graphic_->getImage(current_frame_, angle);
}

const sf::Texture &GraphicRender::outline()
{
    if (!graphic_) {
        return nullImage;
    }

    return graphic_->overlayImage(current_frame_, angle, m_playerId);
}

void GraphicRender::setGraphic(res::GraphicPtr graphic)
{
    graphic_ = graphic;

    current_frame_ = 0;

    m_deltas.clear();

    for (const genie::GraphicDelta &delta : graphic->deltas()) {
        if (delta.GraphicID < 0) {
            continue;
        }

        GraphicDelta graphicDelta;
        graphicDelta.graphic = ResourceManager::Inst()->getGraphic(delta.GraphicID);
        if (!graphicDelta.graphic->isValid()) {
            continue;
        }

        graphicDelta.offset = ScreenPos(delta.OffsetX, delta.OffsetY);

        m_deltas.push_back(graphicDelta);
    }

    if (!m_deltas.empty()) {
        std::reverse(m_deltas.begin(), m_deltas.end());
    }
}

ScreenRect GraphicRender::rect()
{
    ScreenRect ret;
    const ScreenPos hotspot = graphic_->getHotspot(current_frame_, angle);
    ret.x = -hotspot.x;
    ret.y = -hotspot.y;
    const sf::Vector2u size = image().getSize();
    ret.width = size.x;
    ret.height = size.y;

    for (const GraphicDelta &delta : m_deltas) {
        ScreenPos position = delta.graphic->getHotspot(0, 0) - delta.offset;
        const sf::Texture &deltaImage = delta.graphic->getImage();
        ScreenRect deltaRect;
        deltaRect.x = -position.x;
        deltaRect.y = -position.y;
        deltaRect.width = deltaImage.getSize().x;
        deltaRect.height = deltaImage.getSize().y;
        ret += deltaRect;
    }

    return ret;
}

}
