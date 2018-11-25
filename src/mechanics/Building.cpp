#include "Building.h"

Building::Building(const genie::Unit &data_, const std::shared_ptr<Player> &player, const MapPtr &map_) :
    Unit(data_, player, map_, Entity::Type::Building)
{

}
