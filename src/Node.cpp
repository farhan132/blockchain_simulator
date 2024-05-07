#include "simulator.h"
#include <iostream>
using namespace std;
Node::Node(int b, BlockchainNetwork* bcn, long long sd) {
    base = b;
    difficulty = 2000;
    bcNetwork = bcn;
    rndEngine.seed(sd);
}

Block *Node::getLatestBlock() {
    return latestBlock;
}

void Node::setLatestBlock(Block *block) {
    latestBlock = block;
    if(block->getPositionAtLedger() % bcNetwork-> difficultyUpdateInterval == 0) {
        long long takenTime = bcNetwork-> curTime - lastDifficultyUpdateTime;
        long long shouldTake = bcNetwork-> expectedMineTime * bcNetwork-> difficultyUpdateInterval;
        difficulty *=  1.00 * shouldTake / takenTime; 

        lastDifficultyUpdateTime = bcNetwork-> curTime;
        cout << "Difficulty updated to " << difficulty << "\n";
    }
}

long long Node::randomBlockMineTime() {
    long double p = 1.00 * base / difficulty;
    geometric_distribution<long long> gd(p);
    return gd(rndEngine); 
}
