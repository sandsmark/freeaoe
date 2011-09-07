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


#ifndef TUNNELTOCLIENT_H
#define TUNNELTOCLIENT_H

#include <deque>
#include "ICommand.h"

//------------------------------------------------------------------------------
/// Server part of the tunnel, it receives commands and can send back data about
/// the game state to the client.
//
class TunnelToClient
{
public:
  virtual ~TunnelToClient() {}
  
  /// Send data back to client  
  virtual void sendData(void *data) = 0;
  
  /// Is a command queued?
  bool commandAvailable();
  
  /// Get the first command from the queue.
  //
  ICommand *getCommand();       //TODO: auto_ptr
  
protected:
  void queueCommand(ICommand *cmd);
  
private:
  
  std::deque<ICommand *> commands_;
};

#endif // ITUNNELTOCLIENT_H
