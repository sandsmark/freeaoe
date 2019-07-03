#include "MouseCursor.h"

#include "resource/Resource.h"

#include <genie/resource/SlpFile.h>

void MouseCursor::setCursor(const MouseCursor::Type type)
{
    if (type == currentType) {
        return;
    }

    texture.loadFromImage(Resource::convertFrameToImage(cursorsFile->getFrame(type)));
    sprite.setTexture(texture, true);
    currentType = type;
}
