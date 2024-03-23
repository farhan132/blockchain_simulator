#include "simulator.h"
using namespace std;
Node::Node(int b) {
    base = b;
}

Block *Node::getLatestBlock() {
    return latestBlock;
}

void Node::setLatestBlock(Block *block) {
    latestBlock = block;
}

int Node::randomBlockMineTime(long long randVal) {
    return randVal % 100 + (base - 100); 
}
