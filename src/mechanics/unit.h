#ifndef UNIT_H
#define UNIT_H

#include <memory>
namespace genie {
class Unit;
}

class Unit
{
public:
    Unit();

private:
    std::shared_ptr<genie::Unit> m_properties;
};

#endif // UNIT_H
