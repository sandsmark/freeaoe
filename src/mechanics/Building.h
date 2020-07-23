#ifndef BUILDING_H
#define BUILDING_H

#include <stddef.h>
#include <memory>
#include <string>
#include <vector>

#include "Entity.h"
#include "Unit.h"
#include "core/ResourceMap.h"
#include "core/Types.h"

class UnitManager;
struct Player;

namespace genie {
class Tech;
class Unit;
}

struct Building : public Unit
{
    typedef std::shared_ptr<Building> Ptr;

    Building(const genie::Unit &data_, const std::shared_ptr<Player> &player, UnitManager &unitManager);
    ~Building();

    std::vector<std::weak_ptr<Unit>> garrisonedUnits;
    int constructors = 0;

    bool ungarrison(const std::shared_ptr<Unit> &unit);

    bool enqueueProduceUnit(const genie::Unit *data) noexcept;
    bool enqueueProduceResearch(const genie::Tech *data) noexcept;
    void abortProduction(size_t index) noexcept;
    size_t productionQueueLength() const noexcept { return m_productionQueue.size() + (m_currentProduct != nullptr ? 1 : 0); }

    bool isResearching() const noexcept { return m_currentProduct && m_currentProduct->type == Product::Research; }
    bool isProducing() const noexcept { return productionQueueLength() > 0; }
    int productIcon(size_t index) noexcept;
    std::string currentProductName() noexcept;
    float productionProgress() const noexcept;

    bool update(Time time) noexcept override;

    void setPosition(const MapPos &pos, const bool initial = false) override;

    MapPos waypoint;

    static bool canPlace(const MapPos &pos, const MapPtr &map, const genie::Unit *data) noexcept;

private:
    void finalizeUnit() noexcept;
    void finalizeResearch() noexcept;
    void attemptStartProduction() noexcept;

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
