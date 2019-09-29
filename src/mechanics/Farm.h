#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <memory>

#include "Building.h"
#include "core/Types.h"
#include "render/GraphicRender.h"

class UnitManager;
namespace genie {
class Unit;
}  // namespace genie
namespace sf {
class RenderTarget;
}  // namespace sf
struct Player;

class FarmRender : public GraphicRender
{
public:
    FarmRender(const Size &size);

    void render(sf::RenderTarget &renderTarget, const ScreenPos screenPos, const RenderType pass) noexcept override;

private:
    sf::Texture m_availableTexture;
    sf::Texture m_unavailableTexture;
    ScreenPos m_hotspot;
    Size m_size;
};


class Farm : public Building
{
    enum TerrainTypes {
        FarmFinished = 7,
        FarmDead = 8,
        FarmConstruct0 = 29,
        FarmConstruct1 = 30,
        FarmConstruct2 = 31,
    };

public:
    Farm(const genie::Unit &data_, const std::shared_ptr<Player> &player, UnitManager &unitManager);
    void setCreationProgress(float progress) noexcept override;
    bool update(Time time) noexcept override;

    GraphicRender &renderer() noexcept override { return m_farmRenderer; }
    ScreenRect rect() const noexcept override;
    bool checkClick(const ScreenPos &pos) const noexcept override;

private:
    void setTerrain(const TerrainTypes terrainToSet) noexcept;

    int m_currentTerrain = -1;
    bool m_updated = true;
    FarmRender m_farmRenderer;
};

