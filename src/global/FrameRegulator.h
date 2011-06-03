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


#ifndef FRAMEREGULATOR_H_
#define FRAMEREGULATOR_H_

#include <SFML/System/Clock.hpp>

//------------------------------------------------------------------------------
/// Class for regulation frames in the game loop
//
class FrameRegulator 
{
public:
  //----------------------------------------------------------------------------
  /// Constructor
  //
  FrameRegulator();
  
  //----------------------------------------------------------------------------
  /// Destructor
  //
  virtual ~FrameRegulator();

  //----------------------------------------------------------------------------
  /// Returns set frames per second
  ///
  /// @return frames per second
  //
  int getFPS(void) const;
  
  //----------------------------------------------------------------------------
  /// Sets max frames per second.
  ///
  /// @param fps frames per second
  //
  void setFPS(int fps);

  //----------------------------------------------------------------------------
  /// Starts the internal clock.
  //
  void start(void);
  
  //----------------------------------------------------------------------------
  /// If called in the game loop, it regulates time using sleep so that the
  /// loop cycle doesn't exceed the set fps.
  //
  void regulate(void);

private:
  int fps_;

  sf::Clock clock_;
};


#endif /* FRAMEREGULATOR_H_ */
