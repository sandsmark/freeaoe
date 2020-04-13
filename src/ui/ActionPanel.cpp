#include "ActionPanel.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <genie/dat/Research.h>
#include <genie/dat/Unit.h>

#include <genie/dat/Unit.h>
#include <genie/resource/SlpFile.h>
#include <stddef.h>
#include <stdint.h>
#include <algorithm>

#include "actions/IAction.h"
#include "core/Logger.h"
#include "mechanics/Civilization.h"
#include "mechanics/Player.h"
#include "mechanics/Unit.h"
#include "mechanics/UnitManager.h"
#include "render/SfmlRenderTarget.h"
#include "resource/AssetManager.h"
#include "resource/LanguageManager.h"
#include "resource/Resource.h"

ActionPanel::ActionPanel(const std::shared_ptr<SfmlRenderTarget> &renderTarget) :
    m_renderTarget(renderTarget)
{
}


bool ActionPanel::init()
{
    genie::SlpFilePtr unitIconsSlp = AssetManager::Inst()->getSlp("btnunit.shp", AssetManager::ResourceType::Interface);
    if (!unitIconsSlp) {
        WARN << "Failed to load unit icons";
        return false;
    }
    for (size_t i=0; i<unitIconsSlp->getFrameCount(); i++) {
        m_unitIcons[i].loadFromImage(Resource::convertFrameToImage(unitIconsSlp->getFrame(i)));
    }

    // ico_bld1-4.shp looks identical, for some reason
    genie::SlpFilePtr buildingIconsSlp = AssetManager::Inst()->getSlp("ico_bld2.shp", AssetManager::ResourceType::Interface);
    if (!buildingIconsSlp) {
        WARN << "Failed to load building icons";
        return false;
    }
    for (size_t i=0; i<buildingIconsSlp->getFrameCount(); i++) {
        m_buildingIcons[i].loadFromImage(Resource::convertFrameToImage(buildingIconsSlp->getFrame(i)));
    }

    genie::SlpFilePtr researchIconsSlp = AssetManager::Inst()->getSlp("btntech.shp", AssetManager::ResourceType::Interface);
    if (!researchIconsSlp) {
        WARN << "Failed to load research icons";
        return false;
    }
    for (size_t i=0; i<researchIconsSlp->getFrameCount(); i++) {
        m_researchIcons[i].loadFromImage(Resource::convertFrameToImage(researchIconsSlp->getFrame(i)));
    }

    genie::SlpFilePtr commandIconsSlp = AssetManager::Inst()->getSlp("btncmd.shp", AssetManager::ResourceType::Interface);
    if (!commandIconsSlp) {
        WARN << "Failed to load action icons";
        return false;
    }
    for (size_t i=0; i<int(Command::IconCount); i++) {
        if (i >= commandIconsSlp->getFrameCount()) {
            WARN << "icon out of range " << i;
            return false;
        }
        m_commandIcons[Command(i)].loadFromImage(Resource::convertFrameToImage(commandIconsSlp->getFrame(i)));
    }

    { // hax
        sf::Image prevImage = Resource::convertFrameToImage(commandIconsSlp->getFrame(int(Command::NextPage)));
        prevImage.flipHorizontally();
        m_commandIcons[Command::PreviousPage].loadFromImage(prevImage);
    }

    { // can't find this icon anywhere else
        genie::SlpFilePtr cursorsSlp = AssetManager::Inst()->getSlp("mcursors.shp", AssetManager::ResourceType::Interface);
        if (!cursorsSlp) {
            WARN << "Failed to load cursors";
            return false;
        }
        sf::Image garrisonIcon = Resource::convertFrameToImage(cursorsSlp->getFrame(13));
        m_commandIcons[Command::Garrison].loadFromImage(garrisonIcon);
    }

    return true;
}

bool ActionPanel::handleEvent(sf::Event event)
{
    if (event.type != sf::Event::MouseButtonPressed && event.type != sf::Event::MouseButtonReleased) {
        return false;
    }
    ScreenPos mousePos(event.mouseButton.x, event.mouseButton.y);
    if (!rect().contains(mousePos)) {
        releaseButtons();
        return false;
    }

    for (InterfaceButton &button : currentButtons) {
        if (button.interfacePage != m_currentPage) {
            continue;
        }

        if (!buttonRect(button.index).contains(mousePos)) {
            if (button.pressed) {
                m_dirty = true;
            }

            button.pressed = false;
            continue;
        }
        if (button.type == InterfaceButton::AttackStance) {
            if (event.type == sf::Event::MouseButtonPressed) {
                handleButtonClick(button);
            }

            break;
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (button.pressed) {
                m_dirty = true;
            }
            button.pressed = true;
        } else {
            if (button.pressed) {
                m_dirty = true;
                handleButtonClick(button);
            }
            button.pressed = false;
        }
        break;
    }

    return true;
}

bool ActionPanel::update(Time /*time*/)
{
    if (m_unitManager->selected() != m_selectedUnits) {
        m_selectedUnits = m_unitManager->selected();
        updateButtons();
        m_dirty = true;
    }

    if (m_dirty) {
        m_dirty = false;
        return true;
    }

    return false;
}

void ActionPanel::draw()
{
    for (const InterfaceButton &button : currentButtons) {
        if (button.interfacePage != m_currentPage) {
            continue;
        }

        if (button.showBorder) {
            sf::RectangleShape bevelRect(Size(40, 40));
            sf::RectangleShape shadowRect(Size(38, 38));

            // need this because the garrison icon is actually a cursor
            sf::RectangleShape backgroundRect(Size(36, 36));
            backgroundRect.setFillColor(sf::Color::Black);

            bevelRect.setPosition(buttonPosition(button.index) - ScreenPos(2, 2));
            shadowRect.setPosition(buttonPosition(button.index));
            backgroundRect.setPosition(buttonPosition(button.index));

            if (button.pressed) {
                bevelRect.setFillColor(sf::Color(64, 64, 64));
                shadowRect.setFillColor(sf::Color(192, 192, 192));
            } else {
                bevelRect.setFillColor(sf::Color(192, 192, 192));
                shadowRect.setFillColor(sf::Color(64, 64, 64));
            }

            m_renderTarget->draw(bevelRect);
            m_renderTarget->draw(shadowRect);
            m_renderTarget->draw(backgroundRect);
        }

        switch(button.type) {
        case InterfaceButton::CreateBuilding:
            m_renderTarget->draw(m_buildingIcons[button.iconId], buttonPosition(button.index));
            break;
        case InterfaceButton::CreateUnit:
            m_renderTarget->draw(m_unitIcons[button.iconId], buttonPosition(button.index));
            break;
        case InterfaceButton::Research:
            m_renderTarget->draw(m_researchIcons[button.iconId], buttonPosition(button.index));
            break;
        case InterfaceButton::AttackStance:
        case InterfaceButton::Other:
            m_renderTarget->draw(m_commandIcons[button.action], buttonPosition(button.index));
            break;
        }
//        m_renderTarget->draw(button.tex, buttonPosition(button.index));
    }
}

void ActionPanel::setUnitManager(const std::shared_ptr<UnitManager> &unitManager)
{
    if (unitManager == m_unitManager) {
        return;
    }
    m_unitManager = unitManager;
}

void ActionPanel::setHumanPlayer(const Player::Ptr &player)
{
    if (player == m_humanPlayer) {
        return;
    }

    m_humanPlayer = player;
}

ScreenRect ActionPanel::rect() const
{
    ScreenRect r;
    r.height = 3 * 51;
    r.width = 5 * 55;
    r.x = 35;
//    r.y = 845;
    r.y = m_renderTarget->getSize().height - r.height - 25;
    return r;
}

void ActionPanel::releaseButtons()
{
    for (InterfaceButton &button : currentButtons) {
        if (button.pressed) {
            m_dirty = true;
        }

        button.pressed = false;
    }
}

const std::string &ActionPanel::helpTextId(const ActionPanel::Command icon)
{
    static const std::unordered_map<ActionPanel::Command, int> helpTextIds = {
        { Command::Cancel, 4911 },
        { Command::Ungarrison, 41014}, // TODO: 4950 for ram
        { Command::Stop, 4905 },
        { Command::Patrol, 4938 },
        { Command::Guard, 4936},
        { Command::Pack, 41055 },
        { Command::Unpack, 41056 },
        { Command::Convert, 4925  },
        { Command::SellWood, 41072 },
        { Command::SellFood, 41073 },
        { Command::SellStone, 41074 },
        { Command::CollectWood, 41076 }, // buy wood
        { Command::CollectFood, 41077 }, // buy food
        { Command::BuyFood, 41077 }, // buy food
        { Command::CollectStone, 41078 }, // buy stone
        { Command::BuyStone, 41078 }, // buy stone
        { Command::BuildCivilian, 41061 },
        { Command::BuildMilitary, 41062 },
        { Command::NextPage, 4912 }, // TODO 4918 for dock
        { Command::NextPage, 4912 },
        { Command::DisbandFormation, 41006 },
        { Command::LineFormation, 41021 },
        { Command::BoxFormation, 41020 },
        { Command::HordeFormation, 41019 },
        { Command::SetRallyPoint, 4944 },
        { Command::RemoveRallyPoint, 4949 },
        { Command::CloseGate, 41104 },
        { Command::OpenGate, 41105 },

        { Command::ResearchSpies, 41113 },

        { Command::Kill, 4941 },
        { Command::AttackGround, 4923 },
        { Command::FlankFormation, 41023 },
        { Command::SpreadOutFormation, 41022 },
        { Command::AbortTownBell, 41015 },
        { Command::RingTownBell, 41111 },
        { }
    };

    if (helpTextIds.find(icon) == helpTextIds.end()) {
        static const std::string nullString;
        return nullString;
    }

    return LanguageManager::Inst()->getString(helpTextIds.at(icon));
}

void ActionPanel::updateButtons()
{
    currentButtons.clear();
    if (m_selectedUnits.empty()) {
        return;
    }

    Unit::Ptr unit = *m_selectedUnits.begin();
    if (unit->player.lock() != m_humanPlayer) {
        return;
    }

    // Still prefer Definitive Edition Way. Simple Delete button. Always felt it takes unnecessary Index space. I think I will do Attack Move first. Then do simple waypoint behaviour?
    /*if (unit->data()->Type >= genie::Unit::MovingType && unit->data()->Type < genie::Unit::BuildingType) {
        InterfaceButton killButton;
        killButton.action = Command::Kill;
        killButton.index = 3;
        currentButtons.push_back(killButton);
    }*/

    const std::unordered_set<Task> actions = unit->actions.availableActions();
    std::unordered_set<genie::ActionType> addedTypes;
    for (const Task &task : actions) {
        if (addedTypes.count(task.data->ActionType)) {
            continue;
        }
        addedTypes.insert(task.data->ActionType);

        switch(task.data->ActionType) {
        case genie::ActionType::Garrison: {
            InterfaceButton garrisonButton;
            garrisonButton.action = Command::Garrison;
            garrisonButton.index = 4;
            currentButtons.push_back(garrisonButton);
            break;
        }
        case genie::ActionType::Build: {
            InterfaceButton backButton;
            backButton.action = Command::PreviousPage;
            backButton.index = 14;
            backButton.interfacePage = genie::Unit::BuildingsInterface;
            currentButtons.push_back(backButton);
            backButton.interfacePage = genie::Unit::MilitaryBuildingsInterface;
            currentButtons.push_back(backButton);

            InterfaceButton civilianButton;
            civilianButton.action = Command::BuildCivilian;
            civilianButton.index = 0;
            currentButtons.push_back(civilianButton);

            InterfaceButton militaryButton;
            militaryButton.action = Command::BuildMilitary;
            militaryButton.index = 1;
            currentButtons.push_back(militaryButton);

            InterfaceButton repairButton;
            repairButton.action = Command::Repair;
            repairButton.index = 2;
            currentButtons.push_back(repairButton);
            break;
        }
        case genie::ActionType::RetreatToShootingRage:
        case genie::ActionType::Combat:
            break;
        default:
            WARN << "Unhandled action type" << task.data->ActionType << task.data->actionTypeName() << task.data->AutoSearchTargets;
            break;
        }
    }

    if (!actions.empty()) {
        InterfaceButton stopButton;
        stopButton.action = Command::Stop;
        stopButton.index = 9;
        currentButtons.push_back(stopButton);
    }

    addCreateButtons(unit);
    if (unit->data()->InterfaceKind == genie::Unit::BuildingsInterface) {
        addResearchButtons(unit);
    }
    if (unit->data()->InterfaceKind == genie::Unit::SoldiersInterface) {
        addMilitaryButtons(unit);
    }
}

void ActionPanel::addCreateButtons(const std::shared_ptr<Unit> &unit)
{
    m_currentPage = 0;
    const std::vector<const genie::Unit *> creatableUnits = unit->creatableUnits();

    if (creatableUnits.empty()) {
        return;
    }

    if (unit->data()->Type >= genie::Unit::BuildingType) {
        InterfaceButton rallypointButton;
        rallypointButton.action = Command::SetRallyPoint;
        rallypointButton.index = 4;
        currentButtons.push_back(rallypointButton);
    }

    bool hasNext = false;
    for (const genie::Unit *creatable : creatableUnits) {
        if (creatable->Creatable.ButtonID > m_buttonOffset + 15) {
            hasNext = true;
            continue;
        }

        InterfaceButton button;
        if (unit->data()->InterfaceKind == genie::Unit::CiviliansInterface) {
            button.type = InterfaceButton::CreateBuilding;
            button.interfacePage = creatable->InterfaceKind;
        } else {
            button.type = InterfaceButton::CreateUnit;
            button.interfacePage = 0;
        }
        button.index = std::max(creatable->Creatable.ButtonID - 1, 0);
        button.unit = creatable;
        button.iconId = creatable->IconID;

        currentButtons.push_back(button);
    }

    if (hasNext) {
        InterfaceButton rightButton;
        rightButton.action = Command::NextPage;
        rightButton.index = 14;
        currentButtons.push_back(rightButton);
    }
}

void ActionPanel::addResearchButtons(const std::shared_ptr<Unit> &unit)
{
    Player::Ptr player = unit->player.lock();
    if (!player) {
        WARN << "Player-less unit";
        return;
    }
    const std::vector<const genie::Tech *> techs = player->civilization.researchAvailableAt(unit->data()->ID);
    if (techs.empty()) {
        return;
    }

    bool hasNext = false;

    for (const genie::Tech *tech : techs) {
        if (tech->ButtonID > m_buttonOffset + 15) {
            hasNext = true;
            continue;
        }

        InterfaceButton button;
        button.type = InterfaceButton::Research;

        button.index = std::max(tech->ButtonID - 1, 0);
        button.tech = tech;
        button.iconId = tech->IconID;

        currentButtons.push_back(button);

    }


    if (hasNext) {
        InterfaceButton rightButton;
        rightButton.action = Command::NextPage;
        rightButton.index = 14;
        currentButtons.push_back(rightButton);
    }

}

void ActionPanel::addMilitaryButtons(const std::shared_ptr<Unit> &unit)
{
    if (unit->data()->InterfaceKind != genie::Unit::SoldiersInterface) {
        return;
    }

    if (unit->data()->Class == genie::Unit::SiegeWeapon || unit->data()->Class == genie::Unit::UnpackedSiegeUnit) {
        InterfaceButton button;
        button.type = InterfaceButton::Other;
        button.interfacePage = 0;
        button.index = 0;
        button.action = Command::AttackGround;

        currentButtons.push_back(button);
    } else {
        InterfaceButton button;
        button.type = InterfaceButton::Other;
        button.interfacePage = 0;
        button.index = 3;
        button.action = Command::AttackWithSword; // In AOC uses a very different Icon. Seems like a Beta formation. AttackWithSword=AttackMove
        currentButtons.push_back(button);

        button.type = InterfaceButton::Other;
        button.interfacePage = 0;
        button.index = 0;
        button.action = Command::Patrol;
        currentButtons.push_back(button);

        button.type = InterfaceButton::Other;
        button.interfacePage = 0;
        button.index = 1;
        button.action = Command::Guard;
        currentButtons.push_back(button);


        button.type = InterfaceButton::Other;
        button.interfacePage = 0;
        button.index = 2;
        button.action = Command::Follow;
        currentButtons.push_back(button);
    }

    // Stance buttons
    if (unit->actions.hasAutoTargets()) {
        const Unit::Stance current = unit->stance;
        InterfaceButton button;
        button.showBorder = false;
        button.type = InterfaceButton::AttackStance;
        button.interfacePage = 0;

        if (current == Unit::Stance::Aggressive) {
            button.action = Command::AggressiveEnabled;
        } else {
            button.action = Command::Aggressive;
        }
        button.index = 5;
        currentButtons.push_back(button);

        if (current == Unit::Stance::Defensive) {
            button.action = Command::DefensiveEnabled;
        } else {
            button.action = Command::Defensive;
        }
        button.index = 6;
        currentButtons.push_back(button);

        if (current == Unit::Stance::StandGround) {
            button.action = Command::StandGroundEnabled;
        } else {
            button.action = Command::StandGround;
        }
        button.index = 7;
        currentButtons.push_back(button);

        if (current == Unit::Stance::NoAttack) {
            button.action = Command::NoAttackEnabled;
        } else {
            button.action = Command::NoAttack;
        }
        button.index = 8;
        currentButtons.push_back(button);

    }
}

void ActionPanel::handleButtonClick(const ActionPanel::InterfaceButton &button)
{
    if (button.type == InterfaceButton::CreateBuilding) {
        m_unitManager->startPlaceBuilding(button.unit->ID, m_humanPlayer);
        return;
    } else if (button.type == InterfaceButton::CreateUnit) {
        m_unitManager->enqueueProduceUnit(button.unit, m_selectedUnits);
    } else if (button.type == InterfaceButton::Research) {
        m_unitManager->enqueueResearch(button.tech, m_selectedUnits);
    } else if (button.type == InterfaceButton::AttackStance) {
        Unit::Stance newStance = Unit::Stance::Aggressive;
        switch(button.action) {
        case Command::Aggressive:
            newStance = Unit::Stance::Aggressive;
            break;
        case Command::Defensive:
            newStance = Unit::Stance::Defensive;
            break;
        case Command::StandGround:
            newStance = Unit::Stance::StandGround;
            break;
        case Command::NoAttack:
            newStance = Unit::Stance::NoAttack;
            break;
        default:
            return;
        }

        for (const Unit::Ptr &unit : m_selectedUnits) {
            unit->stance = newStance;
        }

        updateButtons();

    } else if (button.type == InterfaceButton::Other) {
        switch(button.action) {
        case Command::BuildMilitary:
            m_currentPage = genie::Unit::MilitaryBuildingsInterface;
            break;
        case Command::BuildCivilian:
            m_currentPage = genie::Unit::BuildingsInterface;
            break;
        case Command::PreviousPage:
            m_currentPage = 0;
            break;
        case Command::Stop:
            for (const Unit::Ptr &unit : m_unitManager->selected()) {
                unit->actions.clearActionQueue();
            }
            break;
        case Command::Kill:
            for (const Unit::Ptr &unit : m_unitManager->selected()) {
                unit->kill();
            }
            break;
        case Command::AttackGround:
            m_unitManager->selectAttackTarget();
            break;
        default:
            break;
        }
    }
}

ScreenPos ActionPanel::buttonPosition(const int index) const
{
    ScreenPos position;
    position.x = index % 5;
    position.x = (position.x) * 50 + 55;
    position.y = std::floor(index / 5.f);
    position.y *= 50;
    position.y += m_renderTarget->getSize().height  - 170;
    return position;
}

ScreenRect ActionPanel::buttonRect(const int index) const
{
    ScreenRect rect;
    const ScreenPos screenPos = buttonPosition(index);
    rect.x = screenPos.x;
    rect.y = screenPos.y;
    rect.width = 40;
    rect.height = 40;
    return rect;
}
