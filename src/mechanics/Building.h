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

    typedef std::shared_ptr<Building> Ptr;

    Building(const genie::Unit &data_, const std::shared_ptr<Player> &player, const MapPtr &map_);

    int garrisonedUnits = 0;
    int constructors = 0;

    bool enqueueProduceUnit(const genie::Unit *data);
    bool enqueueProduceResearch(const genie::Tech *data);
    void abortProduction(const size_t index);
    size_t productionQueueLength() { return m_productionQueue.size(); }

    bool isProducing() const { return !m_productionQueue.empty(); }
    int productionQueueIcon(const size_t index);
    std::string currentProductName();
    float productionProgress() const;

private:
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

    std::vector<Product> m_productionQueue;
    float m_productionProgress = 0.f;
};

#endif // BUILDING_H
