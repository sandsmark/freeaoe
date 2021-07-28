#include "IconButton.h"

#include <genie/resource/SlpFile.h>
#include <genie/resource/SlpFrame.h>

#include "core/Logger.h"
#include "render/IRenderTarget.h"
#include "resource/AssetManager.h"
#include "resource/Resource.h"

IconButton::IconButton(std::shared_ptr<IRenderTarget> renderTarget) :
    m_renderTarget(std::move(renderTarget))
{
    genie::SlpFilePtr buttonsFile = AssetManager::Inst()->getSlp("btngame2x.shp");
    if (!buttonsFile) {
        WARN << "Failed to load SLP for buttons";
        return;
    }

    if (buttonsFile->getFrameCount() < IconButton::ButtonsCount * 2) {
        WARN << "Not enough buttons";
        return;
    }

    m_buttonsFile = buttonsFile;
}

bool IconButton::setType(const IconButton::Type type)
{
    if (type >= ButtonsCount) {
        WARN << "Invalid type" << type;
        return false;
    }

    if (type == m_type) {
        DBG << "Tried to set same button type";
        return false;
    }
    if (!m_buttonsFile) {
        WARN << "No buttons file available!";
        return false;
    }

    m_type = type;

    genie::SlpFramePtr frame = m_buttonsFile->getFrame(type * 2);
    if (!frame) {
        WARN << "Failed to load normal graphic for icon button";
        return false;
    }
    texture.loadFromImage(Resource::convertFrameToImage(frame));

    frame = m_buttonsFile->getFrame(type * 2 + 1);
    if (!frame) {
        WARN << "Failed to load pressed graphic for icon button";
        return false;
    }
    pressedTexture.loadFromImage(Resource::convertFrameToImage(frame));

    m_rect.setSize(texture.getSize());

    m_sprite.setTexture(texture);

    return true;
}

bool IconButton::setPosition(const ScreenPos &position)
{
    if (position == m_position) {
        return false;
    }

    m_position = position;
    m_sprite.setPosition(position);
    m_rect.x = position.x;
    m_rect.y = position.y;
    return true;
}

bool IconButton::onMousePressed(const ScreenPos &mousePosition)
{
    return setPressed(m_rect.contains(mousePosition));
}

bool IconButton::onMouseReleased(const ScreenPos &mousePosition)
{
    if (m_pressed && m_rect.contains(mousePosition)) {
        setPressed(false);
        return true;
    }

    setPressed(false);

    return false;
}

void IconButton::render() const
{
    m_renderTarget->draw(m_sprite);
}

bool IconButton::setPressed(const bool isPressed)
{
    if (isPressed == m_pressed) {
        return false;
    }
    m_pressed = isPressed;

    if (m_pressed) {
        m_sprite.setTexture(pressedTexture);
    } else {
       m_sprite.setTexture(texture);
    }
    return true;
}
