#pragma once

#include "core/Types.h"
#include "mechanics/StateManager.h"
#include "render/MapRenderer.h"
#include "ui/ActionPanel.h"
#include "ui/Dialog.h"
#include "ui/IconButton.h"
#include "ui/Minimap.h"
#include "ui/NumberLabel.h"
#include "ui/UiScreen.h"
#include "ui/UnitInfoPanel.h"
#include "Engine.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <memory>
#include <string>
#include <vector>

namespace sf
{
class Clock;
class Event;
class RenderWindow;
}

class SfmlRenderTarget;
struct MouseCursor;

class Editor
{
public:
    Editor();
    virtual ~Editor();
private:
    Engine engine;
};