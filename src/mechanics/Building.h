#ifndef BUILDING_H
#define BUILDING_H

#include "Unit.h"

class Map;

struct Building : public Unit
{
    typedef std::shared_ptr<Building> Ptr;

    Building(const genie::Unit &data_, const std::shared_ptr<Player> &player, const MapPtr &map_);

    int garrisonedUnits = 0;
    int constructors = 0;
};

#endif // BUILDING_H
