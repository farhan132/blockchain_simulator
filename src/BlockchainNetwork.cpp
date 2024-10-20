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

    genesisBlock = new Block(++totalBlockCount, 1, NULL);
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
    const int Mx_Base = 50002;

    stack < int > st[Mx_Base];

    for(int i = 1; i <= N; i++) {
        int firstMine = node[i].randomBlockMineTime();
        st[firstMine].push(i);
        node[i].nextProcessTime = firstMine;
        node[i].setLatestBlock(genesisBlock);
    }

    for(int _T = 0; _T <= Mx_T; _T++) {

        curTime = _T;

        int T = _T % Mx_Base;

        if(rng() % 1000 == 0) {
            cout << "One new node joined the network." << endl;
            addNode();
            cout << "Now node count = " << node.size() << endl;
            int nextMine = node[N].randomBlockMineTime();
            nextMine = min(nextMine, Mx_Base - 1);
            st[(T + nextMine) % Mx_Base].push(N);
            node[N].nextProcessTime = _T + nextMine;
        }
        
        while(st[T].size()) {
            int x = st[T].top(); st[T].pop();

            if(_T != node[x].nextProcessTime) continue; 
            
            // cout << "Current difficulty for node  "<< x << " : " << node[x].difficulty << " at T = " << _T << " " << node[x].pool.size() << "\n";
            bool Block_up = 0;
            int par = x;

            if(node[x].pool.size()) {
                set < pair<int,int> > ST;
                auto cur = node[x].pool.top(); //this will denote the block with highest ledger length
                ST.insert({cur->getBlockHash(), cur->getPositionAtLedger()});
                node[x].pool.pop();
                while(node[x].pool.size()) {
                    auto cont = node[x].pool.top(); 
                    ST.insert({cont->getPositionAtLedger(), cont->getPositionAtLedger()});
                    if(cur->getPositionAtLedger() < cont->getPositionAtLedger()) {
                        cur = cont;
                    }
                    node[x].pool.pop();
                }

                if(ST.size() > 1) {
                    //Currently pool contains multiple new block requests
                    print_fork(x, (int)ST.size());
                    int cid = 0;
                    // for(auto [p, q] : ST) {
                    //     cout << "Chain "<< ++cid << " length = " << q << endl;
                    
                }

                if(cur->getPositionAtLedger() > node[x].getLatestBlock()->getPositionAtLedger()) {
                    node[x].setLatestBlock(cur);
                    Block_up = 1;
                    print_pool_update(x, par);
                }
            }


            if(!Block_up) {
                int P = rng() % 70;
                if(P == 0) {
                    //mining a new block
                    Block *new_block = new Block(++totalBlockCount, node[x].getLatestBlock()->getPositionAtLedger() + 1, node[x].getLatestBlock());
                    node[x].setLatestBlock(new_block);
                    Block_up = 1;
                    print_solved(x, new_block->getBlockHash());
                }
            }

            if(Block_up) {
                //if a new block was mined by node x
                for(auto u : node[x].adj) {
                    if(node[x].getLatestBlock() == node[u].getLatestBlock()) {
                        continue;
                    }
                    node[u].nextProcessTime = (_T + W);
                    node[u].pool.push(node[x].getLatestBlock());
                    st[(T + W) % Mx_Base].push(u);
                }
            }
            
            int nextMine = node[x].randomBlockMineTime();
            // cout << nextMine << " here got for "<< x << " " << 1.00 * node[x].base / node[x].difficulty << endl;
            nextMine = min(nextMine, Mx_Base - 1);

            st[(T + nextMine) % Mx_Base].push(x);
            node[x].nextProcessTime = _T + nextMine;
        }
    }


    for(int i = 0; i < node.size(); i++) {
        cout << "Node " << i << "expected time: " << 1.000 * node[i].difficulty / node[i].base << " ---- "<< node[i].difficulty << endl;
    }
}


void BlockchainNetwork::print_solved(int i, long long id){
    // cout << "Mined a new block: " << i <<" with id = "<<id<< endl; 
}
void BlockchainNetwork::print_pool_update(int i, int j){
    // cout << "Ledger Update: " << i << " (from " << j << " )" << endl;
}
void BlockchainNetwork::print_fork(int x, int sz){
    // cout << "Fork (size: " << sz << "): " << x << endl; 
}


