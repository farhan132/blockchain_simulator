#include <vector>
class Block {
public:
    Block(long long, int, Block*);
    Block *getPreviousBlock();
    long long getBlockHash();
    int getPositionAtLedger();
private:
    long long blockHash; 
    int positionAtLedger;
    Block *previousBlock;

};

class Node {
public:
    std::vector<int> adj;
    int base; //in the current implementation, it denotes the computational capacity of the node
    Node(int);
    Block *getLatestBlock();
    void setLatestBlock(Block*);
private:
    Block* latestBlock;

};

class BlockchainNetwork {
public:
    int N; // N denotes the total node count in the network
    std::vector<Node> node; //contains the nodes of the network


    void generate(int); //generates the initial graph & initializes genesis block
    void simulate(int); //simulates the network

    //Following functions are used for printing the network status while simulation
    void print_solved(int, long long);
    void print_pool_update(int, int);
    void print_fork(int, int);
private:
    Block *genesisBlock;
};
