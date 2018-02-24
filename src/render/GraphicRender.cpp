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

const sf::Image GraphicRender::nullImage;

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

void GraphicRender::drawOn(sf::RenderTarget &renderTarget, ScreenPos screenPos)
{
//    screenPos -= graphic_->getHotspot(current_frame_);

    sf::Texture texture;
    texture.loadFromImage(image());
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(screenPos - graphic_->getHotspot(current_frame_));
    renderTarget.draw(sprite);

    for (const GraphicDelta &delta : m_deltas) {
        sf::Texture texture;
        texture.loadFromImage(delta.graphic->getImage());
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(screenPos - delta.graphic->getHotspot() - delta.offset);
//        sprite.setPosition(screenPos - delta.offset - delta.graphic->getHotspot());
        renderTarget.draw(sprite);
    }
}

void GraphicRender::drawOutlineOn(sf::RenderTarget &renderTarget, ScreenPos screenPos)
{
    screenPos = graphic_->getHotspot();

    sf::Texture texture;
    texture.loadFromImage(outline());
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(screenPos);
    sf::BlendMode blendMode = sf::BlendAlpha;
    blendMode.alphaSrcFactor = sf::BlendMode::DstAlpha;
    renderTarget.draw(sprite, blendMode);

    for (const GraphicDelta &delta : m_deltas) {
        sf::Texture texture;
        texture.loadFromImage(delta.graphic->getImage());
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(screenPos + delta.offset);
        sf::BlendMode blendMode = sf::BlendAlpha;
        blendMode.alphaSrcFactor = sf::BlendMode::DstAlpha;
        renderTarget.draw(sprite, blendMode);
    }
}

const sf::Image &GraphicRender::image()
{
    if (!graphic_) {
        return nullImage;
    }
    return graphic_->getImage(current_frame_);
}

const sf::Image &GraphicRender::outline()
{
    if (!graphic_) {
        return nullImage;
    }

    return graphic_->overlayImage(current_frame_, angle, m_playerId);
}

void GraphicRender::setGraphic(res::GraphicPtr graphic)
{
    graphic_ = graphic;

    m_deltas.clear();

    for (const genie::GraphicDelta &delta : graphic->deltas()) {
        if (delta.GraphicID < 0) {
            continue;
        }

        GraphicDelta graphicDelta;
        graphicDelta.graphic = ResourceManager::Inst()->getGraphic(delta.GraphicID);
        if (!graphicDelta.graphic->isValid()) {
            std::cerr << "failed to get delta" << std::endl;
            continue;
        }

        graphicDelta.offset = ScreenPos(delta.OffsetX, delta.OffsetY);

        m_deltas.push_back(graphicDelta);
    }

    if (!m_deltas.empty()) {
        std::reverse(m_deltas.begin(), m_deltas.end());
    }
}

}
