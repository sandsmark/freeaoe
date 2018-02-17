#ifndef CIVILIZATION_H
#define CIVILIZATION_H

//#include <genie/dat/Research.h>
//#include <genie/dat/Unit.h>
#include <genie/dat/Civ.h>
#include <genie/dat/Research.h>

#include <unordered_map>
#include <vector>
#include <memory>

namespace genie {
class Tech;
class Unit;
class DatFile;
}

class Civilization
{
public:
    Civilization(const int civId, const genie::DatFile &dataFile);

    int id() { return m_civId; }

    const std::vector<const genie::Unit *> creatableUnits(int16_t creator) const;

    const std::vector<const genie::Tech *> researchAvailableAt(int16_t creator) const;

    const genie::Unit &unit(const uint16_t id) const;
    const genie::Tech &tech(const uint16_t id) const;

private:
    const genie::Unit nullUnit;

    std::unordered_map<int16_t, std::vector<const genie::Unit*>> m_creatableUnits;
    std::unordered_map<int16_t, std::vector<const genie::Tech*>> m_researchAvailable;

    const int m_civId;
    const genie::Civ m_data;

    std::unordered_map<uint16_t, genie::Tech> m_techs;

};

#endif // CIVILIZATION_H
