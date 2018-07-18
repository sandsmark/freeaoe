#ifndef FARM_H
#define FARM_H

#include "core/Entity.h"

class Map;

class FarmRender : public comp::GraphicRender
{
public:
    FarmRender();

    void render(sf::RenderTarget &renderTarget, const ScreenPos screenPos, const comp::RenderType pass) override;

private:
    sf::Texture m_texture;
    ScreenPos m_hotspot;

};


class Farm : public Unit
{
    enum TerrainTypes {
        FarmFinished = 7,
        FarmDead = 8,
        FarmConstruct0 = 29,
        FarmConstruct1 = 30,
        FarmConstruct2 = 31,

    };
public:
    Farm(const genie::Unit &data_, int playerId, std::shared_ptr<Civilization> civilization, const std::shared_ptr<Map> &map);
    void setCreationProgress(float progress) override;
    bool update(Time time) override;

    comp::GraphicRender &renderer() override { return m_farmRenderer; }
    ScreenRect rect() const override;

private:
    std::weak_ptr<Map> m_map;
    int m_currentTerrain = -1;
    bool m_updated = true;
    FarmRender m_farmRenderer;
};

#endif // FARM_H
