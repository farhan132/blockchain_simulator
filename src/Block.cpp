#include "simulator.h"
Block::Block(long long _hash, int _positionAtLedger, Block *_previousBlock) {
    blockHash = _hash;
    positionAtLedger = _positionAtLedger;
    previousBlock = _previousBlock;
    ttt = 69;
}
long long Block::getBlockHash() {
    return blockHash;
}
int Block::getPositionAtLedger() {
    return positionAtLedger;
}
Block *Block::getPreviousBlock() {
    return previousBlock;
}

