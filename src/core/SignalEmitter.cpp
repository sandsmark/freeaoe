#include "SignalEmitter.h"

SignalEmitterDeathDisconnecter::~SignalEmitterDeathDisconnecter()
{
    for (SignalReceiver *receiver : m_connectedReceivers) {
        receiver->m_connectedEmitters.erase(this);
    }
}

void SignalEmitterDeathDisconnecter::removeReceiver(SignalReceiver *receiver)
{
    receiver->m_connectedEmitters.erase(this);
    m_connectedReceivers.erase(receiver);
}

void SignalEmitterDeathDisconnecter::addReceiver(SignalReceiver *receiver)
{
    receiver->m_connectedEmitters.insert(this);
    m_connectedReceivers.insert(receiver);
}

SignalReceiver::~SignalReceiver()
{
    for (SignalEmitterDeathDisconnecter *emitter : m_connectedEmitters) {
        emitter->m_connectedReceivers.erase(this);
    }
}
