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

// Hack to make qtcreator's builtin code model handle c++17
#ifdef Q_CREATOR_RUN
#undef __cplusplus
#define __cplusplus 201703
#endif

#include <genie/Types.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <cmath>

#include "core/Logger.h"
#include "core/Utility.h"

#ifndef SFML_CONFIG_HPP
namespace sf {
    typedef unsigned char Uint8;
    typedef signed   int Int32;
    typedef unsigned int Uint32;
}
#endif

using sf::Uint32;
using sf::Uint8;

using sf::Int32;

using sf::Vector2u;

struct Size {
    float width = 0.f;
    float height = 0.f;

    Size() = default;

    Size (const float w, const float h) :
        width(w), height(h)
    {}

    explicit Size (const genie::XYZF &genieVec) : width(genieVec.x), height(genieVec.y) { }

    Size(const sf::Vector2f &sfVector) :
        width(sfVector.x), height(sfVector.y)
    {}

    Size(const sf::Vector2u &sfVector) :
        width(sfVector.x), height(sfVector.y)
    {}

    inline bool isValid() const {
        return width > 0.f && height > 0.f;
    }

    inline operator sf::Vector2f() const {
        return sf::Vector2f(width, height);
    }

    inline operator sf::Vector2u() const {
        return sf::Vector2u(width, height);
    }

    inline operator sf::FloatRect() const {
        return sf::FloatRect(0, 0, width, height);
    }

    inline Size operator/(const float divisor) const {
        return Size(width / divisor, height / divisor);
    }

    inline Size operator*(const float factor) const {
        return Size(width * factor, height * factor);
    }

    inline bool operator==(const Size &other) const {
        return (
            other.width == width &&
            other.height == height
        );
    }

    inline bool operator!=(const Size &other) const {
        return !(*this == other);
    }
};

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

    inline bool operator!=(const MapPos &other) const {
        return !(*this == other);
    }

    inline MapPos &operator+=(const MapPos &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    inline MapPos &operator-=(const MapPos &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    inline MapPos &operator+=(const Size &size) {
        x += size.width;
        y += size.height;
        return *this;
    }

    inline MapPos &operator-=(const Size &size) {
        x -= size.width;
        y -= size.height;
        return *this;
    }

    inline MapPos &operator/=(float divisor) {
        x /= divisor;
        y /= divisor;
        z /= divisor;
        return *this;
    }

    inline MapPos operator/(float divisor) const {
        MapPos ret(*this);
        ret.x /= divisor;
        ret.y /= divisor;
        ret.z /= divisor;
        return ret;
    }

    inline MapPos operator*(float multiplier) const {
        return MapPos(x * multiplier, y * multiplier, z * multiplier);
    }

    inline MapPos &operator*=(float factor) {
        x *= factor;
        y *= factor;
        z *= factor;
        return *this;
    }

    float manhattanDistance(const MapPos &other) const noexcept {
        return std::abs(other.x - x) + std::abs(other.y - y);
    }

    float distance(const MapPos &other) const noexcept {
        return util::hypot(other.x - x, other.y - y, other.z - z);
    }

    float distanceToLine(const MapPos &lineP1, const MapPos &lineP2) const {
        const float deltaX = x - lineP2.x;
        const float deltaY = y - lineP2.y;
        float lineLengthX = lineP1.x - lineP2.x;
        float lineLengthY = lineP1.y - lineP2.y;
        const float normLength = util::hypot(lineLengthX, lineLengthY);
        if (IS_UNLIKELY(!normLength)) {
            return 0;
        }
        lineLengthX /= normLength;
        lineLengthY /= normLength;
        const float alongDist = lineLengthX * deltaX + lineLengthY * deltaY;
        const float lengthSquared = deltaX  * deltaX + deltaY * deltaY;
        const float distSquared = lengthSquared - alongDist * alongDist;
        if (IS_UNLIKELY(distSquared < 0)) {
            return 0;
        }
        return std::sqrt(lengthSquared - alongDist * alongDist);
    }

    float angleTo(const MapPos &other) const {
        return atan2(other.y - y, other.x - x);
    }

    inline MapPos rounded() const noexcept {
        return MapPos(std::round(x), std::round(y), std::round(z));
    }

    inline void round() {
        x = std::round(x);
        y = std::round(y);
        z = std::round(z);
    }

    inline void clampX(const float min, const float max) noexcept {
        x = std::clamp(x, min, max);
    }

    inline void clampY(const float min, const float max) noexcept {
        y = std::clamp(y, min, max);
    }

    inline void clampZ(const float min, const float max) noexcept {
        z = std::clamp(z, min, max);
    }

    inline void clamp(const Size size) noexcept {
        x = std::clamp(x, 0.f, size.width);
        y = std::clamp(y, 0.f, size.height);
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

inline MapPos operator +(const MapPos& pos, const Size &size)
{
    return MapPos(
        pos.x + size.width,
        pos.y + size.height,
        pos.z
    );
}


inline MapPos operator -(const MapPos& pos, const Size &size)
{
    return MapPos(
        pos.x - size.width,
        pos.y - size.height,
        pos.z
    );
}


struct ScreenPos {
    ScreenPos() = default;

    explicit ScreenPos (const Size &size) :
        x(size.width),
        y(size.height)
    {}

    ScreenPos(const sf::Vector2i &v) :
        x(v.x),
        y(v.y)
    {}


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

    inline bool operator==(const sf::Vector2f &other) const {
        return (other.x == x && other.y == y);
    }

    inline ScreenPos &operator+=(const ScreenPos &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    inline ScreenPos &operator-=(const ScreenPos &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    inline ScreenPos &operator*(const double d) {
        x *= d;
        y *= d;
        return *this;
    }

    float angleTo(const ScreenPos &other) const {
        return atan2(other.y - y, other.x - x);
    }

    float distanceTo(const ScreenPos &other) const {
        return util::hypot(other.x - x, other.y - y);
    }


    /// screen position to relative map position (map(0,0,0) is on screen(0,0)
    MapPos toMap(const float z = 0.f) const;
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

inline ScreenPos operator -(const ScreenPos& pos, const Size& size)
{
    return ScreenPos(
        pos.x - size.width,
        pos.y - size.height
    );
}

inline ScreenPos MapPos::toScreen() const
{
    return ScreenPos(
        x + y,
        z + (y - x) / 2.f
    );
}

inline MapPos ScreenPos::toMap(const float z) const
{
    return MapPos(
        x / 2.0 - y,
        x / 2.0 + y,
        z
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

    ScreenRect(const sf::FloatRect &r) :
        x(r.left), y(r.top), width(r.width), height(r.height)
    {}

    ScreenRect(const float x_, const float y_, const float w_, const float h_) :
        x(x_), y(y_), width(w_), height(h_)
    {}

    ScreenRect(const ScreenPos &a, const ScreenPos &b)
    {
        x = std::min(a.x, b.x);
        y = std::min(a.y, b.y);

        width  = std::abs(a.x - b.x);
        height = std::abs(a.y - b.y);
    }

    ScreenRect(const ScreenPos &a, const Size &s)
    {
        x = a.x;
        y = a.y;
        width = s.width;
        height = s.height;
    }

    ScreenPos bounded(const ScreenPos &other) const {
        ScreenPos ret = other;

        if (ret.x < 0.f) ret.x = 0;
        if (ret.y < 0.f) ret.y = 0;
        if (ret.x > width) ret.x = width;
        if (ret.y > height) ret.y = height;

        return ret;
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
    float bottom() const {
        return y + height;
    }
    float right() const {
        return x + width;
    }
    ScreenPos bottomRight() const {
        return ScreenPos(x + width, y + height);
    }
    ScreenPos center() const {
        return ScreenPos(x + width/2, y+height/2);
    }

    bool isEmpty() const {
        return (width <= 0 || height <= 0);
    }

    Size size() const {
        return Size(width, height);
    }

    void setSize(const Size s) {
        width = s.width;
        height = s.height;
    }

    void setTopLeft(const ScreenPos &pos) {
        x = pos.x;
        y = pos.y;
    }

    inline ScreenRect &operator +=(const ScreenRect& other)
    {
        float x1 = std::min(x, other.x);
        float y1 = std::min(y, other.y);

        float x2 = std::max(x + width, other.x + other.width);
        float y2 = std::max(y + height, other.y + other.height);


        x = x1;
        y = y1;

        width  = x2 - x1;
        height = y2 - y1;

        return *this;
    }

    MapRect boundingMapRect() const;

    operator bool() const {
        return (width >= 0 && height >= 0);
    }

    bool contains(const float x_, const float y_) const {
        return (
            x_ >= x &&
            x_ <= x + width &&
            y_ >= y &&
            y_ <= y + height
        );

    }
    bool contains(const ScreenPos &point) const {
        return contains(point.x, point.y);
    }

    bool operator==(const ScreenRect &other) const {
        return x == other.x && y == other.y &&
               width == other.width && height == other.height;
    }

    bool operator!=(const ScreenRect &other) const {
        return x != other.x || y != other.y ||
               width != other.width || height != other.height;
    }

    bool overlaps(const ScreenRect &otherRect) const {
        return (
            otherRect.contains(x, y) ||
            otherRect.contains(x + width, y) ||
            otherRect.contains(x, y + height) ||
            otherRect.contains(x + width, y + height)
        ) || (
            contains(otherRect.x, otherRect.y) ||
            contains(otherRect.x + otherRect.width, otherRect.y) ||
            contains(otherRect.x, otherRect.y + otherRect.height) ||
            contains(otherRect.x + otherRect.width, otherRect.y + otherRect.height)
        );
    }

    ScreenRect intersected(const ScreenRect &otherRect) const;
};

inline ScreenRect operator +(const ScreenRect& rect, const ScreenPos& pos)
{
    ScreenRect ret = rect;
    ret.x += pos.x;
    ret.y += pos.y;
    return ret;
}

inline ScreenRect operator -(const ScreenRect& rect, const ScreenPos& pos)
{
    ScreenRect ret = rect;
    ret.x -= pos.x;
    ret.y -= pos.y;
    return ret;
}


struct MapRect {
    float x = 0;
    float y = 0;
    float z = 0;
    float width = 0;
    float height = 0;

    MapRect() = default;

    MapRect(const float x_, const float y_, const float width_, const float height_, const float z_ = 0) :
        x(x_),
        y(y_),
        z(z_),
        width(width_),
        height(height_)
    {}

    MapRect(const MapPos &pos, const Size &size) :
        x(pos.x),
        y(pos.y),
        z(pos.z),
        width(size.width),
        height(size.height)
    {}

    MapRect(const MapPos &a, const MapPos &b)
    {
        x = std::min(a.x, b.x);
        y = std::min(a.y, b.y);

        width  = std::abs(a.x - b.x);
        height = std::abs(a.y - b.y);

        z = (a.z + b.z) / 2.f;
    }

    MapPos bounded(const MapPos &other) const {
        MapPos ret = other;

        if (ret.x < 0.f) ret.x = 0;
        if (ret.y < 0.f) ret.y = 0;
        if (ret.x > width) ret.x = width;
        if (ret.y > height) ret.y = height;

        return ret;
    }

    MapPos topLeft() const {
        return MapPos(x, y, z);
    }
    MapPos topRight() const {
        return MapPos(x + width, y, z);
    }
    MapPos bottomLeft() const {
        return MapPos(x, y + height , z);
    }
    MapPos bottomRight() const {
        return MapPos(x + width, y + height, z);
    }

    MapPos center() const {
        return MapPos(x + width/2, y + height/2, z/2);
    }

    bool isEmpty() const {
        return !(width > 0 && height > 0);
    }

    ScreenRect boundingScreenRect() const;

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

    bool contains(const float otherX, const float otherY, const float otherZ = 0.f) const {
        return contains(MapPos(otherX, otherY, otherZ));
    }

    bool overlaps(const MapRect &otherRect) const {
        return (
            otherRect.contains(x, y, z) ||
            otherRect.contains(x + width, y, z) ||
            otherRect.contains(x, y + height, z) ||
            otherRect.contains(x + width, y + height, z)
        ) || (
            contains(otherRect.x, otherRect.y, z) ||
            contains(otherRect.x + otherRect.width, otherRect.y, z) ||
            contains(otherRect.x, otherRect.y + otherRect.height, z) ||
            contains(otherRect.x + otherRect.width, otherRect.y + otherRect.height, z)
        );
    }

    inline MapRect &operator +=(const MapRect& other)
    {
        float x1 = std::min(x, other.x);
        float y1 = std::min(y, other.y);

        float x2 = std::max(x + width, other.x + other.width);
        float y2 = std::max(y + height, other.y + other.height);


        x = x1;
        y = y1;

        width  = x2 - x1;
        height = y2 - y1;

        return *this;
    }

    Size size() const {
        return Size(width, height);
    }
};

inline MapRect operator -(const MapRect& rect, const MapPos& pos)
{
    MapRect ret = rect;
    ret.x -= pos.x;
    ret.y -= pos.y;
    ret.z -= pos.z;
    return ret;
}

inline MapRect operator +(const MapRect& rect, const MapPos& pos)
{
    MapRect ret = rect;
    ret.x += pos.x;
    ret.y += pos.y;
    ret.z += pos.z;
    return ret;
}

/// Time in milliseconds
typedef int64_t Time;

inline MapRect ScreenRect::boundingMapRect() const
{
    const float x1 = bottomLeft().toMap().x;
    const float y1 = topLeft().toMap().y;
    const float x2 = topRight().toMap().x;
    const float y2 = bottomRight().toMap().y;

    return MapRect(MapPos(x1, y1), Size(x2-x1, y2-y1));
}

inline ScreenRect ScreenRect::intersected(const ScreenRect &otherRect) const
{
    const float left = std::max(x, otherRect.x);
    const float right = std::min(x + width, otherRect.x + otherRect.width);
    const float top = std::max(y, otherRect.y);
    const float bottom = std::min(y + height, otherRect.y + otherRect.height);
    return ScreenRect(ScreenPos(left, top), Size(right - left, bottom - top));
}

inline ScreenRect MapRect::boundingScreenRect() const
{
    const float x1 = topLeft().toScreen().x;
    const float y1 = bottomLeft().toScreen().y;
    const float x2 = bottomRight().toScreen().x;
    const float y2 = topRight().toScreen().y;
    return ScreenRect(ScreenPos(x1, y1), Size(x2-x1, y1-y2));
}

inline LogPrinter operator <<(LogPrinter os, const MapRect &rect) {
    const char *separator = os.separator;
    os.separator = "";
    os << "MapRect(x: "  << rect.x << ", y: " << rect.y << ", width: " << rect.width << ", height: " << rect.height << ", z:" << rect.z << ")" << separator;
    os.separator = separator;
    return os;
}

inline LogPrinter operator <<(LogPrinter os, const ScreenRect &rect) {
    const char *separator = os.separator;
    os.separator = "";
    os << "ScreenRect(x: "  << rect.x << ", y: " << rect.y << ", width: " << rect.width << ", height: " << rect.height << ")" << separator;
    os.separator = separator;
    return os;
}

inline LogPrinter operator <<(LogPrinter os, const Size &size) {
    const char *separator = os.separator;
    os.separator = "";
    os << "Size(width: " << size.width << ", height: " << size.height << ")" << separator;
    os.separator = separator;
    return os;
}

inline LogPrinter operator <<(LogPrinter os, const MapPos &pos) {
    const char *separator = os.separator;
    os.separator = "";
    os << "MapPos(x: " << pos.x << ", y: " << pos.y << ", z: " << pos.z << ")" << separator;
    os.separator = separator;
    return os;
}


inline LogPrinter operator <<(LogPrinter os, const ScreenPos &pos) {
    const char *separator = os.separator;
    os.separator = "";
    os << "ScreenPos(x: " << pos.x << ", y: " << pos.y << ")" << separator;
    os.separator = separator;
    return os;
}
