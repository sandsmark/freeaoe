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
    unitManager->onCursorPositionChanged(m_position, m_renderTarget->camera());

    switch(unitManager->state()) {
    case UnitManager::State::Default: {
        const Task &targetAction = unitManager->currentActionUnderCursor();
        if (!targetAction.isValid()) {
            return setCursor(MouseCursor::Normal);
        }

        REQUIRE(targetAction.data, return false);

        if (targetAction.data->ActionType == genie::ActionType::Combat) {
            return setCursor(MouseCursor::Attack);
        } else {
            return setCursor(MouseCursor::Action);
        }

        break;
    }
    case UnitManager::State::SelectingAttackTarget: {
        return setCursor(MouseCursor::Axe); // idk
    }
    case UnitManager::State::PlacingBuilding:
    case UnitManager::State::PlacingWall:
        return setCursor(MouseCursor::Invalid); // IDK
    case UnitManager::State::SelectingGarrisonTarget:
        return setCursor(MouseCursor::Garrison);
    }

    WARN << "Unhandled state" << unitManager->state();
    return false;
}

void MouseCursor::render()
{
    if (m_currentType == Invalid) {
        return;
    }
    m_cursor_pos_text.setString(std::to_string(m_position.x) + ", " + std::to_string(m_position.y));
    m_cursor_pos_text.setCharacterSize(11);
    m_cursor_pos_text.setPosition(ScreenPos(m_position));

    if (m_currentType != Invalid) {
        m_renderTarget->draw(m_image, m_position);
    }

    m_renderTarget->draw(m_cursor_pos_text);
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

    if (type != Invalid) {
        REQUIRE(type < m_cursorsFile->getFrameCount(), return false);

        const genie::SlpFramePtr &newFrame = m_cursorsFile->getFrame(type);
        REQUIRE(newFrame != nullptr, return false);

        m_image = m_renderTarget->convertFrameToImage(newFrame);
    }

    m_currentType = type;
    return true;
}
