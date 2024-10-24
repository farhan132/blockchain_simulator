#include <vector>
#include <string>
#include <stack>
#include <random>
class BlockchainNetwork;


class Block {
public:
    Block(long long, int, long long, Block*); //Block hash, block position, cumulative difficulty, prev block 
    Block *getPreviousBlock();
    long long getBlockHash();
    int getPositionAtLedger();
    long long getCumulativeDifficulty();

private:
    long long blockHash = 0; 
    int positionAtLedger;
    long long cumulativeDifficulty = 0;
    Block *previousBlock;

};


class Node {
public:
    BlockchainNetwork* bcNetwork;
    std::vector<int> adj;
    std::stack<Block*> pool; //contains the block requests of neighbor nodes
    long long nextProcessTime; //denotes the next time this node is supposed to mine a block
    long long nextMineTime = 0;
    long long base; //in the current implementation, it denotes the computational capacity of the node
    Node(int, BlockchainNetwork*, long long);
    Block *getLatestBlock();
    void setLatestBlock(Block*);
    long long randomBlockMineTime(); //returns a random amount of time the node might take to mine next block
    long long lastDifficultyUpdateTime = 0;
    long long lastUpdatedBlockPosition = 1; 
    long long difficulty;
    int id;
    void generateNewBlock(long long);
private:
    Block* latestBlock;
    std::mt19937 rndEngine;
};

class BlockchainNetwork {
public:
    int N; // N denotes the total node count in the network
    int totalBlockCount = 0;
    std::vector<Node> node; //contains the nodes of the network
    void generate(int); //generates the initial graph & initializes genesis block
    void simulate(int); //simulates the network
    void addNode();
    //Following functions are used for printing the network status while simulation
    void print_solved(int, long long);
    void print_pool_update(int, int);
    void print_fork(int, int);

    int difficultyUpdateInterval = 50; //denotes how often we update the difficulty of the nodes; its value x means we update after x, 2x, 3x, .. -th blocks are created

    long long expectedMineTime = 1000;
    long long curTime; // denotes the current time in the simulator
    static const int max_size = 50000;
    std::stack<int> st[max_size];

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
