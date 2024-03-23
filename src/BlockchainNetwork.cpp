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
        node.push_back(Node(300 + rng() % 201));
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

void BlockchainNetwork::simulate(int Mx_T) {
    const int W = 200;
    const int Mx_Base = 502;

    stack < int > st[Mx_Base];
    stack < int > pool[N + 1];

    long long nxt[N + 1];

    for(int i = 1; i <= N; i++){
        st[node[i].base].push(i);
        nxt[i] = node[i].base;
        node[i].setLatestBlock(genesisBlock);
    }

    for(int _T = 0; _T <= Mx_T; _T++){
        int T = _T % Mx_Base;

        while(st[T].size()){
            int x = st[T].top(); st[T].pop();

            if(_T ^ nxt[x]) continue;

            bool Block_up = 0;
            int par = x;

            if(pool[x].size()){
                set < pair<int,int> > ST;
                auto cur = node[pool[x].top()].getLatestBlock(); 
                par = pool[x].top();
                ST.insert({node[pool[x].top()].getLatestBlock()->getBlockHash(), node[pool[x].top()].getLatestBlock()->getPositionAtLedger()});
                pool[x].pop();
                while(pool[x].size()){
                    auto cont = node[pool[x].top()].getLatestBlock(); 
                    ST.insert({node[pool[x].top()].getLatestBlock()->getPositionAtLedger(), node[pool[x].top()].getLatestBlock()->getPositionAtLedger()});
                    if(cur->getPositionAtLedger() < cont->getPositionAtLedger()){
                        cur = cont;
                        par = pool[x].top();
                    }
                    pool[x].pop();
                }
                if(ST.size() > 1) {
                    print_fork(x, (int)ST.size());
                    int cid = 0;
                    for(auto [p, q] : ST) {
                        cout << "Chain "<< ++cid << " length = " << q << endl;
                    }
                }

                if(cur->getPositionAtLedger() > node[x].getLatestBlock()->getPositionAtLedger()){
                    node[x].setLatestBlock(cur);
                    Block_up = 1;
                    print_pool_update(x, par);
                }
            }


            if(!Block_up){
                int P = rng() % 70;
                if(P == 0){
                    Block *new_block = new Block(++totalBlockCount, node[x].getLatestBlock()->getPositionAtLedger() + 1, node[x].getLatestBlock());
                    node[x].setLatestBlock(new_block);
                    Block_up = 1;
                    print_solved(x, new_block->getBlockHash());
                }
            }

            if(Block_up){
                for(auto u : node[x].adj){
                    if(node[x].getLatestBlock() == node[u].getLatestBlock()){
                        continue;
                    }

                    nxt[u] = _T + W;
                    pool[u].push(par);
                    st[(T + W) % Mx_Base].push(u);
                }
            }
            st[(T + node[x].base) % Mx_Base].push(x);
            nxt[x] = _T + node[x].base;
        }
    }
}


void BlockchainNetwork::print_solved(int i, long long id){
    // cout << "Mined a new block: " << i <<" with id = "<<id<< endl; 
}
void BlockchainNetwork::print_pool_update(int i, int j){
    // cout << "Ledger Update: " << i << " (from " << j << " )" << endl;
}
void BlockchainNetwork::print_fork(int x, int sz){
    cout << "Fork (size: " << sz << "): " << x << endl; 
}


