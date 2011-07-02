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
#include <file/BinaFile.h>
#include <file/ColorPalette.h>

Logger& ResourceManager::log = Logger::getLogger("freeaoe.ResourceManager");

//------------------------------------------------------------------------------
ResourceManager* ResourceManager::Inst()
{
  static ResourceManager rm;
  return &rm;
}

//------------------------------------------------------------------------------
SlpFile* ResourceManager::getSlp(sf::Uint32 id)
{
  std::map<sf::Uint32, SlpFile *>::iterator it = slp_files_.find(id);
  
  if (it == slp_files_.end())
  {
    log.warn("Trying to get slp file with id [%u] that doesn't exist!", id);
    return 0;
  }
  
  SlpFile *slp = slp_files_[id];
  slp->load();
  
  return slp;
}

//------------------------------------------------------------------------------
ColorPalette* ResourceManager::getPalette(sf::Uint32 id)
{
  return bina_files_[id]->readPalette();
}

//------------------------------------------------------------------------------
void ResourceManager::addSlpFile(SlpFile* slp)
{
  std::map<sf::Uint32, SlpFile *>::iterator it = slp_files_.find(slp->getId());
  
  if (it != slp_files_.end())
    log.warn("Slp file with id: [%u] already exists!", slp->getId());
  else
    slp_files_[slp->getId()] = slp;
}

//------------------------------------------------------------------------------
void ResourceManager::addBinaFile(BinaFile* bina)
{
  bina_files_[bina->getId()] = bina;
}

//------------------------------------------------------------------------------
ResourceManager::ResourceManager()
{
  initialize();
}

//------------------------------------------------------------------------------
ResourceManager::~ResourceManager()
{
  for (std::map<sf::Uint32, SlpFile *>::iterator it = slp_files_.begin();
       it != slp_files_.end(); it++)
    delete it->second;
  
  for (std::map<sf::Uint32, BinaFile*>::iterator it = bina_files_.begin();
       it != bina_files_.end(); it++)
    delete it->second;
  
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

