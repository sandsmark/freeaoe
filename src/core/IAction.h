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

#ifndef IACTION_H
#define IACTION_H

#include "global/Types.h"

#include <memory>

class IAction
{
public:
    enum class Type {
        None,
        Move,
        PlaceOnMap,
        Build
    };
    const Type type = Type::None;

    virtual ~IAction();

    /// @return true if action is done
    virtual bool update(Time time) = 0;

protected:
    IAction(const Type type_);
    //isDone?
};

typedef std::shared_ptr<IAction> ActionPtr;

#endif // IACTION_H
