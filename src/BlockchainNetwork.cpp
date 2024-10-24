#include "simulator.h"
#include <iostream>
#include <random>
#include <stack>
#include <set>
using namespace std;

mt19937 rng(68);
void BlockchainNetwork::generate(int n) {
    N = n;
    for(int i = 0; i <= n; i++) {
        node.push_back(Node(300 + rng() % 201, this, i));
    }
    genesisBlock = new Block(++totalBlockCount, 1, 0, NULL);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(i == j) continue;
            int d = rng() % 100;
            if(d < 25) {
                node[i].adj.push_back(j);
            }
        }
    }
}

void BlockchainNetwork::addNode() {
    N++;
    node.push_back(Node(300 + rng() % 201, this, N));

    for(int i = 1; i < N; i++) {
        int d1 = rng() % 100;
        int d2 = rng() % 100;
        if(d1 < 25) {
            node[i].adj.push_back(N);
        }
        if(d2 < 25) {
            node[N].adj.push_back(i);
        }
    }
    node[N].setLatestBlock(node[node[N].adj[0]].getLatestBlock());
}


// Mx_T = Simulating untill Mx_T unit time

void BlockchainNetwork::simulate(int Mx_T) {
    const int W = 240;

    auto processMine = [&](int x, int curTime) {
        int nextMine = node[x].randomBlockMineTime();
        nextMine = min(nextMine, max_size - 1);
        st[(curTime + nextMine) % max_size].push(x);
        node[x].nextProcessTime = curTime + nextMine;
        node[x].nextMineTime = curTime + nextMine;
    };



    for(int i = 1; i <= N; i++) {
        int firstMine = node[i].randomBlockMineTime();
        st[firstMine % max_size].push(i);
        node[i].nextProcessTime = firstMine;
        node[i].nextMineTime = firstMine;
        node[i].setLatestBlock(genesisBlock);
    }

   
    for(int _T = 0; _T <= Mx_T; _T++) {

        curTime = _T;

        int T = _T % max_size;

        if(rng() % newNodeArrivalRate == 0) {
            addNode();
            processMine(N, _T);
        }
        

        
        while(st[T].size()) {
            int x = st[T].top(); st[T].pop();

            if(_T != node[x].nextProcessTime) continue; 
       
            bool block_updated = false;
            int par = x;

            if(!node[x].pool.empty()) {
                auto max_diff_block= node[x].pool.top(); //this will denote the block with highest ledger length
                
                node[x].pool.pop();
                while(node[x].pool.size()) {
                    auto cur = node[x].pool.top(); 
                    if(max_diff_block->getCumulativeDifficulty() < cur->getCumulativeDifficulty()) {
                        max_diff_block = cur;
                    }
                    node[x].pool.pop();
                }

                if(max_diff_block->getPositionAtLedger() > node[x].getLatestBlock()->getPositionAtLedger()) {
                    node[x].setLatestBlock(max_diff_block);
                    block_updated = true;
                }
            }


            if(!block_updated && _T == node[x].nextMineTime) {
                //mining a new block
                node[x].generateNewBlock(++totalBlockCount);
                block_updated = true;
            }

            if(block_updated) {
                //if a new block was mined by node x
                for(auto u : node[x].adj) {
                    if(node[x].getLatestBlock() == node[u].getLatestBlock()) {
                        continue;
                    }
                    node[u].nextProcessTime = (_T + W);
                    node[u].pool.push(node[x].getLatestBlock());
                    st[(T + W) % max_size].push(u);
                }
            }
            
            processMine(x, _T);
        }
    }
}


