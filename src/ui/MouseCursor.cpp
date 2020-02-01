#include "MouseCursor.h"

#include <genie/resource/SlpFile.h>
#include <genie/dat/UnitCommand.h>

#include "core/Logger.h"
#include "mechanics/UnitManager.h"
#include "render/IRenderTarget.h"
#include "resource/AssetManager.h"

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
    return true;
}

bool MouseCursor::update(const std::shared_ptr<UnitManager> &unitManager)
{
    const Task targetAction = unitManager->defaultActionAt(m_position, m_renderTarget->camera());
    if (!targetAction.data) {
        return setCursor(MouseCursor::Normal);
    } else if (targetAction.data->ActionType == genie::ActionType::Combat) {
        return setCursor(MouseCursor::Attack);
    } else {
        return setCursor(MouseCursor::Action);
    }
}

void MouseCursor::render()
{
    m_cursor_pos_text.setString(std::to_string(m_position.x) + ", " + std::to_string(m_position.y));
    m_cursor_pos_text.setCharacterSize(11);
    m_cursor_pos_text.setPosition(ScreenPos(m_position));
    m_renderTarget->draw(m_cursor_pos_text);
    m_renderTarget->draw(m_image, m_position);
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

    m_image = m_renderTarget->convertFrameToImage(newFrame);
    m_currentType = type;
    return true;
}
