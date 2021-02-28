#pragma once

#include "actions/IAction.h"

#include <memory>
#include <utility>
#include <deque>

using ActionPtr = std::shared_ptr<IAction>;
struct Player;

struct TaskSet {
    using iterator = std::vector<Task>::iterator;
    using const_iterator = std::vector<Task>::const_iterator;

    inline iterator begin() { return tasks.begin(); }
    inline iterator end() { return tasks.end(); }

    inline const_iterator begin() const { return tasks.begin(); }
    inline const_iterator end() const { return tasks.end(); }

    inline bool isEmpty() const { return tasks.empty(); }
    size_t size() const { return tasks.size(); }

    const Task &first() const { return tasks[0]; }

    bool contains(const Task &task) const {
        return std::find(tasks.begin(), tasks.end(), task) != tasks.end();
    }

    // STL sucks, so let's wrap it
    inline void add(const Task &task) {
        REQUIRE(task.isValid(), return);
        const std::vector<Task>::const_iterator it = std::find(tasks.begin(), tasks.end(), task);
        if (it != tasks.end()) {
            return;
        }
        tasks.push_back(task);
    }

    inline bool remove(const Task &task) {
        REQUIRE(task.isValid(), return false);
        const std::vector<Task>::const_iterator it = std::find(tasks.begin(), tasks.end(), task);
        if (it == tasks.end()) {
            return false;
        }
        tasks.erase(it);
        return true;
    }
    void clear() {
        tasks.clear();
    }

    std::vector<Task> tasks;
};


struct UnitActionHandler
{
    UnitActionHandler(Unit *unit);

    TaskSet availableActions() const noexcept;

    Task findAnyTask(const genie::ActionType &type, int targetUnit) noexcept;
    Task findTaskWithTarget(const std::shared_ptr<Unit> &target);
    static Task findMatchingTask(const std::shared_ptr<Player> &ownPlayer, const std::shared_ptr<Unit> &target, const TaskSet &potentials);

    bool hasAutoTargets() const noexcept { return m_autoTargetTasks.size() > 0; }
    Task checkForAutoTargets() ;

    int taskGraphicId(const genie::ActionType taskType, const IAction::UnitState state);

    void prependAction(const ActionPtr &action) noexcept;
    void queueAction(const ActionPtr &action) noexcept;
    void removeAction(const ActionPtr &action);
    void clearActionQueue() noexcept;

    void setCurrentAction(const ActionPtr &action) noexcept;
    const ActionPtr &currentAction() const noexcept { return m_currentAction; }

    ActionPtr m_currentAction;
    std::deque<ActionPtr> m_actionQueue;

    TaskSet m_autoTargetTasks;
    bool autoConvert = false;

private:
    Unit *m_unit;
};
