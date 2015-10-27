#include "udpwrapper.h"

#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring> // memset

using namespace std;

UdpWrapper *UdpWrapper::instance = nullptr;

UdpWrapper::UdpWrapper(const NodeInfo &mSender) : dataReceived(false)
{
    // Openning the socket

    mSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (mSocket < 0)
    {
        cout << "Error: cannot open a socket." << endl;
        exit(-1);
    }

    struct sockaddr_in mSrcAddr;

    // Setting the src adress and port

    memset(&mSrcAddr, 0, sizeof(mSrcAddr));
    mSrcAddr.sin_family = AF_INET;
    mSrcAddr.sin_addr.s_addr = inet_addr(mSender.getAddress().c_str());
    mSrcAddr.sin_port = htons(mSender.getPort());

    if (::bind(mSocket, (struct sockaddr*) &mSrcAddr, sizeof(mSrcAddr)) < 0)
    {
        cout << "Error: bind " << mSender.toString() << endl;
    }

    tv.tv_sec = 0;
    tv.tv_usec = 100000;
    FD_ZERO(&rset);
}

UdpWrapper::~UdpWrapper()
{
    // Close the socket
    close(mSocket);
}

UdpWrapper *UdpWrapper::initialize(const NodeInfo &sender)
{
    if(instance == nullptr)
    {
        instance = new UdpWrapper(sender);
    }
    return instance;
}

void UdpWrapper::main()
{
    FD_SET(mSocket, &rset);
    if(select(mSocket+1, &rset, NULL, NULL, &tv) < 0)
    {
        if (errno == EINTR)
            cout << "What's happend here ?" << endl;
        else
            cout << "Error: Select" << endl;
    }

    if(FD_ISSET(mSocket, &rset))
    {
        dataReceived = true;
        receiveOnce();
    }
    else
    {
        dataReceived = false;
    }
}

void UdpWrapper::sendOnce(const NodeInfo &receiver, const std::string &message)
{
    struct sockaddr_in dstAddr;

    memset(&dstAddr, 0, sizeof(dstAddr));
    dstAddr.sin_family = AF_INET;
    dstAddr.sin_addr.s_addr = inet_addr(receiver.getAddress().c_str());
    dstAddr.sin_port = htons(receiver.getPort());

    cout << "Sending packet : " << message << endl;

    if (sendto(mSocket,
               message.c_str(), message.size()+1, // +1 for the null character
               0,
               (struct sockaddr *)&dstAddr, sizeof(dstAddr))
            < 0)
    {
        cout << "Error: sending to " << receiver.toString() << endl;
    }
}

std::string UdpWrapper::receiveOnce()
{
    if(dataReceived)
    {
        struct sockaddr_in emitterAdress;
        socklen_t emitterAdressLength = sizeof(emitterAdress);

        const int MAX_SIZE_BUFFER = 30;
        char buffer[MAX_SIZE_BUFFER];

        if (recvfrom(mSocket,
                     buffer, MAX_SIZE_BUFFER, 0,
                     (struct sockaddr *) &emitterAdress, &emitterAdressLength) < 0)
        {
            cout << "Error receving data" << endl;
            exit(-1);
        }
        cout << "Data: "<< buffer << endl;
        cout << "Received from " << inet_ntoa(emitterAdress.sin_addr) << ":" << ntohs(emitterAdress.sin_port);
        cout << endl;
        cout << endl;
    }
    return "";
}
