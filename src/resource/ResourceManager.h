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
#include <global/NonCopyable.h>

class ColorPalette;
class BinaFile;
class DrsFile;

//------------------------------------------------------------------------------
/// The resource manager is the primary interface for getting recourses. At
/// initialization the manager loads header information from drs and other
/// files and loads needed resources on the fly.
//
class ResourceManager : public NonCopyable
{
public:
  //----------------------------------------------------------------------------
  /// Initializes the resource manager once and returns its reference.
  //
  static ResourceManager* Inst();
  
  //----------------------------------------------------------------------------
  /// Returns the slp file with given id or 0 if not found. The slp file
  /// should not be deleted!
  ///
  /// @param id id of the slp file
  /// @return slp file
  //
  SlpFile * const getSlp(sf::Uint32 id);
  
  ColorPalette* getPalette(sf::Uint32 id);
  
  //----------------------------------------------------------------------------
  /// Adds an slp file that will be managed by the ResourceManager.
  /// TODO: Maybe auto_ptr
  ///
  /// @param slp reference to the slp file
  //
  void addSlpFile(SlpFile *slp);
  
  void addBinaFile(BinaFile *bina);
  
private:
  ResourceManager();
  virtual ~ResourceManager();
  
  std::vector<DrsFile *> drs_files_;
  std::map<sf::Uint32, SlpFile *> slp_files_;
  std::map<sf::Uint32, BinaFile*> bina_files_;
  
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
