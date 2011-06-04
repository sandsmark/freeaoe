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


#ifndef RESOURCE_H
#define RESOURCE_H
#include <SFML/Config.hpp>

//------------------------------------------------------------------------------
/// All data in age of empires inherit from resource. A resource can be
/// a palette, a sprite, music or map descriptions. Each resource seems to
/// have its individual id.
//
class Resource
{

public:
  //----------------------------------------------------------------------------
  /// Resource types
  enum Type {TYPE_UNDEFINED, TYPE_GRAPHIC};
  
  //----------------------------------------------------------------------------
  /// Constructor
  ///
  /// @param id resources' id
  /// @param type type of the resource
  //
  Resource(sf::Uint32 id, Type type=TYPE_UNDEFINED);
  
  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~Resource();
  
  //----------------------------------------------------------------------------
  /// Gets resources' id
  ///
  /// @return id of resource
  //
  sf::Uint32 getId() const;
  
  //----------------------------------------------------------------------------
  virtual void load() {}
  
  //----------------------------------------------------------------------------
  /// Returns type of the resource
  ///
  /// @return type
  //
  Type getType() const;
  
  //----------------------------------------------------------------------------
  bool isLoaded() const;
protected:
  //----------------------------------------------------------------------------
  /// Sets resources' id
  ///
  /// @param id new id
  //
  void setId(sf::Uint32 id);
  
  //----------------------------------------------------------------------------
  void setLoaded(bool loaded);
  
private:
  sf::Uint32 id_;
  Type type_;
  
  bool loaded_;
};

#endif // RESOURCE_H
