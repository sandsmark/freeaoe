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

#include "FrameRegulator.h"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>


FrameRegulator::FrameRegulator() : fps_(60)
{
}

FrameRegulator::~FrameRegulator() 
{
}

int FrameRegulator::getFPS(void) const 
{
  return fps_;
}

void FrameRegulator::setFPS(int fps) 
{
  fps_ = fps;
}

void FrameRegulator::start(void) 
{
  clock_.Reset();
}

void FrameRegulator::regulate(void) 
{
  if (clock_.GetElapsedTime() < (1000 / fps_)) 
  {
    sf::Sleep((1000 / fps_) - clock_.GetElapsedTime());
  }

  clock_.Reset();
}

