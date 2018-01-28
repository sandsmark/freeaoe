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

#include <SFML/System.hpp>
#include <cmath>

using sf::Uint32;
using sf::Uint8;

using sf::Int32;

// for now TODO Maybe switch to boost vectors or something
using sf::Vector2u;

struct ScreenPos;

struct MapPos {
    MapPos() = default;

    MapPos (float x_, float y_, float z_ = 0) :
        x(x_),
        y(y_),
        z(z_) {}

    float x = 0.;
    float y = 0.;
    float z = 0.;

    inline bool operator==(const MapPos &other) const {
        return (
            other.x == x &&
            other.y == y &&
            other.z == z
        );
    }

    float distance(const MapPos &other) const {
        return std::sqrt((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y));
    }

    /// relative map position to screen position (map(0,0,0) is on screen(0,0)
    ScreenPos toScreen() const;
};

inline MapPos operator -(const MapPos& left, const MapPos& right)
{
    return MapPos(
        left.x - right.x,
        left.y - right.y,
        left.z - right.z
    );
}

inline MapPos operator +(const MapPos& left, const MapPos& right)
{
    return MapPos(
        left.x + right.x,
        left.y + right.y,
        left.z + right.z
    );
}


struct ScreenPos {
    ScreenPos() = default;

    ScreenPos (float x_, float y_) :
        x(x_),
        y(y_)
    {}

    float x = 0.;
    float y = 0.;

    inline operator sf::Vector2f() const {
        return sf::Vector2f(x, y);
    }

    inline bool operator!=(const sf::Vector2f &other) const {
        return (other.x != x || other.y != y);
    }

    /// screen position to relative map position (map(0,0,0) is on screen(0,0)
    MapPos toMap() const;
};

inline ScreenPos operator -(const ScreenPos& left, const ScreenPos& right)
{
    return ScreenPos(
        left.x - right.x,
        left.y - right.y
    );
}

inline ScreenPos operator +(const ScreenPos& left, const ScreenPos& right)
{
    return ScreenPos(
        left.x + right.x,
        left.y + right.y
    );
}

inline ScreenPos MapPos::toScreen() const
{
    return ScreenPos(
        x + y,
        z + (y - x) / 2
    );
}

inline MapPos ScreenPos::toMap() const
{
    return MapPos(
        x / 2.0 - y,
        x / 2.0 + y
    );

}

struct MapRect;

struct ScreenRect
{
    float x = 0;
    float y = 0;
    float width = -1;
    float height = -1;

    ScreenRect() = default;

    ScreenRect(const ScreenPos &a, const ScreenPos &b)
    {
        x = std::min(a.x, b.x);
        y = std::min(a.y, b.y);

        width  = std::abs(a.x - b.x);
        height = std::abs(a.y - b.y);
    }

    ScreenPos topLeft() const {
        return ScreenPos(x, y);
    }
    ScreenPos topRight() const {
        return ScreenPos(x + width, y);
    }
    ScreenPos bottomLeft() const {
        return ScreenPos(x, y + height);
    }
    ScreenPos bottomRight() const {
        return ScreenPos(x + width, y + height);
    }

    bool isEmpty() const {
        return !(width > 0 && height > 0);
    }

    MapRect toMap() const;

    operator bool() const {
        return (width >= 0 && height >= 0);
    }

    bool contains(const ScreenPos &point) const {
        return (
            point.x > x &&
            point.x < x + width &&
            point.y > y &&
            point.y < y + height
        );
    }

    bool operator==(const ScreenRect &other) const {
        return x == other.x && y == other.y &&
               width == other.width && height == other.height;
    }

    bool operator!=(const ScreenRect &other) const {
        return x != other.x || y != other.y ||
               width != other.width || height != other.height;
    }
};

struct MapRect {
    float x = 0;
    float y = 0;
    float width = 0;
    float height = 0;

    MapRect() = default;

    MapRect(const MapPos &a, const MapPos &b)
    {
        x = std::min(a.x, b.x);
        y = std::min(a.y, b.y);

        width  = std::abs(a.x - b.x);
        height = std::abs(a.y - b.y);
    }

    MapPos topLeft() const {
        return MapPos(x, y);
    }
    MapPos topRight() const {
        return MapPos(x + width, y);
    }
    MapPos bottomLeft() const {
        return MapPos(x, y + height);
    }
    MapPos bottomRight() const {
        return MapPos(x + width, y + height);
    }

    bool isEmpty() const {
        return !(width > 0 && height > 0);
    }

    ScreenRect toScreen() const;

    operator bool() const {
        return (width > 0 && height > 0);
    }

    bool contains(const MapPos &point) const {
        return (
            point.x > x &&
            point.x < x + width &&
            point.y > y &&
            point.y < y + height
        );
    }
};


/// Time in milliseconds
typedef unsigned int Time;

inline MapRect ScreenRect::toMap() const
{
    return MapRect(
        ScreenPos(x, y).toMap(),
        ScreenPos(x + width, y + height).toMap()
    );
}

inline ScreenRect MapRect::toScreen() const
{
    return ScreenRect(
        MapPos(x, y).toScreen(),
        MapPos(x + width, y + height).toScreen()
    );

}
