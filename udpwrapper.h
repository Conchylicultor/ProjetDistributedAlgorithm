#ifndef UDPWRAPPER_H
#define UDPWRAPPER_H

#include <arpa/inet.h>
#include <list>

#include "nodeinfo.h"

class UdpWrapper
{
private:
    UdpWrapper(const NodeInfo &mSender);
    ~UdpWrapper();

    static UdpWrapper *instance;

    int mSocket;

    bool dataReceived;
    fd_set  rset;
    struct timeval tv;

public:
    static UdpWrapper *initialize(const NodeInfo &sender);

    void main();

    void sendOnce(const NodeInfo &mReceiver, const std::string &message);
    std::string receiveOnce();
};

#endif // UDPWRAPPER_H
