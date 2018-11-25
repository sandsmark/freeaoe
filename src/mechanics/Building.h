#ifndef BUILDING_H
#define BUILDING_H

#include "Unit.h"
#include <vector>

namespace genie {
class Tech;
}

class Map;

struct Building : public Unit
{
    struct Product {
        enum {
            Unit,
            Research
        } type;

        ResourceMap cost;

        union {
            const genie::Unit *unit = nullptr;
            const genie::Tech *tech;
        };
    };

    typedef std::shared_ptr<Building> Ptr;

    Building(const genie::Unit &data_, const std::shared_ptr<Player> &player, const MapPtr &map_);

    int garrisonedUnits = 0;
    int constructors = 0;

    inline const std::vector<Product> &productionQueue() const { return m_productionQueue; }
    void enqueueProduceUnit(const genie::Unit *data);
    void enqueueProduceResearch(const genie::Tech *data);
    void abortProduction(const size_t index);

    int productionProgressPercent() const;

private:
    std::vector<Product> m_productionQueue;
    float m_productionProgress = 0.f;
};

#endif // BUILDING_H
