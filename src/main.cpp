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

#include <iostream>

#include "Engine.h"
#include "resource/DataManager.h"
#include "resource/ResourceManager.h".h"

#include "mechanics/EntityFactory.h"
#include "global/Config.h"
#include "resource/ResourceManager.h"
#include "render/GraphicRender.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shape.hpp>

// TODO: Bad_alloc
int main(int argc, char **argv)
{
  Logger::setLogLevel(Logger::L_INFO);
  
  if (!Config::Inst()->parseOptions(argc, argv)) {
      return 1;
  }

  if (!DataManager::Inst().initialize()) {
      return 1;
  }

  if (!ResourceManager::Inst()->initialize()) {
      return 1;
  }

  Engine en;
  en.start();
  
  return 0;
}
