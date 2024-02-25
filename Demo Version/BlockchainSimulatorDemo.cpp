#include<bits/stdc++.h>
using namespace std;

mt19937 rng(68);

namespace BlockChain {

int N;


struct Block {
    long long id;
    int length;
    Block *prev;
    Block(long long _id, int _length, Block *prv = NULL) : id(_id), length(_length), prev(prv) {}

};

struct Node {
    Block *LatestBlock;
    vector<int> Adj;
    int base;
    Node() {
        LatestBlock = NULL;
        base = 300 + rng() % 201;
    }

};


vector<Node> node;



void generate(int n) {
    N = n;

    node.resize(n + 1);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(i == j) continue;

            int d = rng() % 100;

            if(d < 25) {
                node[i].Adj.push_back(j);
            }
        }
    }
}

void print_solved(int i, long long id){
    cout << "Mined a new block: " << i <<" with id = "<<id<< endl; 
}
void print_pool_update(int i, int j){
    cout << "Ledger Update: " << i << " (from " << j << " )" << endl;
}
void print_fork(int x, int sz){
    cout << "Fork (size: " << sz << "): " << x << endl; 
}



long long genesis_id = rng();
Block *genesis = new Block(genesis_id, 1);

void Simulate(int Mx_T) {

    const int W = 50;
    const int Mx_Base = 502;

    stack < int > st[Mx_Base];
    stack < int > pool[N + 1];

    long long nxt[N + 1];

    // ...

    for(int i = 1; i <= N; i++){
        st[node[i].base].push(i);
        nxt[i] = node[i].base;
        node[i].LatestBlock = genesis;
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

                auto cur = node[pool[x].top()].LatestBlock; 
                par = pool[x].top(); ST.insert({node[pool[x].top()].LatestBlock->id, node[pool[x].top()].LatestBlock->length});

                pool[x].pop();

                while(pool[x].size()){
                    auto cont = node[pool[x].top()].LatestBlock; 
                    ST.insert({node[pool[x].top()].LatestBlock->id, node[pool[x].top()].LatestBlock->length});
                    if(cur->length < cont->length){
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

                if(cur->length > node[x].LatestBlock->length){
                    node[x].LatestBlock = cur;

                    Block_up = 1;

                    print_pool_update(x, par);
                }
            }


            if(!Block_up){
                int P = rng() % 70;
                if(P == 0){
                    Block *new_block = new Block(rng(), node[x].LatestBlock->length + 1, node[x].LatestBlock);
                    node[x].LatestBlock = new_block;
                    Block_up = 1;
                    print_solved(x, new_block->id);
                }
            }

            if(Block_up){
                for(auto u : node[x].Adj){
                    if(node[x].LatestBlock == node[u].LatestBlock){
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

};

int main() {
    BlockChain::generate(100);
    BlockChain::Simulate(10000);

    for(int i = 1; i <= 100; i++) {
        auto cur = BlockChain::node[i].LatestBlock;

        cout << "Starting for node "<<i<<endl;
        while(cur->id != BlockChain::genesis_id) {
            cout << cur -> id <<" ";
            cur = cur->prev;
        }
        cout << cur->id << endl;
    }
}
