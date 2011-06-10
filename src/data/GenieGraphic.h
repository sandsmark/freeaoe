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


#ifndef GENIEGRAPHIC_H
#define GENIEGRAPHIC_H
#include <SFML/Config.hpp>
#include <string>

//------------------------------------------------------------------------------
/// Class for loading data describing Slp Graphics
//
class GenieGraphic
{
public:
  //----------------------------------------------------------------------------
  /// Returns the id of the described slp file.
  ///
  /// @return slp id
  //
  sf::Uint32 getSlpId();
 
public: //TODO: encapsule

  sf::Uint32 id_;
  std::string name1_;
  sf::Uint32 slp_id_;
  sf::Uint32 frame_count_;
  sf::Uint32 angle_count_;
  
  float frame_rate_;
};

#endif // GENIEGRAPHIC_H
