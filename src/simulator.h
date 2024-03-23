#include <vector>
#include <string>
class Block {
public:
    Block(long long, int, Block*);
    int ttt;
    Block *getPreviousBlock();
    long long getBlockHash();
    int getPositionAtLedger();
private:
    long long blockHash = 0; 
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
    int randomBlockMineTime(long long); //returns a random amount of time the node might take to mine next block
private:
    Block* latestBlock;

};

class BlockchainNetwork {
public:
    int N; // N denotes the total node count in the network
    int totalBlockCount = 0;
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

class log_writer {
public:
    log_writer(BlockchainNetwork*);
    void printLedger(std::string); 
private:
    BlockchainNetwork *network;

};
