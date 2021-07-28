#include "GameSpecific.h"

#include "mechanics/Unit.h"
#include "mechanics/Player.h"
#include "resource/DataManager.h"
#include <genie/dat/Unit.h>

bool Checks::canConvert(const Unit *converter, const Unit *target)
{
    if (converter->playerId() == target->playerId()) {
        return false;
    }

    // AoE1
    if (DataManager::Inst().gameVersion() < genie::GV_AoKE3) {
        // TODO
        return false;
    }

    // AOE2
    if (DataManager::Inst().gameVersion() < genie::GV_SWGB) {

        // https://ageofempires.fandom.com/wiki/Redemption#Affected_buildings
        // These can never be converted
        switch (target->data()->Class) {
        case genie::Unit::Wall:
        case genie::Unit::Flag:
            return false;
        case genie::Unit::Farm: // Fish traps and actual farms
            // Converted when a villager starts harvesting
            if (converter->data()->Class == genie::Unit::Civilian) {
                return true;
            } else {
                return false;
            }
        case genie::Unit::BuildingClass: {
            Player::Ptr owner = converter->player().lock();
            REQUIRE(owner, return false);
            return owner->resourcesAvailable(genie::ResourceType::EnableBuildingConversion) > 0;
        }
        case genie::Unit::Monk: {
            Player::Ptr owner = converter->player().lock();
            REQUIRE(owner, return false);
            return owner->resourcesAvailable(genie::ResourceType::EnableMonkConversion) > 0;
        }
        default:
            break;
        }

        // https://ageofempires.fandom.com/wiki/Redemption#Affected_buildings
        switch(target->data()->ID) {
        case AoE2::TownCenter:
        case AoE2::RelicCart:
        case AoE2::Wonder:
        case AoE2::Outlaw:
        case AoE2::FriarTuck:
        case AoE2::Castle:
        case AoE2::Monastery:
        default:
            break;
            // TODO: krepost from definitive edition
        }

        // TODO
        return true;
    }

    // SWGB
    // https://swgb.fandom.com/wiki/Jedi/Sith
    // sith knights can convert units, sith masters can also convert buildings
    if (target->data()->Class == genie::Unit::BuildingClass) {
        switch (converter->data()->ID) {
        case SWGB::SithMaster:
        case SWGB::SithMaster2:
        case SWGB::SithMasterHolocron:
        case SWGB::SithMasterHolocron2:
            return true;
        default:
            return false;
        }
    }
    // TODO: check, they can convert "normal" units, whatever that means
    switch (converter->data()->ID) {
    case SWGB::SithMaster:
    case SWGB::SithMaster2:
    case SWGB::SithMasterHolocron:
    case SWGB::SithMasterHolocron2:
    case SWGB::SithKnight:
    case SWGB::SithKnight2:
    case SWGB::SithKnightHolocron:
    case SWGB::SithKnightHolocron2:
        return true;
    default:
        return false;
    }

    return false;
}
