#pragma once

#include <unordered_map>
#include <functional>
#include <algorithm>

template<class Emitter>
struct SignalHolder;

struct SignalReceptacle
{
    SignalReceptacle(uintptr_t o, std::function<void()> f) : targetObject(o), targetFunction(f) {}
    uintptr_t targetObject;
    std::function<void()> targetFunction;
};


template<class Emitter>
struct SignalEmitter
{
    virtual ~SignalEmitter() {
        delete d;
    }

    enum class Signals {

    };


    template<typename Signal,
             class Receiver,
             typename Function>
    void connect(const Signal sig, Receiver *receiver, Function func) {
        static_assert(std::is_enum<Signal>());
        d->connections.insert({sig, {uintptr_t(receiver), std::bind(func, receiver)}});
    }

    template< typename Signal, class Receiver>
    void disconnect(Signal sig, Receiver *receiver);

    template<class Receiver>
    void disconnect(Receiver *receiver);

    template<typename Signal>
    void emit(const Signal sig);

private:
    SignalHolder<Emitter> *d = new SignalHolder<Emitter>();
};


template<class Emitter>
struct SignalHolder {
    typedef std::unordered_multimap<typename Emitter::Signals, SignalReceptacle> SignalMap;
    SignalMap connections;
};

template<class Emitter>
template<typename Signal>
void SignalEmitter<Emitter>::emit(const Signal sig)
{
    static_assert(std::is_enum<Signal>());

    typedef typename SignalHolder<Emitter>::SignalMap SignalMap;

    const std::pair<typename SignalMap::iterator, typename SignalMap::iterator> range = d->connections.equal_range(sig);
    std::for_each(range.first, range.second, [](typename SignalMap::value_type &func) {
        func.second.targetFunction();
    });
}

template<class Emitter>
template<typename Signal, class Receiver>
void SignalEmitter<Emitter>::disconnect(Signal sig, Receiver *receiver)
{
    static_assert(std::is_enum<Signal>());

    typedef typename SignalHolder<Emitter>::SignalMap SignalMap;

    for (typename SignalMap::iterator it = d->connections.begin(); it != d->connections.end();) {
        if (it->first == sig && it->second.targetObject == receiver) {
            it = d->connections.erase(it);
        } else {
            it++;
        }
    }
}

template<class Emitter>
template<class Receiver>
void SignalEmitter<Emitter>::disconnect(Receiver *receiver)
{
    typedef typename SignalHolder<Emitter>::SignalMap SignalMap;
    const uintptr_t receiverId  = uintptr_t(receiver);

    for (typename SignalMap::iterator it = d->connections.begin(); it != d->connections.end();) {
        if (it->second.targetObject == receiverId) {
            it = d->connections.erase(it);
        } else {
            it++;
        }
    }
}
