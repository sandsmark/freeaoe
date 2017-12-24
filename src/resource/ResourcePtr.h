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

namespace res {

//------------------------------------------------------------------------------
/// A pointer class pointing to a Resource Object. It handles loading and
/// unloading dependend on if there are any pointers to the object or not.
//
template <class T>
class ResourcePtr //TODO
{

public:
    //----------------------------------------------------------------------------
    /// Standard constructor
    //
    ResourcePtr()
    {
    }

    //----------------------------------------------------------------------------
    /// Constructor
    ///
    /// @param resource Pointer to the resource to point at.
    //
    ResourcePtr(Resource *resource) :
        res_(resource)
    {
    }

    ResourcePtr(const ResourcePtr &other)
    {
        res_ = other.res_;
    }

    virtual ~ResourcePtr()
    {
    }

    //----------------------------------------------------------------------------
    ///
    //
    /*
  virtual ResourcePtr& operator=(Resource *other) 
  { 
    this->res_ = other; 
  }
  */

    //virtual ResourcePtr& operator=(const ResourcePtr& other);

    //----------------------------------------------------------------------------
    /// Compare pointers to the resources
    //
    virtual bool operator==(const ResourcePtr &other) const
    {
        return res_ == other.res_;
    }

    T *operator->() const
    {
        return dynamic_cast<T *>(res_);
    }
    operator bool() const {
        return (res_ != nullptr);
    }

private:
    Resource *res_;
};
}

#endif // RESOURCEPTR_H
