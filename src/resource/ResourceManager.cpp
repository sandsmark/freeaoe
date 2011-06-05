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


#include "ResourceManager.h"

#include <fstream>
#include <iostream>
#include <memory>

#include <global/Config.h>

#include <file/DrsFile.h>

Logger& ResourceManager::log = Logger::getLogger("freeaoe.ResourceManager");

//------------------------------------------------------------------------------
ResourceManager* ResourceManager::Inst()
{
  static ResourceManager rm;
  return &rm;
}

//------------------------------------------------------------------------------
void ResourceManager::Destroy()
{

}


//------------------------------------------------------------------------------
std::auto_ptr< Graphic > ResourceManager::getGraphic(unsigned int id)
{
  
  std::map<sf::Uint32, Resource *>::iterator pos = resources_.find(id);
  
  if (pos == resources_.end())
  {
    std::cerr << "Graphic " << id << " not found!" << std::endl;
    return std::auto_ptr< Graphic > (0);
  }
  else
  {
    if (pos->second->isLoaded() == false)
    {
      log.info("Loading graphic [%u]", id);
      pos->second->load();
    }
    Graphic *g = dynamic_cast<Graphic *>(pos->second);
    return std::auto_ptr< Graphic >( new Graphic(*g) ); //return a copy
  }
}

//------------------------------------------------------------------------------
void ResourceManager::addResource(Resource* res)
{
  //TODO: check if already added
  resources_[res->getId()] = res;
}


//------------------------------------------------------------------------------
ResourceManager::ResourceManager()
{
  initialize();
}

//------------------------------------------------------------------------------
ResourceManager::~ResourceManager()
{
  for (std::vector<DrsFile *>::iterator it = drs_files_.begin();
       it != drs_files_.end(); it++)
     delete (*it);
}

//------------------------------------------------------------------------------
void ResourceManager::initialize()
{
  log.debug("Initializing ResourceManager");
  
  loadDrs("graphics.drs");
  loadDrs("terrain.drs");
  loadDrs("interfac.drs");
}

//------------------------------------------------------------------------------

void ResourceManager::loadDrs(std::string file_name)
{
  log.info("Loading %s", file_name.c_str());
  
  DrsFile *drs = new DrsFile(Config::Inst()->getDataPath() + file_name, this);
  drs->loadHeader();
  
  drs_files_.push_back(drs);
}

