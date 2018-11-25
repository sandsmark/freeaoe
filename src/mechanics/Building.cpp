#include "Building.h"
#include "Player.h"
#include <genie/dat/Unit.h>
#include <genie/dat/Research.h>
#include "resource/LanguageManager.h"

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

    Product product;
    product.type = Product::Unit;
    product.unit = data;

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
        product.cost[type] = r.Amount;
    }

    m_productionQueue.push_back(product);

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

    Product product;
    product.type = Product::Research;
    product.tech = data;

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
        product.cost[type] = r.Amount;
    }

    m_productionQueue.push_back(product);

    return true;
}

void Building::abortProduction(const size_t index)
{
    if (index >= m_productionQueue.size()) {
        WARN << "index for abort" << index << "is out of range" << m_productionQueue.size();
        return;
    }

    Player::Ptr owner = player.lock();
    if (!owner) {
        WARN << "building owner went away";
        return;
    }
    const Product &toAbort = m_productionQueue.at(index);

    for (const std::pair<const genie::ResourceType, float> &r : toAbort.cost) {
        owner->resources[r.first] += r.second;
    }

    m_productionQueue.erase(m_productionQueue.begin() + index);
}

float Building::productionProgress() const
{
    if (m_productionQueue.empty()) {
        return 0;
    }
    float maximum = 0;
    if (m_productionQueue.front().type == Product::Unit) {
        maximum = m_productionQueue.front().unit->Creatable.TrainTime;
    } else {
        maximum = m_productionQueue.front().tech->ResearchTime;
    }

    return std::floor(m_productionProgress / maximum);
}

int Building::productionQueueIcon(const size_t index)
{
    if (index >= m_productionQueue.size()) {
        WARN << "index for abort" << index << "is out of range" << m_productionQueue.size();
        return 0;
    }
    if (m_productionQueue[index].type == Product::Unit) {
        return m_productionQueue[index].unit->IconID;
    } else {
        return m_productionQueue[index].tech->IconID;
    }
}

std::string Building::currentProductName()
{
    if (m_productionQueue.empty()) {
        return "";
    }
    const Product &product = m_productionQueue.front();
    if (product.type == Product::Unit) {
        return LanguageManager::Inst()->getString(product.unit->LanguageDLLName);
    } else {
        return LanguageManager::Inst()->getString(product.tech->LanguageDLLName);
    }
}

