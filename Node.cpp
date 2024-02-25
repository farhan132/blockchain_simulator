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

