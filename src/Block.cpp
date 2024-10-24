#include "simulator.h"
Block::Block(long long _hash, int _positionAtLedger, long long totDifficulty, Block *_previousBlock) {
    blockHash = _hash;
    positionAtLedger = _positionAtLedger;
    previousBlock = _previousBlock;
    cumulativeDifficulty = totDifficulty;
}
long long Block::getBlockHash() {
    return blockHash;
}
long long Block::getCumulativeDifficulty() {
    return cumulativeDifficulty;
}
int Block::getPositionAtLedger() {
    return positionAtLedger;
}
Block *Block::getPreviousBlock() {
    return previousBlock;
}


