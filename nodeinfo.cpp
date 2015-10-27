#include "nodeinfo.h"

#include <iostream>

using namespace std;

NodeInfo::NodeInfo(const string &address, const string &port) : mAddress(address)
{
    mPort = std::stoi(port);
    cout << "Adding node: " << mAddress << " , " << mPort<< endl;
}

int NodeInfo::getPort() const
{
    return mPort;
}

string NodeInfo::getAddress() const
{
    return mAddress;
}

string NodeInfo::toString() const
{
    return mAddress + ":" + std::to_string(mPort);
}
