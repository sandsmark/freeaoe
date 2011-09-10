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


#ifndef LOCALTUNNELTOCLIENT_H
#define LOCALTUNNELTOCLIENT_H

#include <communication/TunnelToClient.h>

class LocalTunnelToServer;

class LocalTunnelToClient : public TunnelToClient
{

public:
  LocalTunnelToClient();
  virtual ~LocalTunnelToClient();
  
  virtual void sendData(UnitStatus *data);
  
  void setClient(LocalTunnelToServer *client);
  
  void receiveCommand(ICommand *cmd);
    
private:
  LocalTunnelToClient(const LocalTunnelToClient& other);
  
  LocalTunnelToServer *client_;
};

#endif // LOCALTUNNELTOCLIENT_H
