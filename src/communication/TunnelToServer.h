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


#ifndef TUNNELTOSERVER_H
#define TUNNELTOSERVER_H
#include <deque>

class UnitStatus;
class ICommand;

//------------------------------------------------------------------------------
/// Client part of the tunnel, it can send commands and receives data about
/// the game state from the server.
//
class TunnelToServer
{
public:
  virtual ~TunnelToServer() {}
  
  virtual void sendCommand(ICommand *cmd) = 0;
  
  /// Is data queued?
  bool dataAvailable();
  
  /// Returns the first date object in queue.
  UnitStatus *getData(); //TODO auto_ptr
  
protected:
  void queueData(UnitStatus *data);
  
private:
  
  std::deque<UnitStatus *> data_;
};

#endif // ITUNNELTOSERVER_H
