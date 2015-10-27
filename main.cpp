#include <iostream>
#include <list>

#include "nodeinfo.h"
#include "udpwrapper.h"


using namespace std;

const int NB_NODES = 3;

int main(int argc, char* args[])
{
    if(argc < NB_NODES*2 + 3)
    {
        cout << "Error: Not enought argument" << endl;
        return 0;
    }

    int n = std::stoi(args[NB_NODES*2 + 1]);
    string f = args[NB_NODES*2 + 2];

    list<NodeInfo> listNode;

    args = args+1; // We ignore the first argument
    for(int i=0 ; i < NB_NODES*2 ; i+=2)
    {
        listNode.push_back(NodeInfo(args[i], args[i+1]));
    }

    cout << "Loading node " << n << " with " << f << endl;

    UdpWrapper *wrapper = nullptr;
    int i=0;
    for(const NodeInfo &iter : listNode)
    {
        if(i == n)
        {
            wrapper = UdpWrapper::initialize(iter);
        }
        ++i;
    }

    while(1)
    {
        wrapper->main();
        for(const NodeInfo &iter : listNode)
        {
            if(iter.getPort() % 10 != n)
                wrapper->sendOnce(iter, "test " + std::to_string(iter.getPort()));
        }
        //wrap->receiveOnce();
    }

    return 0;
}

