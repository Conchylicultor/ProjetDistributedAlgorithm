#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>

#include "nodeinfo.h"
#include "udpwrapper.h"


using namespace std;

const int NB_NODES = 3;



std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}



int main(int argc, char* args[])
{
    if(argc < NB_NODES*2 + 3)
    {
        cout << "Error: Not enought argument" << endl;
        exit(-1);
    }

    int n = std::stoi(args[NB_NODES*2 + 1]);
    string fileName = args[NB_NODES*2 + 2];

    list<NodeInfo> listNode;

    args = args+1; // We ignore the first argument
    for(int i=0 ; i < NB_NODES*2 ; i+=2)
    {
        listNode.push_back(NodeInfo(args[i], args[i+1]));
    }

    cout << "Loading node " << n << " with " << fileName << endl;

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

    ifstream inputFile(fileName);
    if (!inputFile.is_open())
    {
        cout << "Error: cannot read the imput file: " << fileName << endl;
        exit(-1);
    }

    string line;
    while (getline(inputFile,line))
    {
        // if (brodcast.isReady())
        cout << line << '\n';

        // Parse line.
        //line.sp
        vector<string> splitList = split(line, ',');
        if (splitList.size() == 0)
        {
            continue;
        }
        if (splitList.front() == "put" && splitList.size() == 3)
        {
            cout << "Put detected: " << splitList.at(1) << "-" << splitList.at(2) << endl;
        }
        else if (splitList.front() == "get" && splitList.size() == 2)
        {
            cout << "Get detected: " << splitList.at(1) << endl;
        }
    }

    inputFile.close();

    return 0;

    while(1)
    {
        wrapper->main();
        for(const NodeInfo &iter : listNode)
        {
            if(iter.getPort() % 10 != n)
                wrapper->sendOnce(iter, "test " + std::to_string(iter.getPort()));
        }
    }

    return 0;
}

