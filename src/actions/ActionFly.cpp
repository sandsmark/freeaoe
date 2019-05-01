#include "ActionFly.h"
#include "mechanics/Unit.h"
#include <genie/dat/Unit.h>
#include "mechanics/Map.h"

ActionFly::ActionFly(const std::shared_ptr<Unit> &unit, const Task &task) :
    IAction(IAction::Type::Fly, unit, task)
{

}


IAction::UpdateResult ActionFly::update(Time time)
{
    if (!m_lastUpdateTime) {
        m_lastUpdateTime = time;
        return UpdateResult::NotUpdated;
    }
    Unit::Ptr unit = m_unit.lock();
    if (!unit) {
        WARN << "Unit gone";
        return UpdateResult::Completed;
    }

    const float elapsed = time - m_lastUpdateTime;
    m_lastUpdateTime = time;

    if (time - m_lastTurnTime > 5000 && rand() % 100 > 99) {
        m_lastTurnTime = time;

        if (rand() % 2 == 0) {
            // there are usually (basically always, and I'm lazy) 8 angles
            unit->setAngle(unit->angle() + M_PI / 4);
        } else {
            unit->setAngle(unit->angle() - M_PI / 4);
        }
    }

    const int inStateTime = m_currentState == Moving ? 500 : 5000;
    if (time - m_lastStateChangeTime > inStateTime && rand() % 100 > 95 && unit->renderer().currentFrame() == 0) {
        m_lastStateChangeTime = time;

        if (rand() % 2 == 0) {
            m_currentState = UnitState::Proceeding;
        } else {
            m_currentState = UnitState::Moving;
        }
    }

    const float movement = elapsed * unit->data()->Speed * 0.15;

    // Need to convert to screen, because I'm dumb and the angles are screen relative
    const ScreenPos screenMovement(cos(unit->angle()), sin(unit->angle()));
    MapPos pos = unit->position() + screenMovement.toMap() * movement;

    if (pos.x < 0) {
        pos.x = unit->map()->width() - 1;
    }
    if (pos.x >= unit->map()->width()) {
        pos.x = 0;
    }
    if (pos.y < 0) {
        pos.y = unit->map()->height() - 1;
    }
    if (pos.y >= unit->map()->height()) {
        pos.y = 0;
    }

    unit->setPosition(pos);

    return UpdateResult::Updated;
}

IAction::UnitState ActionFly::unitState() const
{
    return m_currentState;
}
