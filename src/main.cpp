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

#include <Engine.h>

#include <geniedat/File.h>
#include "mechanics/EntityFactory.h"
#include "global/Config.h"
#include "resource/ResourceManager.h"
#include "render/CompGraphic.h"

class Base
{
public:
  virtual void x() = 0;
};

class Derived : public Base
{
public:
  int i;
  
  virtual void x() {}
};

void test(std::map<char *, boost::shared_ptr<Base> > &m)
{
  boost::shared_ptr<Derived> n = boost::shared_ptr<Derived>(new Derived());
  n->i = 10;
  
  m["test"] = n;
}


// TODO: Bad_alloc

int main(int argc, char **argv)
{
  Logger::setLogLevel(Logger::L_INFO);
  
  Config::Inst()->parseOptions(argc, argv);
  
//  boost::shared_ptr<Entity> e = EntityFactory::Inst().createUnit(281);

  std::map<char *, boost::shared_ptr<Base> > map;
  test(map);
  
  boost::shared_ptr<Base> xx = map["test"];
  std::cout << boost::dynamic_pointer_cast<Derived>(xx)->i << std::endl;
  
  //std::cout << e->getAttribute<attr::String>(attr::id::NAME)->value << std::endl;
  
  //std::cout << e->hasAttribute(attr::id::MOVABLE);
  
  comp::GraphicPtr graph = comp::GraphicTemplate::create(881);
  
  std::cout << "comp: " << graph.get() << std::endl;
  
//  std::cout << graph->getAttribute<attr::Graphic>(attr::GRAPHIC)->Resource->getId() << std::endl;
  
  attr::GraphicPtr gp = graph->getAttribute<attr::Graphic>(attr::GRAPHIC); 
  
  std::cout << "attr: " << gp.get() << std::endl;
  
 // std::cout << gp->Resource->getId() << std::endl;
  /*
  Engine en;
  en.start();*/
  
  return 0;
}
