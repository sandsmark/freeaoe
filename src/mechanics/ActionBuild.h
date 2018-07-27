#ifndef ACTIONBUILD_H
#define ACTIONBUILD_H

#include "core/IAction.h"
#include "core/Entity.h"

namespace act {

class ActionBuild : public IAction
{

public:
    ActionBuild(Unit::Ptr builder, Unit::Ptr building);
    ~ActionBuild();

    bool update(Time time) override;

    UnitState unitState() const override;

private:
    std::weak_ptr<Unit> m_targetBuilding;
};

}//namespace act

#endif // ACTIONBUILD_H
