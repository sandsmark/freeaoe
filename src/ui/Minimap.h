#ifndef MINIMAP_H
#define MINIMAP_H

#include <memory>
#include "mechanics/IState.h"
#include "global/Types.h"
#include <SFML/Graphics/RenderTexture.hpp>

class Map;
class SfmlRenderTarget;

class Minimap : public IState
{
public:
    Minimap(const std::shared_ptr<SfmlRenderTarget> &renderTarget);

    void setMap(const std::shared_ptr<Map> &map);

    bool init() override;
    void handleEvent(sf::Event event) override;
    bool update(Time time) override;
    void draw() override;

private:
    void updateUnits();
    void updateTerrain();


    bool m_updated = false;
    std::shared_ptr<Map> m_map;
    std::shared_ptr<SfmlRenderTarget> m_renderTarget;
    ScreenRect m_rect;
    sf::RenderTexture m_texture;
};

#endif // MINIMAP_H
