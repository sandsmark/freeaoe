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

#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <filesystem>
#include <cassert>
#include <vector>

struct LogPrinter
{
    enum class LogType {
        Debug,
        Warning,
        Error,
    };

    inline std::string className(const std::string& prettyFunction)
    {
        size_t colons = prettyFunction.find("::");
        if (colons == std::string::npos)
            return "::";
        size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;
        size_t end = colons - begin;

        return prettyFunction.substr(begin,end);
    }

    LogPrinter(const char *funcName, const char *filename, const int linenum, const LogType type) :
        m_funcName(funcName),
        m_filename(filename),
        m_linenum(linenum),
        m_refs(new int)
    {
        *m_refs = 1;

#ifndef _MSC_VER
        std::cout <<  "\033[0;37m"<< className(funcName) << " ";
#endif

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

    LogPrinter() :
        m_refs(new int)
    {
        *m_refs = 1;
    }

    LogPrinter(const LogPrinter &other) :
        m_funcName(other.m_funcName),
        m_filename(other.m_filename),
        m_linenum(other.m_linenum),
        m_refs(other.m_refs)
    {
        (*m_refs)++;
    }

    inline LogPrinter &operator<<(const char *text) { std::cout << text << separator; return *this; }
    inline LogPrinter &operator<<(const char c) { std::cout << c << separator; return *this; }
    inline LogPrinter &operator<<(const uint8_t num) { std::cout << int(num) << separator; return *this; }
    inline LogPrinter &operator<<(const int8_t num) { std::cout << int(num) << separator; return *this; }
    inline LogPrinter &operator<<(const uint64_t num) { std::cout << num << separator; return *this; }
    inline LogPrinter &operator<<(const int64_t num) { std::cout << num << separator; return *this; }
    inline LogPrinter &operator<<(const uint32_t num) { std::cout << num << separator; return *this; }
    inline LogPrinter &operator<<(const int32_t num) { std::cout << num << separator; return *this; }
    inline LogPrinter &operator<<(const double num) { std::cout << num << separator; return *this; }
    inline LogPrinter &operator<<(const bool b) { std::cout << (b ? "true " : "false ") << separator; return *this; }
    inline LogPrinter &operator<<(const std::string &str) { std::cout << '\'' << str << '\'' << separator; return *this; }
    inline LogPrinter &operator<<(const void *addr) { std::cout << "0x" << std::hex << addr << std::dec << separator; return *this; }

    template<typename T>
    inline LogPrinter &operator<<(const std::vector<T> &vec) {
        std::cout << '(';
        const char *oldSep = separator;
        separator = "";
        for (size_t i=0; i<vec.size(); i++) {
            *this << vec[i];
            if (i < vec.size() - 1) {
                std::cout << " ";
            }
        }
        std::cout << ") ";
        separator = oldSep;

        return *this;
    }

    ~LogPrinter()
    {
        (*m_refs)--;
        assert(*m_refs >= 0);

        if (*m_refs == 0) {
            std::cout << "\033[0;37m("
                      << m_funcName << " "
                      << m_filename << ":" << m_linenum
                      << ")\033[0m" << std::endl;

            delete m_refs;
        }
    }

    const char *separator = " ";

private:
    const char *m_funcName = nullptr;
    const char *m_filename = nullptr;
    const int m_linenum = 0;
    int *m_refs = nullptr;
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
        m_linenum(linenum)
    {
        indent++;
        m_startTime = std::chrono::steady_clock::now();
    }

    long elapsed() {
        std::chrono::steady_clock::duration elapsed = std::chrono::steady_clock::now() - m_startTime;
        return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    }

    ~LifeTimePrinter() {
        indent--;

        std::chrono::steady_clock::duration elapsed = std::chrono::steady_clock::now() - m_startTime;
        const long elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

        if (elapsedMs < 10) {
            return;
        }

        for (size_t i=0; i<m_ticks.size(); i++) {
            for (int j=0; j<indent * 2 + 1; j++) std::cout << ' ';
            std::cout
                    << "\033[0;36m"
                    << m_ticks[i] << " ms\t"
                    << std::filesystem::path(m_filename).filename().c_str() << ":" << m_linenums[i]
                    << " \033[0;37m("
                    << m_funcName
                    << ")\033[0m" << std::endl;

        }

        for (int i=0; i<indent * 2; i++) std::cout << ' ';

        std::cout
                << "\033[1;36m"
                << elapsedMs << " ms\t"
                << "\033[0;36m"
                << std::filesystem::path(m_filename).filename().c_str() << ":" << m_linenum
                << " \033[0;37m("
                << m_funcName
                << ")\033[0m" << std::endl;
    }

    void tick(int linenum) {
        std::chrono::steady_clock::duration elapsed = std::chrono::steady_clock::now() - m_startTime;
        m_ticks.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count());
        m_linenums.push_back(linenum);
    }

private:
    static int indent;
    std::chrono::steady_clock::time_point m_startTime;
    const char *m_funcName;
    const char *m_filename;
    const int m_linenum;
    std::vector<long> m_ticks;
    std::vector<int> m_linenums;
};

#define TIME_THIS LifeTimePrinter lifetime_printer(__FUNCTION__, __FILE__, __LINE__)
#define TIME_TICK lifetime_printer.tick(__LINE__)

