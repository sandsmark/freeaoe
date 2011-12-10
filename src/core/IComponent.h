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


#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include <map>

#include <boost/smart_ptr/shared_ptr.hpp>
#include "Attributes.h"

class IComponent
{

public:
  static const char *COMP_RENDERABLE;
  
public:
  IComponent();
  virtual ~IComponent();
  
 // virtual const char *getCompName() const = 0;
  
  void addAttribute(const char *name, boost::shared_ptr< attr::IAttribute > attribute);
  
  boost::shared_ptr< attr::IAttribute > getAttribute(const char *name);
  
  template< class T >
  boost::shared_ptr< T > getAttribute(const char *name)
  {
    return boost::dynamic_pointer_cast< T >(getAttribute(name));
  }
  
  bool hasAttribute(const char *name);
  
private:
  typedef std::map<const char *, boost::shared_ptr< attr::IAttribute > > AttributeMap;
  AttributeMap attributes_;
};

#endif // ICOMPONENT_H
