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
#include "Unit.h"

class IAction 
{
public:
  IAction() : done_(false) {}
  
  virtual ~IAction() {}
  
  //----------------------------------------------------------------------------
  /// Updates action
  ///
  /// @return true if action is updated and false if action is already done
  //
  virtual void update() = 0;
  
  virtual bool isActive() { return true; }
  
  virtual bool isDone() { return done_; }
  
  //virtual IAction getNextAction() {}
  
  virtual bool hasNextAction() { return false; }
  
  virtual Unit* getUnit(void) = 0;

  void setDone() { done_ = true; }
  
private:
  bool done_;
};