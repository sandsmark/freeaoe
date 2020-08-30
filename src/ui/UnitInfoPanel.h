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

#include "render/IRenderTarget.h"
#include "mechanics/IState.h"
#include <algorithm>
#include <array>
#include <memory>
#include <unordered_set>
#include <vector>

#include "core/Types.h"

class IRenderTarget;
class UnitManager;
struct Building;
struct Unit;

typedef std::vector<std::shared_ptr<Unit>> UnitVector;
typedef std::unordered_set<std::shared_ptr<Unit>> UnitSet; // TODO: make this weak_ptr, it only works by accident because UnitManager cleans up in itself

class UnitInfoPanel : public IState
{
public:
    UnitInfoPanel(const std::shared_ptr<IRenderTarget> &renderTarget);

    void setUnitManager(const std::shared_ptr<UnitManager> &unitManager);

    bool init() override;
    bool handleEvent(sf::Event event) override;
    bool update(Time time) override;
    void draw() override;

    ScreenRect rect() const;

private:
    void drawSingleUnit();
    void drawUnitsList();
    void updateUnitsList(const UnitSet &units, const ScreenPos offset);
    void drawConstructionInfo(const std::shared_ptr<Building> &building);

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
        Drawable::Text::Ptr text;
        Drawable::Image::Ptr icon;
    };

    struct Button {
        ScreenRect rect;
        Drawable::Image::Ptr sprite;
        std::shared_ptr<Unit> unit;
    };

    std::vector<Button> m_unitButtons;

    std::array<StatItem, StatItem::TypeCount> m_statItems;

    std::shared_ptr<IRenderTarget> m_renderTarget;
    std::weak_ptr<UnitManager> m_unitManager;
    UnitSet m_selectedUnits;
    bool m_dirty = true;

    Drawable::Text::Ptr m_name;
    Drawable::Text::Ptr m_civilizationName;
    Drawable::Text::Ptr m_playerName;

    Drawable::Text::Ptr m_productionUpperText;
    Drawable::Text::Ptr m_productionBottomText;

    Drawable::Text::Ptr m_hpText;

    Drawable::Rect m_hpGreenRect;
    Drawable::Rect m_hpRedRect;

    Drawable::Image::Ptr m_currentIcon;

    std::vector<Drawable::Image::Ptr> m_unitIcons;
    std::vector<Drawable::Image::Ptr> m_buildingIcons;
    std::vector<Drawable::Image::Ptr> m_researchIcons;

    Drawable::Image::Ptr m_unitHalo;

    std::vector<Drawable::Image::Ptr> m_progressBars;
    int m_buttonSize = 40;
};

#endif // UNITINFOPANEL_H
