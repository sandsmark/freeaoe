#pragma once

#include "core/Types.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <memory>

namespace genie {
class SlpFile;
typedef std::shared_ptr<SlpFile> SlpFilePtr;
}

class UnitManager;
class IRenderTarget;

struct MouseCursor
{
    MouseCursor(const std::shared_ptr<IRenderTarget> &renderTarget);

    bool isValid() const;

    bool setPosition(const ScreenPos &position);
    bool update(const std::shared_ptr<UnitManager> &unitManager);
    void render();

private:
    enum Type {
        Invalid = -1,
        Normal = 0,
        Busy,
        Target,
        Action,
        Attack,
        TargetPos,
        WhatsThis,
        Build,
        Axe,
        Protect,
        Horn,
        MoveTo,
        Disabled,
        Garrison,
        Garrison2,
        Disembark,
        Embark,
        TargetCircle,
        Flag
    };

    bool setCursor(const Type type);
    Type m_currentType = Invalid;

    sf::Texture m_texture;
    sf::Sprite m_sprite;
    genie::SlpFilePtr m_cursorsFile;
    ScreenPos m_position;

    std::shared_ptr<IRenderTarget> m_renderTarget;
};


