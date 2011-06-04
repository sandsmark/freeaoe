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


#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Resource.h"

#include <memory>
#include <map>
#include <fstream>
#include "Graphic.h"
#include <file/SlpFile.h>
#include <global/Logger.h>

class DrsFile;

//------------------------------------------------------------------------------
/// The resource manager is the primary interface for getting recourses. At
/// initialization the manager loads header information from drs and other
/// files and loads needed resources on the fly.
//
class ResourceManager
{
public:
  //----------------------------------------------------------------------------
  /// Initializes the resource manager once and returns its reference.
  //
  static ResourceManager* Inst();
  
  //----------------------------------------------------------------------------
  /// Destroys the resource manager. Has to be called on exit.
  //
  static void Destroy();
  
  //----------------------------------------------------------------------------
  /// Returns 
  //
  std::auto_ptr<Graphic> getGraphic(unsigned int id);
  
  void addResource(Resource *);
  
private:
  ResourceManager();
  virtual ~ResourceManager();
  
  std::vector<DrsFile *> drs_files_;
  std::map<long, SlpFile *> slp_files_;
  
  std::map<sf::Uint32, Resource *> resources_;
  
  std::fstream terrain_file_;
  std::fstream graphics_file_;
 
  static Logger &log;
  
  //----------------------------------------------------------------------------
  /// Loads all resource headers.
  //
  void initialize();
  
  void loadDrs(std::string file_name);
};

#endif // RESOURCEMANAGER_H
