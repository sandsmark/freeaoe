/*
    Log handling
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

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <iostream>
#include <chrono>
#include <filesystem>

struct LogPrinter
{
    enum class LogType {
        Debug,
        Warning,
        Error,
    };

    LogPrinter(const char *funcName, const char *filename, const int linenum, const LogType type) :
        m_funcName(funcName),
        m_filename(filename),
        m_linenum(linenum)
    {
        switch(type) {
        case LogType::Debug:
            std::cout << "\033[02;32m";
            break;
        case LogType::Warning:
            std::cout << "\033[01;33m";
            break;
        case LogType::Error:
            std::cout << "\033[01;31m";
            break;
        }
    }

    inline LogPrinter &operator<<(const char *text) { std::cout << text << ' '; return *this; }
    inline LogPrinter &operator<<(const char c) { std::cout << c << ' '; return *this; }
    inline LogPrinter &operator<<(const uint8_t num) { std::cout << int(num) << ' '; return *this; }
    inline LogPrinter &operator<<(const int8_t num) { std::cout << int(num) << ' '; return *this; }
    inline LogPrinter &operator<<(const uint64_t num) { std::cout << num << ' '; return *this; }
    inline LogPrinter &operator<<(const int64_t num) { std::cout << num << ' '; return *this; }
    inline LogPrinter &operator<<(const uint32_t num) { std::cout << num << ' '; return *this; }
    inline LogPrinter &operator<<(const int32_t num) { std::cout << num << ' '; return *this; }
    inline LogPrinter &operator<<(const double num) { std::cout << num << ' '; return *this; }
    inline LogPrinter &operator<<(const bool b) { std::cout << (b ? "true " : "false "); return *this; }
    inline LogPrinter &operator<<(const std::string &str) { std::cout << '\'' << str << "' "; return *this; }

    ~LogPrinter()
    {
        std::cout << "\033[0;37m("
                  << m_funcName << " "
                  << m_filename << ":" << m_linenum
                  << ")\033[0m" << std::endl;
    }


private:
    const char *m_funcName;
    const char *m_filename;
    const int m_linenum;
};

#ifdef _MSC_VER
#define DBG LogPrinter(__FUNCTION__, __FILE__, __LINE__, LogPrinter::LogType::Debug)
#define WARN LogPrinter(__FUNCTION__, __FILE__, __LINE__, LogPrinter::LogType::Warning)
#else
#define DBG LogPrinter(__PRETTY_FUNCTION__, __FILE__, __LINE__, LogPrinter::LogType::Debug)
#define WARN LogPrinter(__PRETTY_FUNCTION__, __FILE__, __LINE__, LogPrinter::LogType::Warning)
#endif

class LifeTimePrinter
{
public:
    LifeTimePrinter(const char *funcName, const char *filename, const int linenum) :
        m_funcName(funcName),
        m_filename(filename),
        m_linenum(linenum),
        myindent(++indent)
    {
        m_startTime = std::chrono::steady_clock::now();
    }

    ~LifeTimePrinter() {
        indent--;
        std::chrono::steady_clock::duration elapsed = std::chrono::steady_clock::now() - m_startTime;

        for (int i=0; i<indent * 2; i++) std::cout << ' ';

        std::cout
                << "\033[1;36m"
                << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << " ms\t"
                << "\033[0;36m"
                << std::filesystem::path(m_filename).filename().c_str() << ":" << m_linenum
                << " \033[0;37m("
                << m_funcName
                << ")\033[0m" << std::endl;
    }

    void tick(int linenum) {
        std::chrono::steady_clock::duration elapsed = std::chrono::steady_clock::now() - m_startTime;

        for (int i=0; i<myindent * 2 + 1; i++) std::cout << ' ';
        std::cout
                << "\033[0;36m"
                << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << " ms\t"
                << std::filesystem::path(m_filename).filename().c_str() << ":" << linenum
                << " \033[0;37m("
                << m_funcName
                << ")\033[0m" << std::endl;

    }

private:
    static int indent;
    std::chrono::steady_clock::time_point m_startTime;
    const char *m_funcName;
    const char *m_filename;
    const int m_linenum;
    int myindent;
};

#define TIME_THIS LifeTimePrinter lifetime_printer(__FUNCTION__, __FILE__, __LINE__)
#define TIME_TICK lifetime_printer.tick(__LINE__)

#endif /* LOGGER_H_ */
