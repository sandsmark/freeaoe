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

#include "resource/Graphic.h"
#include <SFML/Graphics/Texture.hpp>

struct Entity;

class GraphicRender;

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
    static const sf::Texture nullImage;

public:
    virtual ~GraphicRender() = default;

    bool update(Time time, const bool isVisible) noexcept;
    bool isValid() const noexcept { return m_graphic && m_graphic->isValid(); }

    virtual void render(sf::RenderTarget &renderTarget, const ScreenPos screenPos, const RenderType renderpass) noexcept;

    void setPlayerColor(int playerColor) noexcept;
    void setCivId(int civId) noexcept { m_civId = civId; }

    void setDamageOverlay(const int graphicId) noexcept;

    bool setGraphic(const int &graphicId) noexcept;
    bool setGraphic(const GraphicPtr &graphic) noexcept;
    inline const GraphicPtr &graphic() const noexcept { return m_graphic; }
    int graphicId() const noexcept;

    ScreenRect rect() const noexcept;
    bool checkClick(const ScreenPos &pos) const noexcept;

    void setAngle(float angle) noexcept;
    float angle() const { return m_angle; }

    int frameCount() const noexcept { return m_graphic ? m_graphic->frameCount() : 0; }

    inline int currentFrame() const noexcept { return m_currentFrame; }
    void setCurrentFrame(int frame) noexcept;

    void setPlaySounds(bool playSound) noexcept { m_playSounds = playSound; }

private:
    void maybePlaySound(const float pan, const float volume) noexcept;

    struct GraphicDelta {
        inline bool validForAngle(const float angle) const noexcept {
            if (angleToDrawOn < 0) {
                return true;
            }

            return graphic->m_graphic->angleToOrientation(angle) == angleToDrawOn;
        }

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
    GraphicPtr m_graphic;

    std::unique_ptr<GraphicRender> m_damageOverlay;

    sf::Texture m_halfBlackTexture; // for shading half visible units

    bool m_frameChanged = false;
    int m_currentSound = 0;
    bool m_playSounds = false;
};

