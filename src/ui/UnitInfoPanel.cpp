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
#include "UnitInfoPanel.h"

#include <genie/dat/Unit.h>
#include <genie/dat/ResourceUsage.h>
#include <genie/dat/unit/AttackOrArmor.h>
#include <genie/dat/unit/Combat.h>
#include <genie/resource/SlpFile.h>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <utility>

#include "core/Logger.h"
#include "core/ResourceMap.h"
#include "mechanics/Building.h"
#include "mechanics/Civilization.h"
#include "mechanics/Player.h"
#include "mechanics/Unit.h"
#include "mechanics/UnitManager.h"
#include "resource/AssetManager.h"
#include "resource/LanguageManager.h"
#include "resource/Resource.h"

UnitInfoPanel::UnitInfoPanel(std::shared_ptr<IRenderTarget> renderTarget) :
    m_renderTarget(std::move(renderTarget))
{
}

void UnitInfoPanel::setUnitManager(const std::shared_ptr<UnitManager> &unitManager)
{
    m_unitManager = unitManager;
}


bool UnitInfoPanel::init()
{
    // Stat icons
    genie::SlpFilePtr iconsSlp = AssetManager::Inst()->getSlp("itemicon.shp", AssetManager::ResourceType::Interface);
    if (iconsSlp->getFrameCount() < StatItem::TypeCount) {
        WARN << "not enough icons in SLP:" << iconsSlp->getFrameCount();
        return false;
    }

    for (int i=0; i<StatItem::TypeCount; i++) {

        m_statItems[i].icon = m_renderTarget->convertFrameToImage(iconsSlp->getFrame(i));
        m_statItems[i].text = m_renderTarget->createText();
        m_statItems[i].text->pointSize = 12;
    }

    // TODO: get proper player civ
    const int playerCiv = 0;

    // Unit icons
    genie::SlpFilePtr unitIconsSlp = AssetManager::Inst()->getInterfaceSlp(AssetManager::StandardSlpType::Units, playerCiv);
    REQUIRE(unitIconsSlp, return false);
    m_unitIcons.resize(unitIconsSlp->getFrameCount());
    for (size_t i=0; i<unitIconsSlp->getFrameCount(); i++) {
        m_unitIcons[i] = m_renderTarget->convertFrameToImage(unitIconsSlp->getFrame(i));
    }

    // Building icons
    genie::SlpFilePtr buildingIconsSlp = AssetManager::Inst()->getInterfaceSlp(AssetManager::StandardSlpType::Buildings, playerCiv);
    REQUIRE(buildingIconsSlp, return false);
    m_buildingIcons.resize(buildingIconsSlp->getFrameCount());
    for (size_t i=0; i<buildingIconsSlp->getFrameCount(); i++) {
        m_buildingIcons[i] = m_renderTarget->convertFrameToImage(buildingIconsSlp->getFrame(i));
    }

    // Tech/research icons
    genie::SlpFilePtr techIconsSlp = AssetManager::Inst()->getInterfaceSlp(AssetManager::StandardSlpType::Technology, playerCiv);
    REQUIRE(techIconsSlp, return false);
    m_researchIcons.resize(techIconsSlp->getFrameCount());
    for (size_t i=0; i<techIconsSlp->getFrameCount(); i++) {
        m_researchIcons[i] = m_renderTarget->convertFrameToImage(techIconsSlp->getFrame(i));
    }

    genie::SlpFilePtr haloSlp = AssetManager::Inst()->getSlp("unithalo.shp", AssetManager::ResourceType::Interface);
    if (!haloSlp) {
        WARN << "couldn't load halo";
        return false;
    }
    m_unitHalo = m_renderTarget->convertFrameToImage(haloSlp->getFrame(0));

    // Building icons
    genie::SlpFilePtr progressbarSlp = AssetManager::Inst()->getSlp("sundial.shp", AssetManager::ResourceType::Interface);
    if (!progressbarSlp) {
        WARN << "Failed to load progress bar";
        return false;
    }
    m_progressBars.resize(progressbarSlp->getFrameCount());
    for (size_t i=0; i<progressbarSlp->getFrameCount(); i++) {
        m_progressBars[i] = m_renderTarget->convertFrameToImage(progressbarSlp->getFrame(i));
    }

    // Labels
    m_name = m_renderTarget->createText();
    m_name->pointSize = 17;
    m_name->position = rect().topLeft();

    m_civilizationName = m_renderTarget->createText();
    m_civilizationName->pointSize = 15;

    m_playerName = m_renderTarget->createText();
    m_playerName->pointSize = 15;

    m_hpText = m_renderTarget->createText();
    m_hpText->pointSize = 12;

    m_productionUpperText = m_renderTarget->createText();
    m_productionUpperText->pointSize = 12;

    m_productionBottomText = m_renderTarget->createText();
    m_productionBottomText->pointSize = 12;


    // HP bar
    m_hpRedRect.filled = true;
    m_hpRedRect.fillColor = Drawable::Red;
    m_hpRedRect.borderColor = Drawable::Transparent;
    m_hpGreenRect.filled = true;
    m_hpGreenRect.fillColor = Drawable::Green;
    m_hpGreenRect.borderColor = Drawable::Transparent;

    return true;
}

bool UnitInfoPanel::handleEvent(sf::Event event)
{
    if (event.type != sf::Event::MouseButtonPressed) {
        return false;
    }

    if (m_selectedUnits.empty()) {
        return false;
    }

    ScreenPos mousePos(event.mouseButton.x, event.mouseButton.y);
    if (!rect().contains(mousePos)) {
        return false;
    }


    int clickedButton = -1;
    for (size_t i=0; i<m_unitButtons.size(); i++) {
        const Button &button = m_unitButtons[i];
        if (button.rect.contains(mousePos)) {
            clickedButton = i;
            break;
        }
    }

    if (clickedButton < 0) {
        return false;
    }

    DBG << "clicked" << clickedButton;

    Unit::Ptr singleUnit;
    if (m_selectedUnits.size() == 1) {
        singleUnit = *m_selectedUnits.begin();
    }

    Building::Ptr building = Building::fromUnit(singleUnit);
    if (building && building->isProducing()) {
        building->abortProduction(clickedButton);
        return true;
    }

    Unit::Ptr clickedUnit = m_unitButtons[clickedButton].unit;

    if (building && !building->garrisonedUnits.empty()) {
        if (building->ungarrison(clickedUnit)) {
            return true;
        }
    }

    std::shared_ptr<UnitManager> unitManager = m_unitManager.lock();
    unitManager->setSelectedUnits({clickedUnit});

    return true;
}

bool UnitInfoPanel::update(Time /*time*/)
{
    // TODO don't do this every update
    if (m_renderTarget->getSize().height >= 1024) {
        m_buttonSize = 45;
    } else {
        m_buttonSize = 40;
    }

    std::shared_ptr<UnitManager> unitManager = m_unitManager.lock();
    if (!unitManager) {
        WARN << "Unit manager went away?";
        return false;
    }

    if (unitManager->selected().units != m_selectedUnits) {
        m_selectedUnits = unitManager->selected().units;

        m_dirty = true;
    }

    if (m_dirty) {
        m_dirty = false;
        return true;
    }

    return false;
}

void UnitInfoPanel::draw()
{
    if (m_selectedUnits.empty()) {
        return;
    }

    m_unitButtons.clear();

    if (m_selectedUnits.size() == 1) {
        drawSingleUnit();
        return;
    }

    if (!m_selectedUnits.empty()) {
        updateUnitsList(m_selectedUnits, ScreenPos(2, 2));
        drawUnitsList();
    }
}

void UnitInfoPanel::drawSingleUnit()
{
    Unit::Ptr unit = *m_selectedUnits.begin();
    if (!unit) {
        WARN << "No selected units??";
        return;
    }

    REQUIRE(unit->data(), WARN << "Unit" << unit->debugName << "missing data"; return);
    REQUIRE(m_name, return);

    if (!unit->data()) {
        WARN << "Unit" << unit->debugName << "missing data";
        return;
    }

    ScreenPos pos = rect().topLeft();
    m_name->string = LanguageManager::getString(unit->data()->LanguageDLLName);
    m_name->position = pos;
    m_renderTarget->draw(m_name);
    pos.y += m_name->size().height + 5;

    const int16_t iconId = unit->data()->IconID;
    if (iconId < 0) {
        return;
    }

    // "Halo" behind the unit, basically a picture frame
    m_renderTarget->draw(m_unitHalo, pos);
    pos.x += 2;
    pos.y += 2;

    // Draw the correct icon
    Size size;
    if (unit->data()->Type == genie::Unit::BuildingType) {
        if (iconId > int16_t(m_buildingIcons.size())) {
            WARN << "out of bounds building icon" << iconId;
            return;
        }

        m_renderTarget->draw(m_buildingIcons[iconId], pos);
        size = m_buildingIcons[iconId]->size;
    } else {
        if (iconId > int16_t(m_unitIcons.size())) {
            WARN << "out of bounds unit icon" << iconId;
            return;
        }

        m_renderTarget->draw(m_unitIcons[iconId], pos);
        size = m_unitIcons[iconId]->size;
    }

    pos.y += size.height + 2;

    int rightX = pos.x + size.width + 2;

    // Hitpoints indicator
    m_hpRedRect.rect.setTopLeft(pos);
    m_hpGreenRect.rect.setTopLeft(pos);
    size.height = 5;
    m_hpRedRect.rect.setSize(size);
    m_hpGreenRect.rect.setSize(Size(size.width * unit->healthLeft(), size.height));
    m_renderTarget->draw(m_hpRedRect);
    m_renderTarget->draw(m_hpGreenRect);

    m_hpText->string = std::to_string(int(unit->hitpointsLeft())) + '/' + std::to_string(unit->data()->HitPoints);
    m_hpText->position = ScreenPos(rightX, pos.y - m_hpText->size().height * 3 / 4);
    m_renderTarget->draw(m_hpText);

    pos.y += size.height + 5;

    // Render garrisoned and garrison capacity
    if (unit->isBuilding() && unit->data()->GarrisonCapacity) {
        Building::Ptr building = Building::fromUnit(unit);
        StatItem &item = m_statItems[StatItem::GarrisonCapacity];
        m_renderTarget->draw(item.icon, ScreenPos(pos));
        item.text->position = ScreenPos(rightX, pos.y);
        item.text->string = std::to_string(building->garrisonedUnits.size()) + '/' + std::to_string(unit->data()->GarrisonCapacity);
        m_renderTarget->draw(item.text);
        pos.y += item.icon->size.height + 5;
    }

    // Look up the different attack types
    int16_t meleeAttack = 0;
    int16_t pierceAttack = 0;
    for (const genie::unit::AttackOrArmor &armor : unit->data()->Combat.Attacks) {
        if (armor.Class == genie::unit::AttackOrArmor::BasePierce) {
            pierceAttack = armor.Amount;
        }
        if (armor.Class == genie::unit::AttackOrArmor::BaseMelee) {
            meleeAttack = armor.Amount;
        }
    }

    // Render attack types
    if (meleeAttack || pierceAttack) {
        StatItem &item = m_statItems[StatItem::Damage];
        m_renderTarget->draw(item.icon, ScreenPos(pos));
        item.text->position = ScreenPos(rightX, pos.y);
        item.text->string = std::to_string(std::max(pierceAttack, meleeAttack));
        m_renderTarget->draw(item.text);
        pos.y += item.icon->size.height + 5;
    }

    // Render armors
    if (unit->data()->Type < genie::Unit::BuildingType) {
        int16_t meleeArmor = 0;
        int16_t pierceArmor = 0;
        for (const genie::unit::AttackOrArmor &armor : unit->data()->Combat.Armours) {
            if (armor.Class == genie::unit::AttackOrArmor::BasePierce) {
                pierceArmor = armor.Amount;
            }
            if (armor.Class == genie::unit::AttackOrArmor::BaseMelee) {
                meleeArmor = armor.Amount;
            }
        }

        if (meleeArmor || pierceArmor) {
            StatItem &item = m_statItems[StatItem::Armor];
            m_renderTarget->draw(item.icon, ScreenPos(pos));
            item.text->position = ScreenPos(rightX, pos.y);
            item.text->string = std::to_string(meleeArmor) + '/' + std::to_string(pierceArmor);
            m_renderTarget->draw(item.text);

            pos.y += item.icon->size.height + 5;
        }
    }

    // Render attack range
    if (unit->data()->Combat.MaxRange > 0) {
        StatItem &item = m_statItems[StatItem::AttackRange];
        m_renderTarget->draw(item.icon, ScreenPos(pos));
        item.text->position = ScreenPos(rightX, pos.y);
        item.text->string = std::to_string(int(unit->data()->Combat.MaxRange));
        m_renderTarget->draw(item.text);

        pos.y += item.icon->size.height + 5;
    }

    // Render resource storages
    if (unit->resources[genie::ResourceType::WoodStorage] > 0) {
        StatItem &item = m_statItems[StatItem::CarryingWoodAmount];
        m_renderTarget->draw(item.icon, ScreenPos(pos));
        item.text->position = ScreenPos(rightX, pos.y);
        item.text->string = std::to_string(int(unit->resources[genie::ResourceType::WoodStorage] ));
        m_renderTarget->draw(item.text);

        pos.y += item.icon->size.height + 5;
    }

    if (unit->resources[genie::ResourceType::StoneStorage] > 0) {
        StatItem &item = m_statItems[StatItem::CarryingStoneAmount];
        m_renderTarget->draw(item.icon, ScreenPos(pos));
        item.text->position = ScreenPos(rightX, pos.y);
        item.text->string = std::to_string(int(unit->resources[genie::ResourceType::StoneStorage]));
        m_renderTarget->draw(item.text);

        pos.y += item.icon->size.height + 5;
    }

    if (unit->resources[genie::ResourceType::FoodStorage] > 0) {
        StatItem &item = m_statItems[StatItem::CarryingFoodAmount];
        m_renderTarget->draw(item.icon, ScreenPos(pos));
        item.text->position = ScreenPos(rightX, pos.y);
        item.text->string = std::to_string(int(unit->resources[genie::ResourceType::FoodStorage]));
        m_renderTarget->draw(item.text);

        pos.y += item.icon->size.height + 5;
    }

    if (unit->resources[genie::ResourceType::GoldStorage] > 0) {
        StatItem &item = m_statItems[StatItem::CarryingGoldAmount];
        m_renderTarget->draw(item.icon, ScreenPos(pos));
        item.text->position = ScreenPos(rightX, pos.y);
        item.text->string = std::to_string(int(unit->resources[genie::ResourceType::GoldStorage]));
        m_renderTarget->draw(item.text);

        pos.y += item.icon->size.height + 5;
    }


    // Render player name and civ, only if building is not producing and don't have any units garrisoned
    Building::Ptr building = Building::fromUnit(unit);
    if (!building || (!building->isProducing() && building->garrisonedUnits.empty())) {
        std::shared_ptr<Player> player = unit->player().lock();
        if (!player) {
            WARN << "Unit missing player";
            return;
        }

        m_civilizationName->string = player->civilization.name();
        m_playerName->string = player->name;

        m_civilizationName->position = (rect().center() - ScreenPos(0, m_civilizationName->size().height + m_playerName->size().height + 10));
        m_playerName->position = (rect().center() - ScreenPos(0, m_playerName->size().height));

        m_renderTarget->draw(m_civilizationName);
        m_renderTarget->draw(m_playerName);


        return;
    }

    // Draw production and production queue
    if (building->isProducing()) {
        drawConstructionInfo(building);
    }

    // Render garrisoned units
    UnitSet garrisoned;
    for (const std::weak_ptr<Unit> &garrisonedWeak : building->garrisonedUnits) {
        Unit::Ptr garrisonedUnit = garrisonedWeak.lock();
        if (!garrisonedUnit) {
            WARN << "Expired unit garrisoned in" << building->debugName;
            continue;
        }
        garrisoned.add(garrisonedUnit);
    }

    if (!garrisoned.isEmpty()) {
        updateUnitsList(garrisoned.units, ScreenPos(100, 2)); // a bit arbitrary
        drawUnitsList();
    }
}

void UnitInfoPanel::drawUnitsList()
{
    // TODO refactor into common function
    Drawable::Rect bevelRect;

    for (const Button &button : m_unitButtons) {
        bevelRect.fillColor = Drawable::Color(192, 192, 192);
        bevelRect.rect.setTopLeft(button.rect.x - 2, button.rect.y - 2);
        bevelRect.rect.setSize(Size(button.rect.width + 2, button.rect.width + 2));
        m_renderTarget->draw(bevelRect);

        bevelRect.fillColor = Drawable::Color(64, 64, 64);
        bevelRect.rect.setTopLeft(button.rect.x + 0, button.rect.y + 0);
        bevelRect.rect.setSize(Size(button.rect.width, button.rect.width));
        m_renderTarget->draw(bevelRect);

        m_renderTarget->draw(button.sprite, button.rect.topLeft());
    }

}

void UnitInfoPanel::updateUnitsList(const UnitVector &units, const ScreenPos offset)
{
    const int maxVertical = 3;
    Size iconSize;
    iconSize.height = rect().height / maxVertical;
    const int maxHorizontal = rect().width / iconSize.height;


    int unitCount = units.size();
    if (unitCount >= maxVertical * maxHorizontal) {
        iconSize.width = iconSize.height - (unitCount - maxVertical * maxHorizontal) / 3.f;
    } else {
        iconSize.width = iconSize.height;
    }
    iconSize.width = std::min(iconSize.width, 38.f);

    ScreenPos pos = rect().topLeft() + offset;
    for (const Unit::Ptr &unit : units) {
        const int16_t iconId = unit->data()->IconID;
        if (iconId < 0) {
            WARN << "invalid unit id";
            continue;
        }
        Button button;
        if (unit->data()->Type == genie::Unit::BuildingType) {
            if (iconId >= int16_t(m_buildingIcons.size())) {
                WARN << "out of bounds building icon" << iconId;
                continue;
            }

            button.sprite = m_buildingIcons[iconId];
        } else {
            if (iconId >= int16_t(m_unitIcons.size())) {
                WARN << "out of bounds unit icon" << iconId;
                continue;
            }

            button.sprite = m_unitIcons[iconId];
        }

        button.rect = ScreenRect(pos, iconSize);
        button.unit = unit;

        m_unitButtons.push_back(std::move(button));

        pos.x += iconSize.width + 2;
        if (pos.x + iconSize.width > rect().bottomRight().x) {
            pos.x = rect().topLeft().x + 2;
            pos.y += iconSize.height + 2;
        }
    }
}

void UnitInfoPanel::drawConstructionInfo(const std::shared_ptr<Building> &building)
{
    m_unitButtons.clear();

    const Drawable::Image::Ptr &icon = building->isResearching() ? m_researchIcons.at(building->productIcon(0)) : m_unitIcons.at(building->productIcon(0));
    const Size iconSize = icon->size;
    ScreenPos pos = rect().center();
    pos.x -= iconSize.width;
    pos.y -= iconSize.height/2;

    Button button;
    button.sprite = icon;
    button.rect = ScreenRect(pos, iconSize);
    m_unitButtons.push_back(std::move(button));

    pos.x += iconSize.width + 2;
    pos.y -= 4;
    m_productionUpperText->position = pos;
    if (building->isResearching()) {
        m_productionUpperText->string = "Researching - " + std::to_string(int(building->productionProgress() * 100)) + "%";
    } else {
        m_productionUpperText->string = "Building - " + std::to_string(int(building->productionProgress() * 100)) + "%";
    }
    m_renderTarget->draw(m_productionUpperText);

    pos.y += m_productionUpperText->size().height;
    m_productionBottomText->position = pos;
    m_productionBottomText->string = building->currentProductName();
    m_renderTarget->draw(m_productionBottomText);

    // To get the width of the progress bar
    pos.y += m_productionBottomText->size().height + 4;
    const size_t currentProgressBar = m_progressBars.size() * building->productionProgress();
    m_renderTarget->draw(m_progressBars[currentProgressBar], pos);
//    DBG << building->productionProgress();

    pos.x = rect().center().x - iconSize.width;
    pos.y = rect().center().y + iconSize.height / 2 + 4;
    for (size_t i = 1; i<building->productionQueueLength(); i++) {
        const Drawable::Image::Ptr &productIcon = m_unitIcons.at(building->productIcon(i));
        const Size productIconSize = productIcon->size;

        Button productButton;
        productButton.sprite = productIcon;
        productButton.rect = ScreenRect(pos, productIconSize);
        m_unitButtons.push_back(std::move(productButton));

        pos.x += productIconSize.width;
    }

    drawUnitsList();
}

ScreenRect UnitInfoPanel::rect() const
{
    ScreenRect r;
    r.height = 4 * m_buttonSize;
    r.width = 10 * m_buttonSize;
    r.x = 8 * m_buttonSize;
    r.y = m_renderTarget->getSize().height - r.height;
    return r;
}
