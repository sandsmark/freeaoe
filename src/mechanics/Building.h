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

    Building(const genie::Unit &data_, const std::shared_ptr<Player> &player, UnitManager &unitManager);

    int garrisonedUnits = 0;
    int constructors = 0;

    bool enqueueProduceUnit(const genie::Unit *data);
    bool enqueueProduceResearch(const genie::Tech *data);
    void abortProduction(size_t index);
    size_t productionQueueLength() const { return m_productionQueue.size() + (m_currentProduct != nullptr ? 1 : 0); }

    bool isProducing() const { return productionQueueLength() > 0; }
    int productIcon(size_t index);
    std::string currentProductName();
    float productionProgress() const;

    bool update(Time time) override;

    MapPos waypoint;

private:
    void finalizeUnit();
    void attemptStartProduction();

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

    std::vector<std::unique_ptr<Product>> m_productionQueue;
    float m_productionProgress = 0.f;

    std::unique_ptr<Product> m_currentProduct;

    Time m_lastUpdateTime = 0;
};

#endif // BUILDING_H
