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
    if (!m_unitManager.lock()) {
        WARN << "no unit manager set!";
        return false;
    }

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

    genie::SlpFilePtr haloSlp = AssetManager::Inst()->getSlp("unithalo.shp", AssetManager::ResourceType::Interface);
    if (!haloSlp) {
        WARN << "couldn't load halo";
        return false;
    }
    m_unitHalo.loadFromImage(Resource::convertFrameToImage(haloSlp->getFrame(0)));

    // Labels
    m_name.setFont(SfmlRenderTarget::defaultFont());
    m_civilizationName.setFont(SfmlRenderTarget::defaultFont());
    m_playerName.setFont(SfmlRenderTarget::defaultFont());
    m_hpText.setFont(SfmlRenderTarget::defaultFont());

    m_name.setFillColor(sf::Color::Black);
    m_civilizationName.setFillColor(sf::Color::Black);
    m_playerName.setFillColor(sf::Color::Black);
    m_hpText.setFillColor(sf::Color::Black);

    m_name.setCharacterSize(17);
    m_civilizationName.setCharacterSize(15);
    m_playerName.setCharacterSize(15);
    m_hpText.setCharacterSize(12);

    m_name.setPosition(rect().topLeft());


    // HP bar
    m_hpRedRect.setFillColor(sf::Color::Red);
    m_hpGreenRect.setFillColor(sf::Color::Green);

    return true;
}

void UnitInfoPanel::handleEvent(sf::Event event)
{
    if (event.type != sf::Event::MouseButtonPressed) {
        return;
    }

    Unit::Ptr clickedUnit;
    ScreenPos mousePos(event.mouseButton.x, event.mouseButton.y);
    for (const Button &button : m_unitButtons) {
        if (button.rect.contains(mousePos)) {
            clickedUnit = button.unit;
            break;
        }
    }

    if (!clickedUnit) {
        return;
    }

    std::shared_ptr<UnitManager> unitManager = m_unitManager.lock();
    unitManager->setSelectedUnits({clickedUnit});
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
        updateUnitButtons();
        drawMultipleUnits();
    }
}

void UnitInfoPanel::drawSingleUnit()
{
    Unit::Ptr unit = *m_selectedUnits.begin();

    std::shared_ptr<Player> player = unit->player.lock();
    m_civilizationName.setString(player->civ->name());
    m_playerName.setString(player->name);

    m_civilizationName.setPosition(rect().center() - ScreenPos(0, m_civilizationName.getLocalBounds().height + m_playerName.getLocalBounds().height + 10));
    m_playerName.setPosition(rect().center() - ScreenPos(0, m_playerName.getLocalBounds().height));

    m_renderTarget->draw(m_civilizationName);
    m_renderTarget->draw(m_playerName);

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
    m_hpGreenRect.setSize(Size(size.width * unit->hitPoints / unit->data()->HitPoints, size.height));
    m_renderTarget->draw(m_hpRedRect);
    m_renderTarget->draw(m_hpGreenRect);

    m_hpText.setString(std::to_string(int(unit->hitPoints)) + '/' + std::to_string(unit->data()->HitPoints));
    m_hpText.setPosition(rightX, pos.y - m_hpText.getLocalBounds().height * 3 / 4);
    m_renderTarget->draw(m_hpText);

    pos.y += size.height + 5;

    if (unit->data()->GarrisonCapacity) {
        StatItem &item = m_statItems[StatItem::GarrisonCapacity];
        m_renderTarget->draw(item.icon, ScreenPos(pos));
        item.text.setPosition(ScreenPos(rightX, pos.y));
        item.text.setString(std::to_string(unit->garrisonedUnits) + '/' + std::to_string(unit->data()->GarrisonCapacity));
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

void UnitInfoPanel::updateUnitButtons()
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

ScreenRect UnitInfoPanel::rect() const
{
    ScreenRect r;
    r.height = 4 * 45;
    r.width = 10 * 45;
    r.x = 8 * 45;
    r.y = m_renderTarget->getSize().height - r.height - 10;
    return r;
}
