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
#include "Utility.h"
#include <global/Types.h>


//TODO: Do I need attributes? Move it to Entity?
class IComponent
{

public:
  static const char *COMP_RENDERABLE;
  
public:
  IComponent();
  virtual ~IComponent();
  
 // virtual const char *getCompName() const = 0;
  /*
  void addAttribute(const std::string name, AttributePtr attribute);
  
  template< class T >
  void addAttribute(const std::string &name, boost::shared_ptr< T > attribute)
  {
    AttributePtr ptr = boost::dynamic_pointer_cast< IAttribute >(attribute);
    addAttribute(name, ptr);
  }
    
  AttributePtr getAttribute(const std::string &name);
  
  template< class T >
  boost::shared_ptr< T > getAttribute(const std::string &name)
  {
    AttributePtr attr_base = getAttribute(name);
    boost::shared_ptr< T > attr = boost::dynamic_pointer_cast< T >(attr_base);
    return attr;
  }
  
  bool hasAttribute(const std::string &name);
  */
  
  virtual void update(Time time) {}
  
private:
  typedef std::map<const char *, AttributePtr, util::cstr_comp > AttributeMap;
  AttributeMap attributes_;
};

typedef boost::shared_ptr< IComponent > ComponentPtr;

#endif // ICOMPONENT_H
