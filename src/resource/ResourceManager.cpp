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

#include <genie/resource/DrsFile.h>
#include <genie/resource/UIFile.h>

Logger &ResourceManager::log = Logger::getLogger("freeaoe.ResourceManager");

//------------------------------------------------------------------------------
ResourceManager *ResourceManager::Inst()
{
    static ResourceManager rm;
    return &rm;
}

genie::ScnFilePtr ResourceManager::getScn(unsigned int id)
{
    for (std::shared_ptr<genie::DrsFile> drsFile : drs_files_) {
        genie::ScnFilePtr scnfile = drsFile->getScnFile(id);

        if (scnfile) {
            log.info("found scn file v %s", scnfile->version.c_str());
            std::cout << scnfile->scenarioInstructions << std::endl;
            return scnfile;
        }
    }

    return genie::ScnFilePtr();
}

//------------------------------------------------------------------------------
genie::SlpFilePtr ResourceManager::getSlp(sf::Uint32 id)
{
    genie::SlpFilePtr slp_ptr;

    log.info("Loading slp with id [%d]", id);

    for (DrsFileVector::iterator i = drs_files_.begin(); i != drs_files_.end();
         i++) {
        slp_ptr = (*i)->getSlpFile(id);

        if (slp_ptr.get() != 0)
            return slp_ptr;
    }

    log.warn("No slp file with id [%d] found!", id);
    return slp_ptr;
    /*std::map<sf::Uint32, SlpFile *>::iterator it = slp_files_.find(id);
  
  if (it == slp_files_.end())
  {
    log.warn("Trying to get slp file with id [%u] that doesn't exist!", id);
    return 0;
  }
  
  SlpFile *slp = slp_files_[id];
  slp->load();
  
  return slp;*/
}

//------------------------------------------------------------------------------
res::GraphicPtr ResourceManager::getGraphic(Uint32 id)
{
    res::Graphic *graph;

    if (graphics_.find(id) != graphics_.end()) {
        graph = graphics_[id];
    } else {
        graph = new res::Graphic(id);
        graph->load();

        graphics_[id] = graph;
    }

    return res::GraphicPtr(graph);
}

//------------------------------------------------------------------------------
res::TerrainPtr ResourceManager::getTerrain(unsigned int type)
{
    if (terrains_.find(type) != terrains_.end()) {
        return terrains_[type];
    }

    res::TerrainPtr terrain = res::TerrainPtr(new res::Terrain(type));
    terrain->load();

    terrains_[type] = terrain;

    return terrain;
}

//------------------------------------------------------------------------------
genie::PalFilePtr ResourceManager::getPalette(sf::Uint32 id)
{
    //   return bina_files_[id]->readPalette();
    genie::PalFilePtr pal_ptr;

    for (std::shared_ptr<genie::DrsFile> drsFile : drs_files_) {
        pal_ptr = drsFile->getPalFile(id);

        if (pal_ptr) {
            return pal_ptr;
        }
    }

    log.warn("No pal file with id [%u] found!", id);
    return pal_ptr;
}

//------------------------------------------------------------------------------
void ResourceManager::addSlpFile(SlpFile *slp)
{
    /*
  std::map<sf::Uint32, SlpFile *>::iterator it = slp_files_.find(slp->getId());
  
  if (it != slp_files_.end())
    log.warn("Slp file with id: [%u] already exists!", slp->getId());
  else
    slp_files_[slp->getId()] = slp;
  */
}

//------------------------------------------------------------------------------
void ResourceManager::addBinaFile(BinaFile *bina)
{
    //   bina_files_[bina->getId()] = bina;
}

//------------------------------------------------------------------------------
ResourceManager::ResourceManager()
{
}

//------------------------------------------------------------------------------
ResourceManager::~ResourceManager()
{
    /*
  for (std::map<sf::Uint32, SlpFile *>::iterator it = slp_files_.begin();
       it != slp_files_.end(); it++)
    delete it->second;
  
  for (std::map<sf::Uint32, BinaFile*>::iterator it = bina_files_.begin();
       it != bina_files_.end(); it++)
    delete it->second;
  
  for (std::vector<DrsFile *>::iterator it = drs_files_.begin();
       it != drs_files_.end(); it++)
     delete (*it);
  
  for (GraphicMap::iterator it = graphics_.begin(); it != graphics_.end(); it++)
    delete it->second;
  */
}

//------------------------------------------------------------------------------
bool ResourceManager::initialize()
{
    log.debug("Initializing ResourceManager");

    try {
        loadDrs("gamedata.drs");
        loadDrs("gamedata_x1.drs");
        loadDrs("gamedata_x1_p1.drs");
        loadDrs("graphics.drs");
        loadDrs("interfac.drs");
        loadDrs("sounds.drs");
        loadDrs("sounds_x1.drs");
        loadDrs("terrain.drs");
    } catch (const std::exception &error) {
        std::cerr << "Failed to load resource: " << error.what() << std::endl;
        return false;
    }

    return true;
}

//------------------------------------------------------------------------------
void ResourceManager::loadDrs(std::string file_name)
{
    log.info("Loading %s", file_name.c_str());

    std::string file_path = Config::Inst()->getDataPath() + file_name;

    std::shared_ptr<genie::DrsFile> drs_file(new genie::DrsFile());

    drs_file->setGameVersion(Config::Inst()->getGameVersion());
    drs_file->load(file_path.c_str());

    drs_files_.push_back(drs_file);

    /*
  DrsFile *drs = new DrsFile(Config::Inst()->getDataPath() + file_name, this);
  drs->loadHeader();
  
  drs_files_.push_back(drs);
  */
}
