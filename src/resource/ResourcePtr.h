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


#ifndef RESOURCEPTR_H
#define RESOURCEPTR_H
#include "Resource.h"

namespace res
{

template <class T>
class ResourcePtr
{

public:
  ResourcePtr(Resource *resource) : res_(resource) {}
  ResourcePtr(const ResourcePtr& other);
  virtual ~ResourcePtr() {}
  //virtual ResourcePtr& operator=(const ResourcePtr& other);
  //virtual bool operator==(const ResourcePtr& other) const;
         
  T *operator->() const 
  {
    return dynamic_cast<T*>(res_);
  }
  
  
private:
    
  Resource *res_;
};

}

#endif // RESOURCEPTR_H
