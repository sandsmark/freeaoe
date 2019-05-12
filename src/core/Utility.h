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

#pragma once

#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>
#include <sstream>
#include <cctype>

#ifndef _MSC_VER
#if __has_cpp_attribute(likely) && __has_cpp_attribute(likely)
#define IS_LIKELY(x) [[likely(x)]]
#define IS_UNLIKELY(x) [[unlikely(x)]]
#else
#define IS_LIKELY(x)      __builtin_expect(!!(x), 1)
#define IS_UNLIKELY(x)    __builtin_expect(!!(x), 0)
#endif
#else
#define IS_LIKELY(x)      (x)
#define IS_UNLIKELY(x)    (x)
#endif

namespace util {

inline std::string toLowercase(std::string input)
{
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}

inline std::string stringReplace(std::string string, const std::string &oldValue, const std::string &newValue)
{
    for (size_t index = 0;; index += newValue.length()) {
        index = string.find(oldValue, index);

        if (index == std::string::npos) {
            break;
        }

        string.erase(index, oldValue.length());
        string.insert(index, newValue);
    }

    return string;
}

inline std::string trimString(std::string string)
{
    string.erase(string.begin(), std::find_if(string.begin(), string.end(), [](int c) { return !std::isspace(c); }  ));
    string.erase(std::find_if(string.rbegin(), string.rend(), [](int c) { return !std::isspace(c); }).base(), string.end());
    return string;
}

inline bool stringStartsWith(const std::string &string, const std::string &prefix)
{
    return string.compare(0, prefix.size(), prefix) == 0;
}

inline std::vector<std::string> stringSplit(const std::string &string, const char delimiter)
{
    if (string.find(delimiter) == std::string::npos) {
        return {string};
    }

    std::vector<std::string> ret;
    std::istringstream stream(string);
    std::string part;
    while (std::getline(stream, part, delimiter)) {
        if (part.empty()) {
            continue;
        }

        ret.push_back(part);
    }
    if (ret.empty()) {
        return {string};
    }
    return ret;
}

// STL is a garbage fire and shitshow
// I blame boost
inline float hypot(const float a, const float b)
{
    return std::sqrt(a * a + b * b);
}

inline float hypot(const float a, const float b, const float c)
{
    return std::sqrt(a * a + b * b + c * c);
}

inline bool floatsEquals(const float a, const float b)
{
    return (std::abs(a - b) * 100000.f <= std::min(std::abs(a), std::abs(b)));
}

inline bool floatsEquals(const double a, const double b)
{
    return (std::abs(a - b) * 1000000000000. <= std::min(std::abs(a), std::abs(b)));
}

/// The escaping can be escaped if you really try to, so don't use with user input
bool openUrl(const std::string &url, std::string *error);

}

