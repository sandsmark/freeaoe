#pragma once

#include <unordered_set>
#include <functional>
#include <algorithm>
#include <array>

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
        d->connections[sig].push_back({receiver, std::bind(func, receiver)});
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
    typedef std::vector<SignalReceptacle> ReceptacleVector;
    typedef std::array<ReceptacleVector, Emitter::Signals::SignalCount> SignalMap;

    SignalMap connections;
};

template<class Emitter>
template<typename Signal>
void SignalEmitter<Emitter>::emit(const Signal sig)
{
    static_assert(std::is_enum<Signal>());

    for (const SignalReceptacle &receptacle : d->connections[sig]) {
        receptacle.targetFunction();
    }
}

template<class Emitter>
template<typename Signal, class Receiver>
void SignalEmitter<Emitter>::disconnect(Signal sig, Receiver *receiver)
{
    static_assert(std::is_enum<Signal>());

    typedef typename SignalHolder<Emitter>::ReceptacleVector ReceptacleVector;

    bool hasConnections = false;

    for (size_t receptacleSig = 0; receptacleSig<d->connections.size(); receptacleSig++) {
        ReceptacleVector &receptacles = d->connections[receptacleSig];
        for (typename ReceptacleVector::iterator it = receptacles.begin(); it != receptacles.end();) {
            if (it->targetObject != receiver) {
                continue;
            }

            if (receptacleSig == sig) {
                it = receptacles.erase(it);
            } else {
                hasConnections = true;
                it++;
            }
        }
    }
    if (!hasConnections) {
        removeReceiver(receiver);
    }
}

template<class Emitter>
void SignalEmitter<Emitter>::disconnect(SignalReceiver *receiver)
{
    typedef typename SignalHolder<Emitter>::ReceptacleVector ReceptacleVector;

    m_connectedReceivers.erase(receiver);

    for (ReceptacleVector &receptacles : d->connections) {
        for (typename ReceptacleVector::iterator it = receptacles.begin(); it != receptacles.end();) {
            if (it->targetObject == receiver) {
                it = receptacles.erase(it);
            } else {
                it++;
            }
        }
    }

    removeReceiver(receiver);
}
