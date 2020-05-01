#include "UnitsRenderer.h"

#include "Camera.h"

#include "mechanics/Player.h"
#include "mechanics/Unit.h"
#include "mechanics/UnitManager.h"
#include "mechanics/Missile.h"
#include "mechanics/Map.h"
#include "GraphicRender.h"
#include "IRenderTarget.h"
#include "SfmlRenderTarget.h"

#ifdef DEBUG
// For debugging pathfinding
#include "actions/ActionMove.h"
#endif

#include <SFML/Graphics.hpp>

void UnitsRenderer::render(const std::shared_ptr<IRenderTarget> &renderTarget, const std::vector<std::weak_ptr<Entity>> &visible)
{
    std::shared_ptr<VisibilityMap> visibilityMap = m_visibilityMap.lock();
    if (!visibilityMap) {
        WARN << "visibility map gone!";
        return;
    }

    std::shared_ptr<UnitManager> unitManager = m_unitManager.lock();
    if (!unitManager) {
        WARN << "Unit manager gone!";
        return;
    }

    CameraPtr camera = renderTarget->camera();

    if (!m_outlineOverlay || m_outlineOverlay->getSize() != renderTarget->getSize()) {
        m_outlineOverlay = renderTarget->createTextureTarget(renderTarget->getSize());
    }

    if (camera->targetPosition() != m_previousCameraPos) {

        for (const Unit::Ptr &unit : unitManager->units()) {
            unit->isVisible = false;
        }
        for (const Missile::Ptr &missile : unitManager->missiles()) {
            missile->isVisible = false;
        }
        for (const DecayingEntity::Ptr &entity : unitManager->decayingEntities()) {
            entity->isVisible = false;
        }
        m_previousCameraPos = camera->targetPosition();
    }

    std::vector<Unit::Ptr> visibleUnits;
    std::vector<Missile::Ptr> visibleMissiles;
    for (const std::weak_ptr<Entity> &e : visible) {
        std::shared_ptr<Entity> entity = e.lock();
        if (!entity) {
            WARN << "got dead entity";
            continue;
        }

        const VisibilityMap::Visibility visibility = visibilityMap->visibilityAt(entity->position());
        if (visibility == VisibilityMap::Unexplored) {
            continue;
        }

        if (entity->isUnit()) {
            Unit::Ptr unit = Unit::fromEntity(entity);

            if (unit->garrisonedIn.lock() != nullptr) {
                continue;
            }

            if (visibility == VisibilityMap::Visible) {
                entity->isVisible = true;
                visibleUnits.push_back(unit);
                entity->renderer().render(*renderTarget, camera->absoluteScreenPos(entity->position()), RenderType::Shadow);

                continue;
            }

            if (visibility != VisibilityMap::Explored || !unit->data()->FogVisibility) {
                continue;
            }

            entity->isVisible = true;

            entity->renderer().render(*renderTarget, camera->absoluteScreenPos(entity->position()), RenderType::InTheShadows);

            continue;
        }

        if (entity->isMissile()) {
            Missile::Ptr missile = Entity::asMissile(entity);
            if (visibility != VisibilityMap::Visible) {;// && missile->playerId != GaiaID) {
                continue;
            }

            entity->isVisible = true;

            MapPos shadowPosition = entity->position();
            shadowPosition.z = entity->map()->elevationAt(shadowPosition);
            entity->renderer().render(*renderTarget, camera->absoluteScreenPos(shadowPosition), RenderType::Shadow);

            visibleMissiles.push_back(missile);

            continue;
        }

        if (entity->isDecayingEntity() || entity->isDoppleganger()) {
            if (visibility == VisibilityMap::Visible) {
                entity->renderer().render(*renderTarget, camera->absoluteScreenPos(entity->position()), RenderType::Base);
            } else {
                entity->renderer().render(*renderTarget, camera->absoluteScreenPos(entity->position()), RenderType::InTheShadows);
            }

            entity->isVisible = true;
        }
    }
    std::sort(visibleUnits.begin(), visibleUnits.end(), MapPositionSorter());


    m_outlineOverlay->clear(Drawable::Transparent);

    for (const Unit::Ptr &unit : visibleUnits) {
        const ScreenPos unitPosition = camera->absoluteScreenPos(unit->position());
        if (!(unit->data()->OcclusionMode & genie::Unit::OccludeOthers)) {
            unit->renderer().render(*m_outlineOverlay, unitPosition, RenderType::Outline);
        } else {
            unit->renderer().render(*m_outlineOverlay, unitPosition, RenderType::BuildingAlpha);

        }
    }
    std::reverse(visibleUnits.begin(), visibleUnits.end());

    for (const Unit::Ptr &unit : visibleUnits) {

        const bool blinkingAsTarget = unit->targetBlinkTimeLeft > 0 &&
                (((unit->targetBlinkTimeLeft) / 500) % 2 == 0) &&
                !unit->isDead() && !unit->isDying();

        if (blinkingAsTarget || unit->selected) {
            sf::RectangleShape rect;
            sf::CircleShape circle;
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineThickness(1);

            double width = unit->data()->OutlineSize.x * Constants::TILE_SIZE_HORIZONTAL;
            double height =  unit->data()->OutlineSize.y * Constants::TILE_SIZE_VERTICAL;

            if (unit->data()->ObstructionType == genie::Unit::UnitObstruction) {
                width /= 2.;
                height /= 2.;
            } else {
                circle.setPointCount(4);
            }

#ifdef DEBUG
            rect.setFillColor(sf::Color::Transparent);
            rect.setOutlineColor(sf::Color::White);
            rect.setOutlineThickness(1);
            rect.setSize(unit->clearanceSize());
            rect.setPosition(camera->absoluteScreenPos(unit->position()));// + unit->rect().topLeft());
            m_outlineOverlay->draw(rect);
#endif

            ScreenPos pos = camera->absoluteScreenPos(unit->position());

            circle.setPosition(pos.x - width, pos.y - height);
            circle.setRadius(width);
            circle.setScale(1, height / width);
            circle.setOutlineColor(sf::Color::Black);
            renderTarget->draw(circle);

            if (blinkingAsTarget) {
                circle.setOutlineColor(sf::Color::Green);
            } else {
                circle.setOutlineColor(sf::Color::White);
            }
            circle.setOutlineThickness(2);
            circle.setPosition(pos.x - width, pos.y - height + 1);
            renderTarget->draw(circle);

            // TODO: figure out what this is used for in which games
//            bool showOutline = false;
            bool showHealthbar = false;
            switch(unit->data()->SelectionEffect) {
            case genie::Unit::ShowHPHideOutline:
//                showOutline = false;
                showHealthbar = true;
                break;
            case genie::Unit::ShowHPShowOutline:
//                showOutline = true;
                showHealthbar = true;
                break;
            case genie::Unit::HideHPHideOutline:
//                showOutline = false;
                showHealthbar = false;
                break;
            case genie::Unit::HideHPShowOutline:
//                showOutline = true;
                showHealthbar = false;
                break;
            default:
                WARN << "invalid selection effect" << unit->data()->SelectionEffect;
                break;
            }

            if (!blinkingAsTarget) {
                pos.x -= Constants::TILE_SIZE_HORIZONTAL / 8;
                pos.y -= height + Constants::TILE_SIZE_HEIGHT * unit->data()->HPBarHeight;

                rect.setOutlineColor(sf::Color::Transparent);
                rect.setPosition(pos);

            }

            // draw health indicator
            if (showHealthbar) {
                if (unit->healthLeft() < 1.) {
                    rect.setFillColor(sf::Color::Red);
                    rect.setSize(sf::Vector2f(Constants::TILE_SIZE_HORIZONTAL / 4., 2));
                    m_outlineOverlay->draw(rect);
                }

                rect.setFillColor(sf::Color::Green);
                rect.setSize(sf::Vector2f(unit->healthLeft() * Constants::TILE_SIZE_HORIZONTAL / 4., 2));
                m_outlineOverlay->draw(rect);
            }
        }

        const ScreenPos pos = renderTarget->camera()->absoluteScreenPos(unit->position());
        unit->renderer().render(*renderTarget, pos, RenderType::Base);


#if defined(DEBUG)
        ActionPtr action = unit->actions.currentAction();
        if (action && action->type == IAction::Type::Move) {
            std::shared_ptr<ActionMove> moveAction = std::static_pointer_cast<ActionMove>(action);

            sf::CircleShape circle;
            circle.setRadius(2);
//            circle.setScale(1, 0.5);
            circle.setFillColor(sf::Color::Black);
            circle.setOutlineColor(sf::Color::White);
            circle.setOutlineThickness(1);
            for (const MapPos &p : moveAction->path()) {
                ScreenPos pos = camera->absoluteScreenPos(p);
                circle.setPosition(pos.x, pos.y);
                m_outlineOverlay->draw(circle);
            }
        }
#endif
    }

    m_outlineOverlay->display();

    {
        // this is a bit wrong, on bright buildings it's almost not visible,
        // but haven't found a better solution other than writing a custom shader (and I'm lazy)
        renderTarget->draw(m_outlineOverlay, sf::BlendAdd);
    }

#if defined(DEBUG)
    for (size_t i=0; i<ActionMove::testedPoints.size(); i++) {
        const MapPos &mpos = ActionMove::testedPoints[i];
        sf::CircleShape circle;
        ScreenPos pos = camera->absoluteScreenPos(mpos);
        circle.setPosition(pos.x, pos.y);
        circle.setRadius(2);
        int col = 128 * i / ActionMove::testedPoints.size() + 128;
        circle.setFillColor(sf::Color(128 + col, 255 - col, 255, 128));
        circle.setOutlineColor(sf::Color::Transparent);
        renderTarget->draw(circle);
    }
    for (const Unit::Ptr &unit : visibleUnits) {
        sf::CircleShape circle;
        ScreenPos pos = camera->absoluteScreenPos(unit->position());
        circle.setPosition(pos.x, pos.y);
        circle.setRadius(5);
        circle.setScale(1, 0.5);
        circle.setOutlineColor(sf::Color::White);
        renderTarget->draw(circle);
    }
#endif

    const MoveTargetMarker::Ptr &marker = unitManager->moveTargetMarker();
    marker->renderer().render(*renderTarget,
                                          renderTarget->camera()->absoluteScreenPos(marker->position()),
                                          RenderType::Base);

    for (const Missile::Ptr &missile : visibleMissiles) {
        missile->renderer().render(*renderTarget, renderTarget->camera()->absoluteScreenPos(missile->position()), RenderType::Base);
    }

    if (unitManager->state() == UnitManager::State::PlacingBuilding || unitManager->state() == UnitManager::State::PlacingWall) {
//        DBG << "placing buildings" << m_buildingsToPlace.size();
        const std::vector<UnplacedBuilding> &buildingsToPlace = unitManager->buildingsToPlace();

        if (buildingsToPlace.size() == 1) {
            const double width = buildingsToPlace[0].data->OutlineSize.x * Constants::TILE_SIZE_HORIZONTAL + 1;
            const double height =  buildingsToPlace[0].data->OutlineSize.y * Constants::TILE_SIZE_VERTICAL + 1;

            sf::CircleShape circle;
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineThickness(1);
            circle.setRadius(width);
            circle.setPointCount(4);
            circle.setScale(1, height / width);

            ScreenPos pos = camera->absoluteScreenPos(buildingsToPlace[0].position);


            circle.setPosition(pos.x - width, pos.y - height + 1);
            circle.setOutlineColor(sf::Color::Black);
            renderTarget->draw(circle);

            circle.setPosition(pos.x - width, pos.y - height);
            circle.setOutlineColor(sf::Color::White);
            renderTarget->draw(circle);
        }

        for (const UnplacedBuilding &building : buildingsToPlace) {
            building.graphic->setOrientation(building.orientation);
            building.graphic->render(*renderTarget,
                                        renderTarget->camera()->absoluteScreenPos(building.position),
                                        building.canPlace ? RenderType::ConstructAvailable : RenderType::ConstructUnavailable);
        }
    }

}

void UnitsRenderer::setUnitManager(const std::shared_ptr<UnitManager> &unitManager)
{
    m_unitManager = unitManager;
}
