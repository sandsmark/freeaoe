#include "Building.h"

#include <genie/Types.h>
#include <genie/dat/Research.h>
#include <genie/dat/TerrainRestriction.h>
#include <genie/dat/Unit.h>
#include <genie/dat/unit/../ResourceUsage.h>
#include <genie/dat/unit/Creatable.h>
#include <stdint.h>
#include <algorithm>
#include <utility>

#include "Map.h"
#include "MapTile.h"
#include "Player.h"
#include "UnitFactory.h"
#include "audio/AudioPlayer.h"
#include "core/Constants.h"
#include "core/Logger.h"
#include "mechanics/Civilization.h"
#include "mechanics/UnitManager.h"
#include "resource/DataManager.h"
#include "resource/LanguageManager.h"

Building::Building(const genie::Unit &data_, const std::shared_ptr<Player> &player_, UnitManager &unitManager) :
    Unit(data_, player_, unitManager, Entity::Type::Building)
{

}

bool Building::enqueueProduceUnit(const genie::Unit *data) noexcept
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

    for (const genie::Resource<short, short> &cost : data->Creatable.ResourceCosts) {
        if (!cost.Paid) {
            continue;
        }

        const genie::ResourceType type = genie::ResourceType(cost.Type);
        if (owner->resourcesAvailable(type) < cost.Amount) {
            return false;
        }
    }

    for (const genie::Resource<short, short> &cost : data->Creatable.ResourceCosts) {
        if (!cost.Paid) {
            continue;
        }

        const genie::ResourceType type = genie::ResourceType(cost.Type);
        owner->removeResource(type, cost.Amount);
        product->cost[type] = cost.Amount;
    }

    m_productionQueue.push_back(std::move(product));

    if (!m_currentProduct) {
        attemptStartProduction();
    }


    return true;
}

bool Building::enqueueProduceResearch(const genie::Tech *data) noexcept
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

    for (const genie::Resource<int16_t, int8_t> &cost : data->ResourceCosts) {
        if (!cost.Paid) {
            continue;
        }

        const genie::ResourceType type = genie::ResourceType(cost.Type);
        if (owner->resourcesAvailable(type) < cost.Amount) {
            return false;
        }
    }

    for (const genie::Resource<int16_t, int8_t> &r : data->ResourceCosts) {
        if (!r.Paid) {
            continue;
        }

        const genie::ResourceType type = genie::ResourceType(r.Type);

        owner->removeResource(type, r.Amount);
        product->cost[type] = r.Amount;
    }

    m_productionQueue.push_back(std::move(product));

    if (!m_currentProduct) {
        attemptStartProduction();
    }

    return true;
}

void Building::abortProduction(size_t index) noexcept
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

    for (const std::pair<const genie::ResourceType, float> &cost : toAbort.cost) {
        owner->addResource(cost.first, cost.second);
    }

    m_productionQueue.erase(m_productionQueue.begin() + index);
}

float Building::productionProgress() const noexcept
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

int Building::productIcon(size_t index) noexcept
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

std::string Building::currentProductName() noexcept
{
    if (!m_currentProduct) {
        if (m_productionQueue.empty()) {
            return "";
        }
        if (m_productionQueue.front()->type == Product::Unit) {
            return LanguageManager::Inst()->getString(m_productionQueue.front()->unit->LanguageDLLName);
        } else {
            return LanguageManager::Inst()->getString(m_productionQueue.front()->tech->LanguageDLLName);
        }
    }

    if (m_currentProduct->type == Product::Unit) {
        return LanguageManager::Inst()->getString(m_currentProduct->unit->LanguageDLLName);
    } else {
        return LanguageManager::Inst()->getString(m_currentProduct->tech->LanguageDLLName);
    }
}



bool Building::update(Time time) noexcept
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
                finalizeResearch();
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

void Building::setPosition(const MapPos &pos, const bool initial) noexcept
{
    Unit::setPosition(Unit::snapPositionToGrid(pos, m_map.lock(), data()), initial);
}

bool Building::canPlace(const MapPos &position, const MapPtr &map, const genie::Unit *data) noexcept
{
    if (!map) {
        WARN << "No map available";
        return false;
    }
    if (!data) {
        WARN << "no data!";
        return false;
    }

    std::vector<float> passable = DataManager::Inst().getTerrainRestriction(data->TerrainRestriction).PassableBuildableDmgMultiplier;

    const int tileX = position.x / Constants::TILE_SIZE;
    const int tileY = position.y / Constants::TILE_SIZE;

    const int valid1 = data->PlacementTerrain.first;
    const int valid2 = data->PlacementTerrain.first;

    const int width = data->ClearanceSize.x + data->Size.x;
    const int height = data->ClearanceSize.x + data->Size.x;

    if (!map->isValidTile(tileX - width/2, tileY - width/2)) {
        return false;
    }

    if (!map->isValidTile(tileX + width/2, tileY + height/2)) {
        return false;
    }

    for (int dx = 0; dx < width; dx++) {
        for (int dy = 0; dy < width; dy++) {
            const int terrainId = map->getTileAt(tileX + dx - width/2, tileY + dy - height/2).terrainId;
            if (valid1 != -1 && terrainId != valid1) {
                return false;
            }
            if (valid2 != -1 && terrainId != valid2) {
                return false;
            }
            if (!passable[terrainId]) {
                return false;
            }
        }
    }

    return true;
}

void Building::finalizeUnit() noexcept
{
    Player::Ptr owner = player.lock();
    if (!owner) {
        WARN << "owner went away";
        return;
    }

    waypoint.x = position().x + 24;
    waypoint.y = position().y + 24;

    Unit::Ptr unit = UnitFactory::Inst().createUnit(m_currentProduct->unit->ID, waypoint, owner, m_unitManager);
    m_unitManager.add(unit);

    Player::Ptr player = unit->player.lock();
    if (player) {
        AudioPlayer::instance().playSound(unit->data()->TrainSound, player->civilization.id());
    } else {
        WARN << "Lost our player";
    }

    DBG << "Finalized" << unit->debugName;
}

void Building::finalizeResearch() noexcept
{
    Player::Ptr owner = player.lock();
    if (!owner) {
        WARN << "building owner went away";
        return;
    }
    owner->applyResearch(m_currentProduct->tech->EffectID);

}

void Building::attemptStartProduction() noexcept
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
        for (const genie::Resource<short, short> &cost : product.unit->Creatable.ResourceCosts) {
            if (cost.Paid) {
                continue;
            }

            const genie::ResourceType type = genie::ResourceType(cost.Type);
            if (owner->resourcesAvailable(type) < cost.Amount) {
                return;
            }
        }
    } else {
        for (const genie::Resource<int16_t, int8_t> &cost : product.tech->ResourceCosts) {
            if (cost.Paid) {
                continue;
            }

            const genie::ResourceType type = genie::ResourceType(cost.Type);
            if (owner->resourcesAvailable(type) < cost.Amount) {
                return;
            }
        }
    }

    m_productionProgress = 0.f;
    m_currentProduct = std::move(m_productionQueue.front());
    m_productionQueue.erase(m_productionQueue.begin());
}
