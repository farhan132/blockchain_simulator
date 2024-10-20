#include "simulator.h"
#include <iostream>
using namespace std;
Node::Node(int b, BlockchainNetwork* bcn, long long sd) {
    base = b;
    difficulty = 700000;
    bcNetwork = bcn;
    rndEngine.seed(sd);
}

Block *Node::getLatestBlock() {
    return latestBlock;
}

void Node::setLatestBlock(Block *block) {
    latestBlock = block;
    if(block->getPositionAtLedger() % bcNetwork-> difficultyUpdateInterval == 0) {
        long double takenTime = bcNetwork-> curTime - lastDifficultyUpdateTime;
        long double shouldTake = bcNetwork-> expectedMineTime * bcNetwork-> difficultyUpdateInterval;

        cout << "From " << difficulty << " ";
        difficulty = ceil((shouldTake / takenTime) * difficulty);

        lastDifficultyUpdateTime = bcNetwork-> curTime;
        cout << "Difficulty updated to " << difficulty << "---- " << takenTime << " " << shouldTake << endl;; "\n";
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
