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

#include "resource/LanguageManager.h"

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

void UnitRenderer::createForms(EntityPtr entity)
{
    comp::UnitDataPtr gunit = entity->getComponent<comp::UnitData>(comp::UNIT_DATA);

    if (!gunit) {
        return;
    }

    std::cout << "Creating form for " << gunit->readableName() << std::endl;

    EntityForm form(entity);

    comp::GraphicPtr graphic = comp::GraphicRender::create(gunit->getData().StandingGraphic.first);

    if (gunit->getData().DeadFish.WalkingGraphic > 0) {
        graphic->setMovingGraphic(gunit->getData().DeadFish.WalkingGraphic);
    }

    graphic->setMapObject(entity->getComponent<comp::MapObject>(comp::MAP_OBJECT));

    form.addComponent(comp::GRAPHIC_RENDER, graphic);

    forms_.push_back(form);
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
    for (EntityForm &form : forms_) {
        renderTarget_->draw(form);
    }
}
