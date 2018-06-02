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

#ifndef UTILITY_H
#define UTILITY_H

#include <cstring>
#include <string>
#include <algorithm>

#if __has_cpp_attribute(likely) && __has_cpp_attribute(likely)
#define IS_LIKELY(x) [[likely(x)]]
#define IS_UNLIKELY(x) [[unlikely(x)]]
#else
#define IS_LIKELY(x)      __builtin_expect(!!(x), 1)
#define IS_UNLIKELY(x)    __builtin_expect(!!(x), 0)
#endif

namespace util {

inline std::string toLowercase(std::string input)
{
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}

//------------------------------------------------------------------------------
/// Struct providing a cstring compare function.
//
struct cstr_comp
{
    bool operator()(char const *a, char const *b)
    {
        return std::strcmp(a, b) < 0;
    }
};
}

#endif //UTILITY_H
