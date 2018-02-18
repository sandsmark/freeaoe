/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

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

#include "UnitRenderer.h"
#include "GraphicRender.h"
#include <mechanics/CompUnitData.h>
#include "IRenderTarget.h"
#include <resource/DataManager.h>
#include "mechanics/Map.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "resource/LanguageManager.h"
#include "mechanics/EntityFactory.h"

UnitRenderer::UnitRenderer()
{
}

UnitRenderer::~UnitRenderer()
{
}

void UnitRenderer::add(const EntityForm &form)
{
    forms_.push_back(form);
}

bool UnitRenderer::createForms(EntityPtr entity)
{
    comp::UnitDataPtr gunit = entity->getComponent<comp::UnitData>(comp::UNIT_DATA);

    if (!gunit) {
        return false;
    }

    std::cout << "Creating form for " << gunit->readableName() << " (" << gunit->getData().ID << ")" << std::endl;

    EntityForm form(entity);

    if (gunit->getData().StandingGraphic.first < 0) {
        std::cerr << "No standing graphic" << std::endl;
        return false;
    }

    comp::GraphicPtr graphic = comp::GraphicRender::create(gunit->getData().StandingGraphic.first);
    if (!graphic) {
        return false;
    }

    if (gunit->getData().Moving.WalkingGraphic > 0) {
        graphic->setMovingGraphic(gunit->getData().Moving.WalkingGraphic);
    }

    graphic->setMapObject(entity->getComponent<comp::MapObject>(comp::MAP_OBJECT));

    form.addComponent(comp::GRAPHIC_RENDER, graphic);

    forms_.push_back(form);

    if (gunit->getData().Type >= genie::Unit::BuildingType) {
        for (const genie::unit::BuildingAnnex &annex : gunit->getData().Building.Annexes) {
            if (annex.UnitID < 0) {
                continue;
            }

            MapPos offset(annex.Misplacement.first * -48, annex.Misplacement.second * -48);
            EntityPtr annexUnit = EntityFactory::Inst().createUnit(annex.UnitID, graphic->map_object_->getPos() + offset);
            createForms(annexUnit);
        }
    }

    return true;
}

bool UnitRenderer::update(Time time)
{
    bool updated = false;
    for (EntityForm &form : forms_) {
        updated = form.update(time) || updated;
    }

    return updated;
}

void UnitRenderer::display()
{
    if (m_outlineOverlay.getSize() != renderTarget_->getSize()) {
        m_outlineOverlay.create(renderTarget_->getSize().x, renderTarget_->getSize().y, false);
    }

    m_outlineOverlay.clear(sf::Color::Transparent);
    for (EntityForm &form : forms_) {
        comp::UnitDataPtr gunit = form.getRoot()->getComponent<comp::UnitData>(comp::UNIT_DATA);
        if (gunit->getData().Type < genie::Unit::BuildingType) {
            continue;
        }

        comp::GraphicPtr graph = form.getComponent<comp::GraphicRender>(comp::GRAPHIC_RENDER);
        comp::MapObjectPtr mapObject = form.getRoot()->getComponent<comp::MapObject>(comp::MAP_OBJECT);

        std::vector<std::shared_ptr<res::Graphic>> graphics = graph->graphic_->getDeltas();
        graphics.push_back(graph->graphic_);

        for (const res::GraphicPtr graphic : graphics) {
            ScreenPos pos = renderTarget_->absoluteScreenPos(mapObject->getPos()) - graphic->getHotspot() - graphic->offset_;
            sf::Texture texture;
            texture.loadFromImage(graphic->getImage());
            sf::Sprite sprite;
            sprite.setTexture(texture);
            sprite.setPosition(pos);
            m_outlineOverlay.draw(sprite);
        }
    }


    for (EntityForm &form : forms_) {
        comp::MapObjectPtr mapObject = form.getRoot()->getComponent<comp::MapObject>(comp::MAP_OBJECT);

        if (form.getRoot()->selected) { // draw health indicator
            ScreenPos pos = renderTarget_->absoluteScreenPos(mapObject->getPos());
            pos.x -= Map::TILE_SIZE_HORIZONTAL / 8;
            pos.y -= Map::TILE_SIZE_VERTICAL;

            sf::RectangleShape rect;
            rect.setFillColor(sf::Color::Green);
            rect.setOutlineColor(sf::Color::Transparent);

            rect.setPosition(pos);
            rect.setSize(sf::Vector2f(Map::TILE_SIZE_HORIZONTAL / 4, 2));
            m_outlineOverlay.draw(rect);
        }

        comp::UnitDataPtr gunit = form.getRoot()->getComponent<comp::UnitData>(comp::UNIT_DATA);
        if (gunit->getData().Type >= genie::Unit::BuildingType) {
            continue;
        }
        renderTarget_->draw(form);

        comp::GraphicPtr graph = form.getComponent<comp::GraphicRender>(comp::GRAPHIC_RENDER);
        ScreenPos pos = renderTarget_->absoluteScreenPos(mapObject->getPos()) - graph->graphic_->getHotspot() - graph->graphic_->offset_;

        sf::Texture texture;
        texture.loadFromImage(graph->overlay());
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(pos);
        sf::BlendMode blendMode = sf::BlendAlpha;
        blendMode.alphaSrcFactor = sf::BlendMode::DstAlpha;
        m_outlineOverlay.draw(sprite, blendMode);
    }

    m_outlineOverlay.display();
    renderTarget_->draw(m_outlineOverlay.getTexture(), ScreenPos(0, 0));
}
