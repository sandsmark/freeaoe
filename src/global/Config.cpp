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


#include "Config.h"

#include <fstream>

namespace po = boost::program_options;
  
//------------------------------------------------------------------------------
Config* Config::Inst()
{
  static Config config;
  return &config;
}

//------------------------------------------------------------------------------
void Config::parseOptions(int argc, char** argv)
{
  
  // options allowed only on commandline
  po::options_description generic("Generic options");
  generic.add_options()
    ("config-file,c", po::value<std::string>()->default_value("faoe.cfg"), 
     "path to config file")
    ("scenario,s", po::value<std::string>()->default_value(""), "load scenario")
    ;
    
  po::options_description config("Configuration");
  config.add_options()
    ("game-path", 
     po::value<std::string>()->default_value("aoe2/"),
     "game path")
    ;
  
    
  po::options_description cmdline_options;
  cmdline_options.add(generic).add(config);
  
  po::options_description config_file_options;
  config_file_options.add(config);
  
  po::store(po::parse_command_line(argc, argv, cmdline_options), options_);
  po::notify(options_);
  
  std::ifstream cfg_file(options_["config-file"].as<std::string>().c_str());
  
  if (cfg_file)
  {
    po::store(po::parse_config_file(cfg_file, config_file_options), options_);
    po::notify(options_);
  }
   
}


//------------------------------------------------------------------------------
std::string Config::getGamePath()
{
  return options_["game-path"].as<std::string>();
}

//------------------------------------------------------------------------------
std::string Config::getDataPath()
{
  return getGamePath() + "Data/";
}

//------------------------------------------------------------------------------
std::string Config::getScenarioFile()
{
  return options_["scenario"].as<std::string>();
}


//------------------------------------------------------------------------------
genie::GameVersion Config::getGameVersion() const
{
  return genie::GV_TC;
}

//------------------------------------------------------------------------------
Config::Config()
{
}

//------------------------------------------------------------------------------
Config::~Config()
{
}

