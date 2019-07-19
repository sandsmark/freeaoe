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

#include "mechanics/UnitManager.h"
#include "mechanics/Entity.h"
#include "render/SfmlRenderTarget.h"
#include "resource/LanguageManager.h"
#include "mechanics/Player.h"
#include "mechanics/Civilization.h"
#include "mechanics/Building.h"

#include <genie/dat/Unit.h>
#include <genie/resource/SlpFile.h>

UnitInfoPanel::UnitInfoPanel(const std::shared_ptr<SfmlRenderTarget> &renderTarget) :
    m_renderTarget(renderTarget)
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
        m_statItems[i].icon.loadFromImage(Resource::convertFrameToImage(iconsSlp->getFrame(i)));
        m_statItems[i].text.setFont(SfmlRenderTarget::defaultFont());
        m_statItems[i].text.setFillColor(sf::Color::Black);
        m_statItems[i].text.setCharacterSize(12);
    }

    // Unit icons
    genie::SlpFilePtr unitIconsSlp = AssetManager::Inst()->getSlp("btnunit.shp", AssetManager::ResourceType::Interface);
    if (!unitIconsSlp) {
        WARN << "Failed to load unit icons";
        return false;
    }
    m_unitIcons.resize(unitIconsSlp->getFrameCount());
    for (size_t i=0; i<unitIconsSlp->getFrameCount(); i++) {
        m_unitIcons[i].loadFromImage(Resource::convertFrameToImage(unitIconsSlp->getFrame(i)));
    }

    // Building icons
    genie::SlpFilePtr buildingIconsSlp = AssetManager::Inst()->getSlp("ico_bld2.shp", AssetManager::ResourceType::Interface);
    if (!buildingIconsSlp) {
        WARN << "Failed to load building icons";
        return false;
    }
    m_buildingIcons.resize(buildingIconsSlp->getFrameCount());
    for (size_t i=0; i<buildingIconsSlp->getFrameCount(); i++) {
        m_buildingIcons[i].loadFromImage(Resource::convertFrameToImage(buildingIconsSlp->getFrame(i)));
    }

    // Tech/research icons
    genie::SlpFilePtr techIconsSlp = AssetManager::Inst()->getSlp("btntech.shp", AssetManager::ResourceType::Interface);
    if (!techIconsSlp) {
        WARN << "Failed to load research icons";
        return false;
    }
    m_researchIcons.resize(techIconsSlp->getFrameCount());
    for (size_t i=0; i<techIconsSlp->getFrameCount(); i++) {
        m_researchIcons[i].loadFromImage(Resource::convertFrameToImage(techIconsSlp->getFrame(i)));
    }

    genie::SlpFilePtr haloSlp = AssetManager::Inst()->getSlp("unithalo.shp", AssetManager::ResourceType::Interface);
    if (!haloSlp) {
        WARN << "couldn't load halo";
        return false;
    }
    m_unitHalo.loadFromImage(Resource::convertFrameToImage(haloSlp->getFrame(0)));

    // Building icons
    genie::SlpFilePtr progressbarSlp = AssetManager::Inst()->getSlp("sundial.shp", AssetManager::ResourceType::Interface);
    if (!progressbarSlp) {
        WARN << "Failed to load progress bar";
        return false;
    }
    m_progressBars.resize(progressbarSlp->getFrameCount());
    for (size_t i=0; i<progressbarSlp->getFrameCount(); i++) {
        m_progressBars[i].loadFromImage(Resource::convertFrameToImage(progressbarSlp->getFrame(i)));
    }

    // Labels
    m_name.setFont(SfmlRenderTarget::defaultFont());
    m_civilizationName.setFont(SfmlRenderTarget::defaultFont());
    m_playerName.setFont(SfmlRenderTarget::defaultFont());
    m_hpText.setFont(SfmlRenderTarget::defaultFont());
    m_productionUpperText.setFont(SfmlRenderTarget::defaultFont());
    m_productionBottomText.setFont(SfmlRenderTarget::defaultFont());

    m_name.setFillColor(sf::Color::Black);
    m_civilizationName.setFillColor(sf::Color::Black);
    m_playerName.setFillColor(sf::Color::Black);
    m_hpText.setFillColor(sf::Color::Black);
    m_productionUpperText.setFillColor(sf::Color::Black);
    m_productionBottomText.setFillColor(sf::Color::Black);

    m_name.setCharacterSize(17);
    m_civilizationName.setCharacterSize(15);
    m_playerName.setCharacterSize(15);
    m_hpText.setCharacterSize(12);
    m_productionUpperText.setCharacterSize(12);
    m_productionBottomText.setCharacterSize(12);

    m_name.setPosition(rect().topLeft());


    // HP bar
    m_hpRedRect.setFillColor(sf::Color::Red);
    m_hpGreenRect.setFillColor(sf::Color::Green);

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

    Unit::Ptr clickedUnit;

    if (m_selectedUnits.size() == 1) {
        clickedUnit = *m_selectedUnits.begin();
    }
    Building::Ptr building = Unit::asBuilding(clickedUnit);
    if (building && building->isProducing()) {
        building->abortProduction(clickedButton);
        return true;
    }

    clickedUnit = m_unitButtons[clickedButton].unit;
    std::shared_ptr<UnitManager> unitManager = m_unitManager.lock();
    unitManager->setSelectedUnits({clickedUnit});

    return true;
}

bool UnitInfoPanel::update(Time /*time*/)
{
    std::shared_ptr<UnitManager> unitManager = m_unitManager.lock();
    if (!unitManager) {
        WARN << "Unit manager went away?";
        return false;
    }

    if (unitManager->selected() != m_selectedUnits) {
        m_selectedUnits = unitManager->selected();

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
    } else {
        updateSelectedUnitButtons();
        drawMultipleUnits();
    }
}

void UnitInfoPanel::drawSingleUnit()
{
    Unit::Ptr unit = *m_selectedUnits.begin();

    Building::Ptr building = Unit::asBuilding(unit);
    if (building && building->isProducing()) {
        drawConstructionInfo(building);
    } else {
        std::shared_ptr<Player> player = unit->player.lock();
        m_civilizationName.setString(player->civilization.name());
        m_playerName.setString(player->name);

        m_civilizationName.setPosition(rect().center() - ScreenPos(0, m_civilizationName.getLocalBounds().height + m_playerName.getLocalBounds().height + 10));
        m_playerName.setPosition(rect().center() - ScreenPos(0, m_playerName.getLocalBounds().height));

        m_renderTarget->draw(m_civilizationName);
        m_renderTarget->draw(m_playerName);
    }

    ScreenPos pos = rect().topLeft();
    m_name.setString(LanguageManager::getString(unit->data()->LanguageDLLName));
    m_name.setPosition(pos);
    m_renderTarget->draw(m_name);
    pos.y += m_name.getLocalBounds().height +  m_name.getLocalBounds().top + 5;

    const int16_t iconId = unit->data()->IconID;
    if (iconId < 0) {
        return;
    }

    m_renderTarget->draw(m_unitHalo, pos);
    pos.x += 2;
    pos.y += 2;

    Size size;
    if (unit->data()->Type == genie::Unit::BuildingType) {
        if (iconId > m_buildingIcons.size()) {
            WARN << "out of bounds building icon" << iconId;
            return;
        }

        m_renderTarget->draw(m_buildingIcons[iconId], pos);
        size = Size(m_buildingIcons[iconId].getSize());
    } else {
        if (iconId > m_unitIcons.size()) {
            WARN << "out of bounds unit icon" << iconId;
            return;
        }

        m_renderTarget->draw(m_unitIcons[iconId], pos);
        size = Size(m_unitIcons[iconId].getSize());
    }

    pos.y += size.height + 2;

    int rightX = pos.x + size.width + 2;

    // Hitpoints indicator
    m_hpRedRect.setPosition(pos);
    m_hpGreenRect.setPosition(pos);
    size.height = 5;
    m_hpRedRect.setSize(size);
    m_hpGreenRect.setSize(Size(size.width * unit->healthLeft(), size.height));
    m_renderTarget->draw(m_hpRedRect);
    m_renderTarget->draw(m_hpGreenRect);

    m_hpText.setString(std::to_string(int(unit->hitpointsLeft())) + '/' + std::to_string(unit->data()->HitPoints));
    m_hpText.setPosition(rightX, pos.y - m_hpText.getLocalBounds().height * 3 / 4);
    m_renderTarget->draw(m_hpText);

    pos.y += size.height + 5;

    if (unit->isBuilding() && unit->data()->GarrisonCapacity) {
        Building::Ptr building = Unit::asBuilding(unit);
        StatItem &item = m_statItems[StatItem::GarrisonCapacity];
        m_renderTarget->draw(item.icon, ScreenPos(pos));
        item.text.setPosition(ScreenPos(rightX, pos.y));
        item.text.setString(std::to_string(building->garrisonedUnits) + '/' + std::to_string(unit->data()->GarrisonCapacity));
        m_renderTarget->draw(item.text);
        pos.y += item.icon.getSize().y + 5;
    }


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

    if (meleeAttack || pierceAttack) {
        StatItem &item = m_statItems[StatItem::Damage];
        m_renderTarget->draw(item.icon, ScreenPos(pos));
        item.text.setPosition(ScreenPos(rightX, pos.y));
        item.text.setString(std::to_string(std::max(pierceAttack, meleeAttack)));
        m_renderTarget->draw(item.text);
        pos.y += item.icon.getSize().y + 5;
    }

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
            item.text.setPosition(ScreenPos(rightX, pos.y));
            item.text.setString(std::to_string(meleeArmor) + '/' + std::to_string(pierceArmor));
            m_renderTarget->draw(item.text);

            pos.y += item.icon.getSize().y + 5;
        }
    }

    if (unit->data()->Combat.MaxRange > 0) {
        StatItem &item = m_statItems[StatItem::AttackRange];
        m_renderTarget->draw(item.icon, ScreenPos(pos));
        item.text.setPosition(ScreenPos(rightX, pos.y));
        item.text.setString(std::to_string(int(unit->data()->Combat.MaxRange)));
        m_renderTarget->draw(item.text);

        pos.y += item.icon.getSize().y + 5;
    }

    if (unit->resources[genie::ResourceType::WoodStorage] > 0) {
        StatItem &item = m_statItems[StatItem::CarryingWoodAmount];
        m_renderTarget->draw(item.icon, ScreenPos(pos));
        item.text.setPosition(ScreenPos(rightX, pos.y));
        item.text.setString(std::to_string(int(unit->resources[genie::ResourceType::WoodStorage] )));
        m_renderTarget->draw(item.text);

        pos.y += item.icon.getSize().y + 5;
    }

    if (unit->resources[genie::ResourceType::StoneStorage] > 0) {
        StatItem &item = m_statItems[StatItem::CarryingStoneAmount];
        m_renderTarget->draw(item.icon, ScreenPos(pos));
        item.text.setPosition(ScreenPos(rightX, pos.y));
        item.text.setString(std::to_string(int(unit->resources[genie::ResourceType::StoneStorage])));
        m_renderTarget->draw(item.text);

        pos.y += item.icon.getSize().y + 5;
    }

    if (unit->resources[genie::ResourceType::FoodStorage] > 0) {
        StatItem &item = m_statItems[StatItem::CarryingFoodAmount];
        m_renderTarget->draw(item.icon, ScreenPos(pos));
        item.text.setPosition(ScreenPos(rightX, pos.y));
        item.text.setString(std::to_string(int(unit->resources[genie::ResourceType::FoodStorage])));
        m_renderTarget->draw(item.text);

        pos.y += item.icon.getSize().y + 5;
    }

    if (unit->resources[genie::ResourceType::GoldStorage] > 0) {
        StatItem &item = m_statItems[StatItem::CarryingGoldAmount];
        m_renderTarget->draw(item.icon, ScreenPos(pos));
        item.text.setPosition(ScreenPos(rightX, pos.y));
        item.text.setString(std::to_string(int(unit->resources[genie::ResourceType::GoldStorage])));
        m_renderTarget->draw(item.text);

        pos.y += item.icon.getSize().y + 5;
    }
}

void UnitInfoPanel::drawMultipleUnits()
{
    // TODO refactor into common function
    sf::RectangleShape bevelRect;

    for (const Button &button : m_unitButtons) {
        bevelRect.setFillColor(sf::Color(192, 192, 192));
        bevelRect.setPosition(button.rect.x - 2, button.rect.y - 2);
        bevelRect.setSize(Size(button.rect.width + 2, button.rect.width + 2));
        m_renderTarget->draw(bevelRect);

        bevelRect.setFillColor(sf::Color(64, 64, 64));
        bevelRect.setPosition(button.rect.x + 0, button.rect.y + 0);
        bevelRect.setSize(Size(button.rect.width, button.rect.width));
        m_renderTarget->draw(bevelRect);

        m_renderTarget->draw(button.sprite);
    }

}

void UnitInfoPanel::updateSelectedUnitButtons()
{
    const int maxVertical = 3;
    Size iconSize;
    iconSize.height = rect().height / maxVertical;
    const int maxHorizontal = rect().width / iconSize.height;


    int unitCount = m_selectedUnits.size();
    if (unitCount >= maxVertical * maxHorizontal) {
        iconSize.width = iconSize.height - (unitCount - maxVertical * maxHorizontal) / 3;
    } else {
        iconSize.width = iconSize.height;
    }
    iconSize.width = std::min(iconSize.width, 38.f);


    ScreenPos pos = rect().topLeft() + ScreenPos(2, 2);
    for (const Unit::Ptr &unit : m_selectedUnits) {
        const int16_t iconId = unit->data()->IconID;
        if (iconId < 0) {
            WARN << "invalid unit id";
            continue;
        }
        Button button;
        if (unit->data()->Type == genie::Unit::BuildingType) {
            if (iconId > m_buildingIcons.size()) {
                WARN << "out of bounds building icon" << iconId;
                continue;
            }

            button.sprite.setTexture(m_buildingIcons[iconId]);
        } else {
            if (iconId > m_unitIcons.size()) {
                WARN << "out of bounds unit icon" << iconId;
                continue;
            }

            button.sprite.setTexture(m_unitIcons[iconId]);
        }

        button.sprite.setPosition(pos);
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

    const sf::Texture &icon = building->isResearching() ? m_researchIcons.at(building->productIcon(0)) : m_unitIcons.at(building->productIcon(0));
    const Size iconSize = icon.getSize();
    ScreenPos pos = rect().center();
    pos.x -= iconSize.width;
    pos.y -= iconSize.height/2;

    Button button;
    button.sprite.setTexture(icon);
    button.sprite.setPosition(pos);
    button.rect = ScreenRect(pos, iconSize);
    m_unitButtons.push_back(std::move(button));

    pos.x += iconSize.width + 2;
    pos.y -= 4;
    m_productionUpperText.setPosition(pos);
    if (building->isResearching()) {
        m_productionUpperText.setString("Researching - " + std::to_string(int(building->productionProgress() * 100)) + "%");
    } else {
        m_productionUpperText.setString("Building - " + std::to_string(int(building->productionProgress() * 100)) + "%");
    }
    m_renderTarget->draw(m_productionUpperText);

    pos.y += m_productionUpperText.getLocalBounds().height;
    m_productionBottomText.setPosition(pos);
    m_productionBottomText.setString(building->currentProductName());
    m_renderTarget->draw(m_productionBottomText);

    // To get the width of the progress bar
    pos.y += m_productionBottomText.getLocalBounds().height + 4;
    const size_t currentProgressBar = m_progressBars.size() * building->productionProgress();
    m_renderTarget->draw(m_progressBars[currentProgressBar], pos);
//    DBG << building->productionProgress();

    pos.x = rect().center().x - iconSize.width;
    pos.y = rect().center().y + iconSize.height / 2 + 4;
    for (size_t i = 1; i<building->productionQueueLength(); i++) {
        const sf::Texture &icon = m_unitIcons.at(building->productIcon(i));
        const Size iconSize = icon.getSize();

        Button button;
        button.sprite.setTexture(icon);
        button.sprite.setPosition(pos);
        button.rect = ScreenRect(pos, iconSize);
        m_unitButtons.push_back(std::move(button));

        pos.x += iconSize.width;
    }

    drawMultipleUnits();
}

ScreenRect UnitInfoPanel::rect() const
{
    ScreenRect r;
    r.height = 4 * 45;
    r.width = 10 * 45;
    r.x = 8 * 45;
    r.y = m_renderTarget->getSize().height - r.height - 10;
    return r;
}
