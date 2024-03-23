#include "simulator.h"
#include <iostream>
#include <queue>
#include <map>
#include <fstream>
using namespace std;

log_writer::log_writer(BlockchainNetwork *bn) {
    network = bn;
}
void log_writer::printLedger(string dr) {
    ofstream file(dr);
    if(!file.is_open()) {
        cout << "error while opening the file" << endl;
        return;
    }
    queue <Block*> q;

    map<long long, bool> mp;
    for(int i = 1; i < network->node.size(); i++) {
        if(network->node[i].getLatestBlock() == NULL) continue;
        q.push(network->node[i].getLatestBlock());
    }

    file << network->totalBlockCount << "\n";


    while(!q.empty()) {
        auto x = q.front();
        q.pop();
        if (x == NULL || x->getBlockHash() == 1 || mp[x->getBlockHash()]) continue;
        mp[x->getBlockHash()] = 1;
        file << x->getPreviousBlock()->getBlockHash() << " "<< x->getBlockHash() << "\n";
        q.push(x->getPreviousBlock());

    }

    file.close();
}
