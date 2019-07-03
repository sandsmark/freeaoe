#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <memory>

namespace genie {
class SlpFile;
typedef std::shared_ptr<SlpFile> SlpFilePtr;
}

struct MouseCursor
{
    enum Type {
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

    void setCursor(const Type type);

    sf::Texture texture;
    sf::Sprite sprite;
    genie::SlpFilePtr cursorsFile;

    Type currentType = Normal;
};


