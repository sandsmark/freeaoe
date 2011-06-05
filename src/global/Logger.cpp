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

#include "Logger.h"

#include <iostream>
#include <fstream>

Logger::LogLevel Logger::LOG_LEVEL = L_OFF;

//------------------------------------------------------------------------------
Logger& Logger::getRootLogger(void) 
{
  static Logger l;
  return l;
}

//------------------------------------------------------------------------------
Logger& Logger::getLogger(std::string name) 
{
  return getRootLogger();
}

//------------------------------------------------------------------------------
void Logger::setLogLevel(Logger::LogLevel loglevel) 
{
  Logger::LOG_LEVEL = loglevel;
}

//------------------------------------------------------------------------------
Logger::Logger() 
{
}

//------------------------------------------------------------------------------
Logger::~Logger() 
{

}

//------------------------------------------------------------------------------
void Logger::log(Logger::LogLevel loglevel, const char *msg, ...) 
{
  va_list args;
  va_start(args,msg);

  this->log(loglevel, args, msg);
}

//------------------------------------------------------------------------------
void Logger::log(Logger::LogLevel loglevel, va_list args, const char *msg) 
{
  if (loglevel >= Logger::LOG_LEVEL)
  {
    char msgBuf[1024];                  //TODO: reserve memory on time
    vsprintf(msgBuf, msg, args);

    //TODO: should be selectable if log goes to stdout or file
    std::cout << getLogLevelName(loglevel) << ": " << msgBuf << std::endl;
  }
}

//------------------------------------------------------------------------------
void Logger::error(const char *msg, ...) {
  va_list args;
  va_start(args,msg);
  this->log(L_ERROR, args, msg);
}

//------------------------------------------------------------------------------
void Logger::warn(const char *msg, ...) {
  va_list args;
  va_start(args,msg);
  this->log(L_WARNING, args, msg);
}

//------------------------------------------------------------------------------
void Logger::info(const char *msg, ...) {
  va_list args;
  va_start(args,msg);
  this->log(L_INFO, args, msg);
}

//------------------------------------------------------------------------------
void Logger::fatal(const char *msg, ...) {
  va_list args;
  va_start(args,msg);
  this->log(L_FATAL, args, msg);
}

//------------------------------------------------------------------------------
void Logger::debug(const char *msg, ...) {
  va_list args;
  va_start(args,msg);
  this->log(L_DEBUG, args, msg);
}

//------------------------------------------------------------------------------
std::string Logger::getLogLevelName(Logger::LogLevel loglevel)
{
  static const std::string LOG_LEVEL_NAMES[] = {
    "Info   ",  //LINFO
    "Debug  ",
    "Warning",
    "ERROR  ",
    "FATAL  ",
    "Off    "   //LOFF
  };
  
  return LOG_LEVEL_NAMES[loglevel];
}

