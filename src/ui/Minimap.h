#pragma once

#include <memory>

#include "core/Types.h"
#include "core/SignalEmitter.h"
#include "mechanics/IState.h"
#include "render/IRenderTarget.h"

class Map;
class UnitManager;
namespace sf {
class Event;
}  // namespace sf
struct Unit;
struct VisibilityMap;

class Minimap : public IState, public SignalReceiver
{
public:
    // TODO implement the rest
    enum class MinimapMode {
        Normal,
        Economic,
        Diplomatic
    };

    Minimap(const IRenderTargetPtr &renderTarget);

    void setMap(const std::shared_ptr<Map> &map);
    void setUnitManager(const std::shared_ptr<UnitManager> &unitManager);
    void setVisibilityMap(const std::shared_ptr<VisibilityMap> &visibilityMap);

    bool init() override;
    bool handleEvent(sf::Event event) override;
    void mouseExited() { m_mousePressed = false; }
    bool update(Time time) override;
    void draw() override;
    ScreenRect rect() const { return m_rect; }

private:
    void updateUnits();
    void updateTerrain();
    void updateCamera();
    bool updateRect(const Size &windowSize);

    Drawable::Color unitColor(const std::shared_ptr<Unit> &unit);

    bool m_unitsUpdated = false;
    bool m_terrainUpdated = false;
    std::shared_ptr<Map> m_map;
    std::shared_ptr<UnitManager> m_unitManager;
    IRenderTargetPtr m_renderTarget;
    ScreenRect m_rect;
    IRenderTargetPtr m_terrainTexture;
    IRenderTargetPtr m_unitsTexture;
    MapPos m_lastCameraPos;
    ScreenRect m_cameraRect;
    bool m_mousePressed = false;
    std::shared_ptr<VisibilityMap> m_visibilityMap;

    Size m_windowSize;

    MinimapMode m_mode = MinimapMode::Diplomatic; // easiest, so sue me
};

