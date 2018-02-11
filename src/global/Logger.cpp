/*
    Log handling
    Copyright (C) 2011  Armin Preiml
    Copyright (C) 2018 Martin Sandsmark

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

std::ostream *Logger::global_out_ = &std::cout;

//------------------------------------------------------------------------------
Logger &Logger::getRootLogger(void)
{
    static Logger l;
    return l;
}

//------------------------------------------------------------------------------
Logger &Logger::getLogger(std::string name)
{
    return getRootLogger();
}

//------------------------------------------------------------------------------
void Logger::setLogLevel(Logger::LogLevel loglevel)
{
    Logger::LOG_LEVEL = loglevel;
}

void Logger::setGlobalOutputStream(std::ostream &ostream)
{
    global_out_ = &ostream;
}

void Logger::info(const std::string &msg)
{
    log(L_INFO, msg);
}

void Logger::debug(const std::string &msg)
{
    log(L_DEBUG, msg);
}

void Logger::warn(const std::string &msg)
{
    log(L_WARNING, msg);
}

void Logger::error(const std::string &msg)
{
    log(L_ERROR, msg);
}

void Logger::fatal(const std::string &msg)
{
    log(L_FATAL, msg);
}

std::ostream *Logger::getGlobalOutputStream(void)
{
    return global_out_;
}

//------------------------------------------------------------------------------
Logger::Logger()
{
}

//------------------------------------------------------------------------------
Logger::~Logger()
{
}

void Logger::log(LogLevel loglevel, const std::string &format)
{
    *global_out_ << getLogLevelName(loglevel) << ": " << format << std::endl;
}

//------------------------------------------------------------------------------
std::string Logger::getLogLevelName(Logger::LogLevel loglevel)
{
    static const std::string LOG_LEVEL_NAMES[] = {
        "Info   ", //LINFO
        "Debug  ",
        "Warning",
        "ERROR  ",
        "FATAL  ",
        "Off    " //LOFF
    };

    return LOG_LEVEL_NAMES[loglevel];
}
