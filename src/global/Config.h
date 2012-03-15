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


#ifndef CONFIG_H
#define CONFIG_H
#include <string>

#include "NonCopyable.h"

#include <boost/program_options.hpp>
#include <genie/Types.h>

//
class Config : public NonCopyable
{
public:
  //----------------------------------------------------------------------------
  /// Get instance (singleton pattern)
  ///
  /// @return returns instance of config
  //
  static Config* Inst();
  
  //----------------------------------------------------------------------------
  /// Parses command line options and config file if present.
  ///
  //
  void parseOptions(int argc, char **argv);
  
  //----------------------------------------------------------------------------
  /// Get path to the game.
  ///
  /// @return path pointing to the game dir
  //
  std::string getGamePath();
  
  //----------------------------------------------------------------------------
  /// Get path of the data directory.
  ///
  /// @return path of data directory
  //
  std::string getDataPath();
  
  //----------------------------------------------------------------------------
  /// Returns a given scenario file or an empty string if unused
  //
  std::string getScenarioFile();
  
  
  genie::GameVersion getGameVersion() const;
  

private:
  Config();
  virtual ~Config();
    
  boost::program_options::variables_map options_;
};

#endif // CONFIG_H
