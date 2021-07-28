#pragma once

#include "core/Types.h"

#include <SFML/Graphics/Text.hpp>
#include <memory>

namespace genie {
class SlpFile;
typedef std::shared_ptr<SlpFile> SlpFilePtr;
}

class UnitManager;
class IRenderTarget;

namespace Drawable {
struct Image;
}

struct MouseCursor
{
    MouseCursor(std::shared_ptr<IRenderTarget> renderTarget);

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

    std::shared_ptr<Drawable::Image> m_image;
    genie::SlpFilePtr m_cursorsFile;
    ScreenPos m_position;
    sf::Text m_cursor_pos_text;

    std::shared_ptr<IRenderTarget> m_renderTarget;
};
