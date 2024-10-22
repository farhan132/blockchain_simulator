#include "simulator.h"
#include <iostream>
using namespace std;
Node::Node(int b, BlockchainNetwork* bcn, long long sd) {
    base = b;
    difficulty = 700000;
    bcNetwork = bcn;
    rndEngine.seed(sd);
    id = sd;
}

Block *Node::getLatestBlock() {
    return latestBlock;
}

void Node::setLatestBlock(Block *block) {
    latestBlock = block;
    if(rndEngine() % 10000 == 0) {
        cout << "Current average time to mine block in network: " << 1.0 *  bcNetwork-> curTime / block->getPositionAtLedger() << endl;
    }
    if(block->getPositionAtLedger() - lastUpdatedBlockPosition > bcNetwork-> difficultyUpdateInterval) {
        long double takenTime = bcNetwork-> curTime - lastDifficultyUpdateTime;
        long double shouldTake = bcNetwork-> expectedMineTime * (block->getPositionAtLedger() - lastUpdatedBlockPosition); 


        // cout <<id << " => From " << 1.00 * difficulty/base << " ";
        difficulty = ceil((shouldTake / takenTime) * difficulty);

        lastDifficultyUpdateTime = bcNetwork-> curTime;
        lastUpdatedBlockPosition = block->getPositionAtLedger();
        // cout << "Difficulty updated to " << 1.00 * difficulty/base << "---- " << takenTime << " " << shouldTake << endl;; 
        if(difficulty == 0) {
            cout << "ERRORRRRR" << " " << takenTime << " " << shouldTake << endl;;
            exit(0);
        }
    }
}

long long Node::randomBlockMineTime() {
    long double bs = base;
    long double dif = difficulty;
    long double p = bs / dif;
    geometric_distribution<long long> gd(p);
    return gd(rndEngine) + 1; 
}
