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

/*
 *  TODO: Config file for logger (loglevel, log method)
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <iostream>
#include <chrono>

//------------------------------------------------------------------------------
/// Simple logging class
//
class Logger
{

public:
    enum LogLevel {
        L_INFO = 0, // Informational messages that highlight the process
        L_DEBUG = 1, // Messages that are most useful for debugging
        L_WARNING = 2, // Messages that designate potential harmful situations
        L_ERROR = 3, // Malfunctions which allows the application to continue
        L_FATAL = 4, // Malfunctions that break the application
        L_OFF = 5 // No messages at all
    };

    //----------------------------------------------------------------------------
    /// Returns the static root logger.
    ///
    /// @return root logger
    //
    static Logger &getRootLogger(void);

    //----------------------------------------------------------------------------
    /// Returns specific logger that prints additionally its name before log info
    /// TODO
    ///
    /// @return specific logger
    //
    static Logger &getLogger(std::string name);

    //----------------------------------------------------------------------------
    /// Set the overall loglevel to print. All lower log levels will be shown.
    /// E.g. if loglevel is L_WARNING, then messages with level L_ERROR and
    /// L_FATAL will also be shown.
    ///
    /// @param loglevel minimum level to log
    //
    static void setLogLevel(LogLevel loglevel);

    static std::ostream *getGlobalOutputStream(void);
    static void setGlobalOutputStream(std::ostream &ostream);

    //----------------------------------------------------------------------------
    /// Logs messages which aren't very important, but they highlight the
    /// program status.
    ///
    /// @param msg message to print
    //
    void info(const std::string &msg);
    template <typename... Types>
    void info(const char *fmt, Types... args)
    {
        log(L_INFO, fmt, args...);
    }

    //----------------------------------------------------------------------------
    /// Messages crucial for debugging can be printed using this method.
    ///
    /// @param msg message to print
    //
    void debug(const std::string &msg);
    template <typename... Types>
    void debug(const char *fmt, Types... args)
    {
        log(L_DEBUG, fmt, args...);
    }

    //----------------------------------------------------------------------------
    /// Message that could interfere the programms behaviour should be printed
    /// using this method.
    ///
    /// @param msg message to print
    //
    void warn(const std::string &msg);
    template <typename... Types>
    void warn(const char *fmt, Types... args)
    {
        log(L_WARNING, fmt, args...);
    }

    //----------------------------------------------------------------------------
    /// Method for printing information about a malfunction which are serious
    /// but lets the programm continue.
    ///
    /// @param msg message to print
    //
    void error(const std::string &msg);
    template <typename... Types>
    void error(const char *fmt, Types... args)
    {
        log(L_ERROR, fmt, args...);
    }

    //----------------------------------------------------------------------------
    /// Prints messages that crashes the program.
    ///
    /// @param msg message to print
    //

    template <typename... Types>
    void fatal(const char *fmt, Types... args)
    {
        log(L_FATAL, fmt, args...);
    }
    void fatal(const std::string &msg);

protected:
    void log(LogLevel logLevel, const std::string &format);

    void printLog(const char *format)
    {
        *global_out_ << format << std::endl;
    }

    template <typename ValueType, typename... Types>
    void printLog(const char *format, ValueType value, Types... arguments)
    {

        for (; *format != '\0'; format++) {
            if (*format == '%') {
                *global_out_ << value;

                printLog(format + 1, arguments...);
                return;
            }

            *global_out_ << *format;
        }
    }

    template <typename... Types>
    void log(LogLevel loglevel, const char *format, Types... arguments)
    {
        if (loglevel < Logger::LOG_LEVEL) {
            return;
        }

        *global_out_ << getLogLevelName(loglevel) << ": ";
        printLog(format, arguments...);
    }

    std::string getLogLevelName(LogLevel loglevel);

private:
    Logger();
    virtual ~Logger();

    static std::ostream *global_out_;

private:
    static LogLevel LOG_LEVEL;
};

class LifeTimePrinter
{
public:
    LifeTimePrinter(const std::string &name, Logger &logger) : m_name(name), m_logger(logger) {
        m_startTime = std::chrono::steady_clock::now();
    }

    ~LifeTimePrinter() {
        std::chrono::steady_clock::duration elapsed = std::chrono::steady_clock::now() - m_startTime;

        m_logger.debug("% %ms", m_name, std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count());
    }

private:
    std::chrono::steady_clock::time_point m_startTime;
    std::string m_name;
    Logger &m_logger;
};

#ifdef _MSC_VER
#define TIME_THIS LifeTimePrinter lifetime_printer(__FUNCTION__, log)
#else
#define TIME_THIS LifeTimePrinter lifetime_printer(__PRETTY_FUNCTION__, log)
#endif

#endif /* LOGGER_H_ */
