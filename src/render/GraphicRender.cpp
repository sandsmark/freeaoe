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

#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <genie/dat/GraphicAttackSound.h>
#include <genie/dat/GraphicDelta.h>
#include <resource/AssetManager.h>
#include <algorithm>
#include <memory>
#include <vector>

#include "audio/AudioPlayer.h"
#include "core/Logger.h"
#include "core/Types.h"
#include "render/GraphicRender.h"
#include "resource/Graphic.h"

const sf::Texture GraphicRender::nullImage;

bool GraphicRender::update(Time time, const bool isVisible) noexcept
{
    m_frameChanged = false;

    bool updated = false;

    if (isVisible) {
        for (size_t i=0; i<m_deltas.size(); i++) {
            if (!m_deltas[i].validForAngle(m_angle)) {
                continue;
            }

            updated = m_deltas[i].graphic->update(time, isVisible) || updated;
        }

        if (m_damageOverlay) {
            updated = m_damageOverlay->update(time, isVisible) || updated;
        }
    }

    if (!m_graphic) {
        return updated;
    }
    if (!m_graphic->framerate()) {
        return updated;
    }

    const bool isAtEnd = m_currentFrame >= m_graphic->frameCount() - 1;

    // Just let it run out if we're not visible
    if (isAtEnd && (m_graphic->runOnce() || !isVisible)) {
        return updated;
    }

    int newFrame = m_currentFrame;

    Time elapsed = time - m_lastFrameTime;

    if (isAtEnd && elapsed < m_graphic->replayDelay() / 0.0015) {
        return updated;
    }

    if (m_lastFrameTime == 0) {
        m_lastFrameTime = time;
        newFrame = 0;
    } else if (elapsed > m_graphic->framerate() / 0.0015) {
        if (newFrame < m_graphic->frameCount() - 1) {
            newFrame++;
        } else {
            newFrame = 0;

            m_currentSound++;
            if (m_currentSound > 2) {
                m_currentSound = 0;
            }
        }

        m_lastFrameTime = time;
    }

    if (newFrame != m_currentFrame) {
        m_frameChanged = true;
    }

    m_currentFrame = newFrame;

    return updated || m_frameChanged;
}

inline bool GraphicRender::isValid() const noexcept
{
    return m_graphic && m_graphic->isValid();
}

void GraphicRender::render(sf::RenderTarget &renderTarget, const ScreenPos screenPos, const RenderType renderpass) noexcept
{
    if (m_frameChanged && m_playSounds) {
        m_frameChanged = false;

        const ScreenPos screenCenter = ScreenPos(renderTarget.getSize().x/2., renderTarget.getSize().y/2.);
        const float pan = (screenPos.x - screenCenter.x) / screenCenter.x;
        const float maxDistance = screenCenter.distanceTo(ScreenPos(0, 0));
        const float volume = (maxDistance - screenCenter.distanceTo(screenPos)) / maxDistance;
        maybePlaySound(pan, volume);
    }

    for (const GraphicDelta &delta : m_deltas) {
        if (!delta.validForAngle(m_angle)) {
            continue;
        }

        delta.graphic->render(renderTarget, screenPos + delta.offset, renderpass);
    }

    if (m_graphic && m_graphic->isValid()) {
        sf::Sprite sprite;
        sf::BlendMode blendMode;

        switch(renderpass) {
        case RenderType::Base:
            sprite.setTexture(m_graphic->texture(m_currentFrame, m_angle, m_playerColor, ImageType::Base));
            break;
        case RenderType::BuildingAlpha:
            sprite.setTexture(m_graphic->texture(m_currentFrame, m_angle, m_playerColor, ImageType::Base));
            blendMode = sf::BlendAdd;
            blendMode.colorSrcFactor = sf::BlendMode::Zero;
            blendMode.colorDstFactor = sf::BlendMode::Zero;
            break;
        case RenderType::Outline:
            sprite.setTexture(m_graphic->texture(m_currentFrame, m_angle, m_playerColor, ImageType::Outline));
            blendMode.alphaSrcFactor = sf::BlendMode::Zero;
            blendMode.alphaEquation = sf::BlendMode::Add;
            blendMode.alphaDstFactor = sf::BlendMode::DstAlpha;

            blendMode.colorSrcFactor = sf::BlendMode::One;
            blendMode.colorEquation = sf::BlendMode::Add;
            blendMode.colorDstFactor = sf::BlendMode::Zero;
            break;
        case RenderType::ConstructAvailable:
            sprite.setTexture(m_graphic->texture(m_currentFrame, m_angle, m_playerColor, ImageType::Construction));
            break;
        case RenderType::Shadow:
            sprite.setTexture(m_graphic->texture(m_currentFrame, m_angle, m_playerColor, ImageType::Shadow));
            break;
        case RenderType::ConstructUnavailable:
            sprite.setTexture(m_graphic->texture(m_currentFrame, m_angle, m_playerColor, ImageType::ConstructionUnavailable));
            break;
        case RenderType::InTheShadows:
            sprite.setTexture(m_graphic->texture(m_currentFrame, m_angle, m_playerColor, ImageType::InTheShadows));
            break;
        }

        sprite.setPosition(screenPos - m_graphic->getHotspot(m_currentFrame, m_angle));
        renderTarget.draw(sprite, blendMode);
    }


    if (m_damageOverlay) {
        m_damageOverlay->render(renderTarget, screenPos, renderpass);
    }
}

void GraphicRender::setPlayerColor(int playerColor) noexcept
{
    m_playerColor = playerColor;

    for (const GraphicDelta &delta : m_deltas) {
        delta.graphic->setPlayerColor(playerColor);
    }

    if (m_damageOverlay) {
        m_damageOverlay->setPlayerColor(playerColor);
    }
}

void GraphicRender::setDamageOverlay(const int graphicId) noexcept
{
    if (graphicId < 0) {
        m_damageOverlay.reset();
        return;
    }

    if (m_damageOverlay && graphicId == m_damageOverlay->graphic()->graphicId) {
        return;
    }

    GraphicPtr graphic = AssetManager::Inst()->getGraphic(graphicId);
    if (!graphic) {
        WARN << "Failed to find damage graphic" << graphicId;
        return;
    }

    if (!graphic->isValid()) {
        WARN << "Invalid damage graphic" << graphicId;
        return;
    }

    if (!m_damageOverlay) {
        m_damageOverlay = std::make_unique<GraphicRender>();
    }

    m_damageOverlay->setPlayerColor(m_playerColor);
    m_damageOverlay->setCivId(m_civId);
    m_damageOverlay->setAngle(m_angle);
    m_damageOverlay->setGraphic(graphic);
}

bool GraphicRender::setGraphic(const int &graphicId) noexcept
{
    return setGraphic(AssetManager::Inst()->getGraphic(graphicId));
}

bool GraphicRender::setGraphic(const GraphicPtr &graphic) noexcept
{
    if (graphic == m_graphic) {
        return true;
    }

    m_damageOverlay.reset();

    m_graphic = graphic;
    m_currentFrame = 0;
    m_currentSound = 0;
    m_frameChanged = true;
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
        delta.graphic->setPlayerColor(m_playerColor);
        delta.graphic->setCivId(m_civId);
        delta.graphic->setAngle(m_angle);

        // Don't use setGraphic, to avoid recursive adding of deltas
        delta.graphic->m_graphic = AssetManager::Inst()->getGraphic(deltaData.GraphicID);
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

int GraphicRender::graphicId() const noexcept
{
    if (!m_graphic) {
        return -1;
    }
    return m_graphic->frameCount();
}

ScreenRect GraphicRender::rect() const noexcept
{
    if (!isValid()) {
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
        if (!delta.graphic->isValid()) {
            continue;
        }

        if (!delta.validForAngle(m_angle)) {
            continue;
        }
        const ScreenRect deltaRect = delta.graphic->rect();
        if (deltaRect.isEmpty()) {
            continue;
        }

        if (ret.isEmpty()) {
            ret = (deltaRect + delta.offset);
        } else {
            ret += (deltaRect + delta.offset);
        }
    }

    return ret;
}

bool GraphicRender::checkClick(const ScreenPos &pos) const noexcept
{
    if (!isValid()) {
        return false;
    }
    const ScreenPos correctedPos = pos + m_graphic->getHotspot(m_currentFrame, m_angle);

    if (m_graphic->checkClick(correctedPos, m_currentFrame, m_angle)) {
        return true;
    }

    for (const GraphicDelta &delta : m_deltas) {
        if (!delta.graphic->isValid()) {
            continue;
        }

        if (delta.angleToDrawOn >= 0 && delta.graphic->m_graphic->angleToOrientation(m_angle) != delta.angleToDrawOn) {
            continue;
        }

        if (delta.graphic->checkClick(pos - delta.offset)) {
            return true;
        }
    }

    return false;
}

void GraphicRender::setAngle(float angle) noexcept
{
    m_angle = angle;

    for (GraphicDelta &delta : m_deltas) {
        delta.graphic->setAngle(angle);
    }

    if (m_damageOverlay) {
        m_damageOverlay->setAngle(angle);
    }
}

int GraphicRender::frameCount() const noexcept
{
    return m_graphic ? m_graphic->frameCount() : 0;
}

void GraphicRender::setCurrentFrame(int frame) noexcept
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

void GraphicRender::maybePlaySound(const float pan, const float volume) noexcept
{
    if (pan <= -1.0f || pan >= 1.0f) {
        return;
    }

    if (m_graphic->sound() != -1 && m_currentFrame == 1) {
        AudioPlayer::instance().playSound(m_graphic->sound(), m_civId, pan, volume);
    }

    if (!m_graphic->hasSounds()) {
        return;
    }

    const genie::GraphicAngleSound angleSound = m_graphic->soundForAngle(m_angle);
    if (angleSound.FrameNum == m_currentFrame) {
        AudioPlayer::instance().playSound(angleSound.SoundID, m_civId, pan, volume);
    }
    if (angleSound.FrameNum2 == m_currentFrame) {
        AudioPlayer::instance().playSound(angleSound.SoundID2, m_civId, pan, volume);
    }
    if (angleSound.FrameNum3 == m_currentFrame) {
        AudioPlayer::instance().playSound(angleSound.SoundID3, m_civId, pan, volume);
    }
}



bool GraphicRender::GraphicDelta::validForAngle(const float angle) const noexcept
{
    if (angleToDrawOn < 0) {
        return true;
    }

    return graphic->m_graphic->angleToOrientation(angle) == angleToDrawOn;
}
