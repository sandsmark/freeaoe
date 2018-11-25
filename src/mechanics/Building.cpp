#include "Building.h"
#include "Player.h"
#include <genie/dat/Unit.h>
#include <genie/dat/Research.h>
#include "resource/LanguageManager.h"
#include "Map.h"
#include "UnitFactory.h"

Building::Building(const genie::Unit &data_, const std::shared_ptr<Player> &player, const MapPtr &map_) :
    Unit(data_, player, map_, Entity::Type::Building)
{

}

bool Building::enqueueProduceUnit(const genie::Unit *data)
{
    if (!data) {
        WARN << "trying to enqueue null unit";
        return false;
    }

    Player::Ptr owner = player.lock();
    if (!owner) {
        WARN << "building owner went away";
        return false;
    }

    DBG << debugName << "enqueueing production of unit" << data->Name;

    std::unique_ptr<Product> product = std::make_unique<Product>();
    product->type = Product::Unit;
    product->unit = data;

    for (const genie::Resource<short, short> &r : data->Creatable.ResourceCosts) {
        if (!r.Paid) {
            continue;
        }

        const genie::ResourceType type = genie::ResourceType(r.Type);
        if (owner->resources[type] < r.Amount) {
            return false;
        }
    }

    for (const genie::Resource<short, short> &r : data->Creatable.ResourceCosts) {
        if (!r.Paid) {
            continue;
        }

        const genie::ResourceType type = genie::ResourceType(r.Type);
        owner->resources[type] -= r.Amount;
        product->cost[type] = r.Amount;
    }

    m_productionQueue.push_back(std::move(product));

    if (!m_currentProduct) {
        attemptStartProduction();
    }


    return true;
}

bool Building::enqueueProduceResearch(const genie::Tech *data)
{
    if (!data) {
        WARN << "trying to enqueue null unit";
        return false;
    }

    Player::Ptr owner = player.lock();
    if (!owner) {
        WARN << "building owner went away";
        return false;
    }

    std::unique_ptr<Product> product = std::make_unique<Product>();
    product->type = Product::Research;
    product->tech = data;

    for (const genie::Resource<int16_t, int8_t> &r : data->ResourceCosts) {
        if (!r.Paid) {
            continue;
        }

        const genie::ResourceType type = genie::ResourceType(r.Type);
        if (owner->resources[type] < r.Amount) {
            return false;
        }
    }

    for (const genie::Resource<int16_t, int8_t> &r : data->ResourceCosts) {
        if (!r.Paid) {
            continue;
        }

        const genie::ResourceType type = genie::ResourceType(r.Type);

        owner->resources[type] -= r.Amount;
        product->cost[type] = r.Amount;
    }

    m_productionQueue.push_back(std::move(product));

    if (!m_currentProduct) {
        attemptStartProduction();
    }

    return true;
}

void Building::abortProduction(size_t index)
{
    if (m_currentProduct) {
        if (index == 0) {
            m_currentProduct.reset();
            return;

        }
        index--;
    }


    if (index >= m_productionQueue.size()) {
        WARN << "index for abort" << index << "is out of range" << m_productionQueue.size();
        return;
    }

    Player::Ptr owner = player.lock();
    if (!owner) {
        WARN << "building owner went away";
        return;
    }
    const Product &toAbort = *m_productionQueue.at(index);

    for (const std::pair<const genie::ResourceType, float> &r : toAbort.cost) {
        owner->resources[r.first] += r.second;
    }

    m_productionQueue.erase(m_productionQueue.begin() + index);
}

float Building::productionProgress() const
{
    if (!m_currentProduct) {
        return 0;
    }

    float maximum = 0;
    if (m_currentProduct->type == Product::Unit) {
        maximum = m_currentProduct->unit->Creatable.TrainTime;
    } else {
        maximum = m_currentProduct->tech->ResearchTime;
    }

    return std::min(m_productionProgress / maximum, 1.f);
}

int Building::productIcon(size_t index)
{
    if (m_currentProduct) {
        if (index == 0) {
            if (m_currentProduct->type == Product::Unit) {
                return m_currentProduct->unit->IconID;
            } else {
                return m_currentProduct->tech->IconID;
            }
        }

        index--;
    }


    if (index >= m_productionQueue.size()) {
        WARN << "index for abort" << index << "is out of range" << m_productionQueue.size();
        return 0;
    }

    if (m_productionQueue[index]->type == Product::Unit) {
        return m_productionQueue[index]->unit->IconID;
    } else {
        return m_productionQueue[index]->tech->IconID;
    }
}

std::string Building::currentProductName()
{
    if (!m_currentProduct) {
        return "";
    }
    if (m_currentProduct->type == Product::Unit) {
        return LanguageManager::Inst()->getString(m_currentProduct->unit->LanguageDLLName);
    } else {
        return LanguageManager::Inst()->getString(m_currentProduct->tech->LanguageDLLName);
    }
}



bool Building::update(Time time)
{
    const Time deltaTime = time - m_lastUpdateTime;
    m_lastUpdateTime = time;

    bool updated = Unit::update(time);

    if (m_currentProduct) {
        float productionTime = 0;
        if (m_currentProduct->type == Product::Unit) {
            productionTime = m_currentProduct->unit->Creatable.TrainTime;
        } else {
            productionTime = m_currentProduct->tech->ResearchTime;
        }

        m_productionProgress += deltaTime * 0.0015;
        if (m_productionProgress >= productionTime) {
            if (m_currentProduct->type == Product::Unit) {
                finalizeUnit();
            } else {
                DBG << "todo implement research";
            }

            m_currentProduct.reset();
            m_productionProgress = 0;
        }

        updated = true;
    } else if (!m_productionQueue.empty()) {
        attemptStartProduction();
        updated = true;
    }

    return updated;
}

void Building::finalizeUnit()
{
    MapPtr map = m_map.lock();
    if (!map) {
        WARN << "map went away";
        return;
    }
    Player::Ptr owner = player.lock();
    if (!owner) {
        WARN << "owner went away";
        return;
    }

    waypoint.x = position().x + 24;
    waypoint.y = position().y + 24;

    Unit::Ptr unit = UnitFactory::Inst().createUnit(m_currentProduct->unit->ID, waypoint, owner, map);
    DBG << "Finalized" << unit->debugName;
    // todo: add
}

void Building::attemptStartProduction()
{
    if (m_productionQueue.empty()) {
        DBG << "empty queue";
        return;
    }

    Player::Ptr owner = player.lock();
    if (!owner) {
        WARN << "building owner went away";
        return;
    }

    const Product &product = *m_productionQueue.front();

    if (product.type == Product::Unit) {
        for (const genie::Resource<short, short> &r : product.unit->Creatable.ResourceCosts) {
            if (r.Paid) {
                continue;
            }

            const genie::ResourceType type = genie::ResourceType(r.Type);
            if (owner->resources[type] < r.Amount) {
                return;
            }
        }
    } else {
        for (const genie::Resource<int16_t, int8_t> &r : product.tech->ResourceCosts) {
            if (r.Paid) {
                continue;
            }

            const genie::ResourceType type = genie::ResourceType(r.Type);
            if (owner->resources[type] < r.Amount) {
                return;
            }
        }
    }

    m_productionProgress = 0.f;
    m_currentProduct = std::move(m_productionQueue.front());
    m_productionQueue.erase(m_productionQueue.begin());
}
