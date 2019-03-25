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

#include <resource/Graphic.h>
#include <resource/AssetManager.h>
#include <SFML/Graphics/Texture.hpp>

struct Entity;

class GraphicRender;

enum class RenderType {
    Shadow,
    Base,
    BuildingAlpha,
    Outline,
    ConstructAvailable,
    ConstructUnavailable
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
    GraphicRender();
    virtual ~GraphicRender();

    bool update(Time time);
    bool isValid() const { return m_graphic && m_graphic->isValid(); }

    virtual void render(sf::RenderTarget &renderTarget, const ScreenPos screenPos, const RenderType renderpass);

    void setPlayerId(int playerId);
    void setCivId(int civId) { m_civId = civId; }

    void setDamageOverlay(const int graphicId);

    bool setGraphic(const int &graphicId);
    bool setGraphic(const GraphicPtr &graphic);
    inline const GraphicPtr &graphic() const { return m_graphic; }
    int graphicId() const;

    ScreenRect rect() const;
    bool checkClick(const ScreenPos &pos) const;

    void setAngle(float angle);
    float angle() const { return m_angle; }

    int frameCount() const { return m_graphic ? m_graphic->frameCount() : 0; }

    inline int currentFrame() const { return m_currentFrame; }
    void setCurrentFrame(int frame);

    void setPlaySounds(bool playSound) { m_playSounds = playSound; }

private:
    void maybePlaySound(const float pan, const float volume);

    struct GraphicDelta {
        GraphicRenderPtr graphic;
        ScreenPos offset;
        int angleToDrawOn = -1;
    };

    Time m_lastFrameTime;
    std::vector<GraphicDelta> m_deltas;

    int m_playerId = 0;
    int m_civId = 0;

    int m_currentFrame;
    float m_angle = 0;
    GraphicPtr m_graphic;

    std::unique_ptr<GraphicRender> m_damageOverlay;

    bool m_frameChanged = false;
    int m_currentSound = 0;
    bool m_playSounds = false;
};

