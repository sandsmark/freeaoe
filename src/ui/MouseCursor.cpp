#include "MouseCursor.h"

#include "resource/Resource.h"
#include "resource/AssetManager.h"
#include "mechanics/UnitManager.h"
#include "render/IRenderTarget.h"

#include <genie/resource/SlpFile.h>

MouseCursor::MouseCursor(const std::shared_ptr<IRenderTarget> &renderTarget) :
    m_renderTarget(renderTarget)
{
    m_cursorsFile = AssetManager::Inst()->getSlp(AssetManager::filenameID("mcursors.shp"));
    if (!m_cursorsFile) {
        WARN << "Failed to get cursors";
    }

    setCursor(Type::Normal);
}

bool MouseCursor::isValid() const
{
    return m_currentType != Type::Invalid;
}

void MouseCursor::render(const ScreenPos &mousePos, const std::shared_ptr<UnitManager> &unitManager)
{
    const Task targetAction = unitManager->defaultActionAt(mousePos, m_renderTarget->camera());
    if (!targetAction.data) {
        setCursor(MouseCursor::Normal);
    } else if (targetAction.data->ActionType == genie::Task::Combat) {
        setCursor(MouseCursor::Attack);
    } else {
        setCursor(MouseCursor::Action);
    }


    m_sprite.setPosition(mousePos);
    m_renderTarget->draw(m_sprite);
}

void MouseCursor::setCursor(const MouseCursor::Type type)
{
    if (type == m_currentType) {
        return;
    }
    if (!m_cursorsFile) {
        WARN << "No cursors file available!";
    }

    const genie::SlpFramePtr &newFrame = m_cursorsFile->getFrame(type);
    if (!newFrame) {
        WARN << "Failed to load new cursor SLP for type" << type;
        return;
    }

    m_texture.loadFromImage(Resource::convertFrameToImage(newFrame));
    m_sprite.setTexture(m_texture, true);
    m_currentType = type;
}
