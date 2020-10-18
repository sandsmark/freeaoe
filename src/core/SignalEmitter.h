#pragma once

#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <algorithm>

/// Because the template magic fucks with my head:
/// The only job of SignalReceiver is to disconnect from the SignalEmitter when a receiver is deleted.
/// SignalEmitterDeathDisconnecter in turn is responsible for making sure SignalReceiver doesn't
/// have any stale connections around when the SignalEmitter is destroyed.

template<class Emitter>
struct SignalHolder;

struct SignalReceiver;

struct SignalEmitterDeathDisconnecter
{
    virtual ~SignalEmitterDeathDisconnecter();

protected:
    void removeReceiver(SignalReceiver *receiver);
    void addReceiver(SignalReceiver *receiver);

protected:
    friend struct SignalReceiver;
    std::unordered_set<SignalReceiver*> m_connectedReceivers;
};

struct SignalReceiver
{
    virtual ~SignalReceiver();
private:
    friend struct SignalEmitterDeathDisconnecter;
    std::unordered_set<SignalEmitterDeathDisconnecter*> m_connectedEmitters;
};

struct SignalReceptacle
{
    SignalReceptacle(SignalReceiver *o, std::function<void()> f) : targetObject(o), targetFunction(f) {}

    SignalReceiver *targetObject;
    std::function<void()> targetFunction;
};


template<class Emitter>
struct SignalEmitter
        : public SignalEmitterDeathDisconnecter
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
        m_connectedReceivers.insert(receiver);
        d->connections.insert({sig, {receiver, std::bind(func, receiver)}});
        addReceiver(receiver);
    }

    template< typename Signal, class Receiver>
    void disconnect(Signal sig, Receiver *receiver);

    void disconnect(SignalReceiver *receiver);

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

    bool hasConnections = false;
    for (typename SignalMap::iterator it = d->connections.begin(); it != d->connections.end();) {
        if (it->second.targetObject != receiver) {
            continue;
        }

        if (it->first == sig) {
            it = d->connections.erase(it);
        } else {
            hasConnections = true;
            it++;
        }
    }
    if (!hasConnections) {
        removeReceiver(receiver);
    }
}

template<class Emitter>
void SignalEmitter<Emitter>::disconnect(SignalReceiver *receiver)
{
    typedef typename SignalHolder<Emitter>::SignalMap SignalMap;

    m_connectedReceivers.erase(receiver);

    for (typename SignalMap::iterator it = d->connections.begin(); it != d->connections.end();) {
        if (it->second.targetObject == receiver) {
            it = d->connections.erase(it);
        } else {
            it++;
        }
    }

    removeReceiver(receiver);
}
