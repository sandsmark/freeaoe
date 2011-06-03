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

/*
 *  TODO: Config file for logger (loglevel, log method)
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <stdarg.h>

//Loglevels
/*const int LINFO    = 0; 
const int LDEBUG   = 1; 
const int LWARNING = 2; 
const int LERROR   = 3; 
const int LFATAL   = 4; 
const int LOFF     = 5; 
*/

class Logger {

public:
  enum LogLevel 
  {
    L_INFO    = 0, // Informational messages that highlight the process
    L_DEBUG   = 1, // Messages that are most useful for debugging
    L_WARNING = 2, // Messages that designate potential harmful situations
    L_ERROR   = 3, // Malfunctions which allows the application to continue 
    L_FATAL   = 4, // Malfunctions that break the application
    L_OFF     = 5  // No messages at all
  };
  

  static Logger& getRootLogger(void);
  static Logger& getLogger(std::string name);

  static void setLogLevel(LogLevel loglevel);

  void log(LogLevel loglevel, const char *msg, ...);

  void debug(const char *msg, ...);
  void info(const char *msg, ...);
  void warn(const char *msg, ...);
  void error(const char *msg, ...);
  void fatal(const char *msg, ...);

protected:
  void log(LogLevel loglevel, va_list vlist, const char *msg);
  
  std::string getLogLevelName(LogLevel loglevel);

private:
  Logger();
  virtual ~Logger();

private:
  static LogLevel LOG_LEVEL;

};


#endif /* LOGGER_H_ */
