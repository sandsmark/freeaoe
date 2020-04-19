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

#pragma once

#include "core/Logger.h"
#include "core/Types.h"

#include <memory>

class Sprite;
using SpritePtr = std::shared_ptr<Sprite>;

class GraphicRender;
class IRenderTarget;

enum class RenderType {
    Shadow,
    Base,
    BuildingAlpha,
    Outline,
    ConstructAvailable,
    ConstructUnavailable,
    InTheShadows, // TODO find a proper name for units not visible
};

inline LogPrinter &operator <<(LogPrinter &os, const RenderType &type) {
    os << "RenderType(";
    switch (type) {
    case RenderType::Shadow:
        os << "Shadow";
        break;
    case RenderType::Base:
        os << "Base";
        break;
    case RenderType::Outline:
        os << "Outline";
        break;
    case RenderType::ConstructAvailable:
        os << "ConstructAvailable";
        break;
    case RenderType::ConstructUnavailable:
        os << "ConstructUnavailable";
        break;
    case RenderType::InTheShadows:
        os << "InTheShadows";
        break;
    default:
        os << "Invalid";
        break;
    }
    os << ")";
    return os;
}

typedef std::shared_ptr<GraphicRender> GraphicRenderPtr;

/// Draws and manages Graphics for EntityForm objects.
class GraphicRender
{
public:
    virtual ~GraphicRender() = default;

    bool update(Time time, const bool isVisible) noexcept;
    inline bool isValid() const noexcept;

    virtual void render(IRenderTarget &renderTarget, const ScreenPos screenPos, const RenderType renderpass) noexcept;

    void setPlayerColor(int playerColor) noexcept;
    void setCivId(int civId) noexcept { m_civId = civId; }

    void setDamageOverlay(const int spriteId) noexcept;

    bool setSprite(const int &spriteId) noexcept;
    bool setSprite(const SpritePtr &sprite) noexcept;
    inline const SpritePtr &sprite() const noexcept { return m_sprite; }
    int spriteId() const noexcept;

    ScreenRect rect() const noexcept;
    bool checkClick(const ScreenPos &pos) const noexcept;

    void setOrientation(int orientation) noexcept;

    void setAngle(float angle) noexcept;
    float angle() const { return m_angle; }

    int frameCount() const noexcept;

    inline int currentFrame() const noexcept { return m_currentFrame; }
    void setCurrentFrame(int frame) noexcept;

    void setPlaySounds(bool playSound) noexcept { m_playSounds = playSound; }

private:
    void maybePlaySound(const float pan, const float volume) noexcept;

    struct GraphicDelta {
        inline bool validForAngle(const float angle) const noexcept;

        GraphicRenderPtr graphic;
        ScreenPos offset;
        int angleToDrawOn = -1;
    };

    Time m_lastFrameTime = 0;
    std::vector<GraphicDelta> m_deltas;

    int m_playerColor = 0;
    int m_civId = 0;

    int m_currentFrame = 0;
    float m_angle = 0;
    SpritePtr m_sprite;

    std::unique_ptr<GraphicRender> m_damageOverlay;

    bool m_frameChanged = false;
    int m_currentSound = 0;
    bool m_playSounds = false;
};

