#pragma once

#include <unordered_map>
#include <functional>

template<typename T>
struct SignalHolder;

template<typename T>
struct SignalEmitter
{
    virtual ~SignalEmitter() {
        delete d;
    }

    enum class Signals {

    };

    template<typename Signal>
    void connect(const Signal sig, const std::function<void()> &func) {
        static_assert(std::is_enum<Signal>());
        d->connections.insert({sig, func});
    }

    template<typename Signal>
    void disconnect(Signal sig, const std::function<void()> func);

    template<typename Signal>
    void emit(const Signal sig);

private:
    SignalHolder<T> *d = new SignalHolder<T>();
};


template<typename T>
struct SignalHolder {
    typedef std::unordered_multimap<typename T::Signals, std::function<void()>> SignalMap;
    SignalMap connections;
};

template<typename T>
template<typename Signal>
void SignalEmitter<T>::emit(const Signal sig)
{
    static_assert(std::is_enum<Signal>());

    typedef typename SignalHolder<T>::SignalMap SignalMap;

    const std::pair<typename SignalMap::iterator, typename SignalMap::iterator> range = d->connections.equal_range(sig);
    std::for_each(range.first, range.second, [](typename SignalMap::value_type &func) {
        func.second();
    });
}

template<typename ReturnType, typename... Args>
size_t getFunctionAddress(std::function<ReturnType(Args...)> f) {
    typedef ReturnType(FunctionType)(Args...);
    FunctionType ** fnPointer = f.template target<FunctionType*>();
    return (size_t) *fnPointer;
}

template<typename T>
template<typename Signal>
void SignalEmitter<T>::disconnect(Signal sig, const std::function<void()> func)
{
    static_assert(std::is_enum<Signal>());

    typedef typename SignalHolder<T>::SignalMap SignalMap;

    for (typename SignalMap::iterator it = d->connections.begin(); it != d->connections.end();) {
        if (it->first == sig && getFunctionAddress(it->second) == getFunctionAddress(func)) {
            it = d->connections.erase(it);
        } else {
            it++;
        }
    }
}
