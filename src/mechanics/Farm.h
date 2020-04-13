#pragma once

#include <memory>

#include "Building.h"
#include "core/Types.h"
#include "render/GraphicRender.h"
#include "render/IRenderTarget.h"

class UnitManager;
namespace genie {
class Unit;
}  // namespace genie
struct Player;

class FarmRender : public GraphicRender
{
    static constexpr int graphicId = 15023; // magic id

public:
    FarmRender(const Size &size);

    void render(IRenderTarget &renderTarget, const ScreenPos screenPos, const RenderType pass) noexcept override;

private:
    Drawable::Image::Ptr m_availableTexture;
    Drawable::Image::Ptr m_unavailableTexture;
    ScreenPos m_hotspot;
    Size m_size;

    std::shared_ptr<genie::SlpFrame> m_frame;
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

