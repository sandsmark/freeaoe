#pragma once

#include <vector>
#include <functional>
#include <cassert>

/// Because the STL APIs suck, we wrap it
template<typename TYPE>

// We name it list, because a vector in normal language (e. g. math) is something else.
struct List {
    // lower_case_shit conflicts with variable, function and member naming,
    // STL.
    using Iterator = std::vector<TYPE>::iterator;
    using ConstIterator = std::vector<TYPE>::const_iterator;

    // But STL really wants it because it is shit
    using iterator = Iterator;
    using const_iterator = ConstIterator;

    // Constructors and stuff
    List<TYPE>(List<TYPE> &&other) = default;
    List<TYPE>() = default;

    // Iterators
    inline Iterator begin() { return contents.begin(); }
    inline Iterator end() { return contents.end(); }

    inline ConstIterator begin() const { return contents.begin(); }
    inline ConstIterator end() const { return contents.end(); }

    // Size stuff
    inline bool isEmpty() const {
        // std::vector::empty() is for some reason much slower than checking
        // size...
        return contents.size() == 0;
    }

    inline size_t size() const { return contents.size(); }
    inline void resize(const size_t newSize) { contents.resize(newSize); }
    inline void clear() { contents.clear(); }

    // Easy access
    inline const TYPE &first() const { assert(!isEmpty()); return contents[0]; }
    inline const TYPE &last() const { assert(!isEmpty()); return contents.back(); }

    inline bool contains(const TYPE &item) const {
        return std::find(contents.begin(), contents.end(), item) != contents.end();
    }

    inline void prepend(const TYPE &item) { contents.insert(begin(), item); }
    inline void prepend(TYPE item) { contents.insert(begin(), std::move(item)); }

    inline void append(const TYPE &item) { contents.push_back(item); }
    inline void append(TYPE item) { contents.push_back(std::move(item)); }

    // Only appends if it isn't there already
    inline void insertUnique(const TYPE &item) {
        const ConstIterator it = std::find(contents.begin(), contents.end(), item);
        if (it != contents.end()) {
            return;
        }
        contents.push_back(item);
    }

    inline void removeLast() {
        assert(!isEmpty());
        contents.resize(size() - 1);
    }

    inline Iterator removeAt(const Iterator &it) { assert(!isEmpty()); return contents.erase(it); }

    inline void removeAt(const int position) {
        assert(position < size());
        contents.erase(begin() + position);
    }

    inline void removeFirst() {
        assert(!isEmpty());
        contents.erase(begin());
    }

    int count(const TYPE &item) const {
        const ConstIterator it = contents.begin();
        int num = 0;
        while ((it = std::find(it, contents.end(), item)) != contents.end()) {
            num++;
        }
        return num;
    }

    bool removeAll(const TYPE &item) {
        const Iterator it = std::find(contents.begin(), contents.end(), item);
        if (it == contents.end()) {
            return false;
        }

        while (it != contents.end()) {
            contents.erase(it);
            it = std::find(contents.begin(), contents.end(), item);
        }
        return true;
    }

    bool removeIf(const std::function<bool(const TYPE &item)> &function) {
        const Iterator it = contents.begin();
        bool found = false;
        while (it != contents.end()) {
            if (function(*it)) {
                it = contents.erase(it);
                found = true;
            } else {
                it++;
            }
        }
        return found;
    }

    Iterator find(const std::function<bool(const TYPE &item)> &function) {
        const Iterator it = contents.begin();
        while (it != contents.end()) {
            if (function(*it)) {
                return it;
            }
        }
        return end();
    }

    inline void takeAt(const int position) {
        assert(position < size());
        TYPE ret = std::move(contents[position]);
        contents.erase(begin() + position);
        return ret;
    }

    inline TYPE takeLast() {
        assert(!isEmpty());
        TYPE ret = std::move(contents.back());
        contents.resize(size() - 1);
        return ret;
    }

    inline TYPE takeFirst() {
        assert(!isEmpty());
        TYPE ret = std::move(contents.front());
        contents.erase(begin());
        return ret;
    }

    // No accidental copying
    List<TYPE>(const List<TYPE> &other) = delete;
    inline const List<TYPE> &operator=(const List<TYPE> &other) = delete;
    // But allow explicit copying
    List<TYPE> makeCopy() const {
        List<TYPE> ret;
        ret.contents = contents;
        return ret;
    }

    // Let it be used directly with shit that needs a std::vector
    List<TYPE>(const std::vector<TYPE> &other) : contents(other) {}
    List<TYPE>(const TYPE &val) { contents.push_back(val); }
    inline const List<TYPE> &operator=(const std::vector<TYPE> &other) { contents = other; }
    //inline operator const std::vector<TYPE> &() { return contents; }

    // and in case something needs access to this
    std::vector<TYPE> contents;
};

