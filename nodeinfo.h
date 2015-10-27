#ifndef NODEINFO_H
#define NODEINFO_H

#include <string>

class NodeInfo
{
private:
    int mPort;
    std::string mAddress;

public:
    NodeInfo(const std::string &address, const std::string &port);

    int getPort() const;
    std::string getAddress() const;

    std::string toString() const;
};

#endif // NODEINFO_H
