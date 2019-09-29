#include "MouseCursor.h"

#include <genie/dat/unit/../UnitCommand.h>
#include <genie/resource/SlpFile.h>
#include <genie/resource/SlpFrame.h>

#include "actions/IAction.h"
#include "core/Logger.h"
#include "mechanics/UnitManager.h"
#include "render/IRenderTarget.h"
#include "resource/AssetManager.h"
#include "resource/Resource.h"

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

bool MouseCursor::setPosition(const ScreenPos &position)
{
    if (position == m_position) {
        return false;
    }

    m_position = position;
    m_sprite.setPosition(position);
    return true;
}

bool MouseCursor::update(const std::shared_ptr<UnitManager> &unitManager)
{
    const Task targetAction = unitManager->defaultActionAt(m_position, m_renderTarget->camera());
    if (!targetAction.data) {
        return setCursor(MouseCursor::Normal);
    } else if (targetAction.data->ActionType == genie::Task::Combat) {
        return setCursor(MouseCursor::Attack);
    } else {
        return setCursor(MouseCursor::Action);
    }
}

void MouseCursor::render()
{
    m_renderTarget->draw(m_sprite);
}

bool MouseCursor::setCursor(const MouseCursor::Type type)
{
    if (type == m_currentType) {
        return false;
    }
    if (!m_cursorsFile) {
        WARN << "No cursors file available!";
        return false;
    }

    const genie::SlpFramePtr &newFrame = m_cursorsFile->getFrame(type);
    if (!newFrame) {
        WARN << "Failed to load new cursor SLP for type" << type;
        return false;
    }

    m_texture.loadFromImage(Resource::convertFrameToImage(newFrame));
    m_sprite.setTexture(m_texture, true);
    m_currentType = type;
    return true;
}
