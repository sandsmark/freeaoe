/*
    Copyright (C) 2018 Martin Sandsmark <martin.sandsmark@kde.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef UNITINFOPANEL_H
#define UNITINFOPANEL_H

#include <memory>
#include <unordered_set>

#include <mechanics/IState.h>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class UnitManager;

struct Unit;
class SfmlRenderTarget;
class UnitManager;
typedef std::unordered_set<std::shared_ptr<Unit>> UnitSet;

class UnitInfoPanel : public IState
{
public:
    UnitInfoPanel(const std::shared_ptr<SfmlRenderTarget> &renderTarget);

    void setUnitManager(const std::shared_ptr<UnitManager> &unitManager);

    bool init() override;
    void handleEvent(sf::Event event) override;
    bool update(Time time) override;
    void draw() override;

    ScreenRect rect() const;

private:
    void updateInfo();
    void drawSingleUnit();
    void drawMultipleUnits();
    void drawUnitPortrait(const std::shared_ptr<Unit> &unit, ScreenPos pos);

    struct StatItem {
        enum Type {
            CarryingWoodAmount,
            CarryingStoneAmount,
            CarryingFoodAmount,
            CarryingGoldAmount,

            GarrisonCapacity,

            CarryingTradeAmount,

            AttackRange,
            Damage,
            Armor,

            TimeThing,
            ShieldThing,

            TypeCount
        };

        bool visible = false;
        sf::Text text;
        sf::Texture icon;
    };
    std::array<StatItem, StatItem::TypeCount> m_statItems;

    std::shared_ptr<SfmlRenderTarget> m_renderTarget;
    std::weak_ptr<UnitManager> m_unitManager;
    UnitSet m_selectedUnits;
    bool m_dirty = true;

    sf::Text m_name;
    sf::Text m_civilizationName;
    sf::Text m_playerName;

    sf::Text m_hpText;

    sf::RectangleShape m_hpGreenRect;
    sf::RectangleShape m_hpRedRect;

    sf::Texture m_currentIcon;

    std::vector<sf::Texture> m_unitIcons;
    std::vector<sf::Texture> m_buildingIcons;
};

#endif // UNITINFOPANEL_H