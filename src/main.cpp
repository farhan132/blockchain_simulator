#include "simulator.h"
#include <iostream>
using namespace std;
int main() {
    BlockchainNetwork BN;
    BN.generate(1000);
    BN.simulate(2000000);
    //log_writer lw(&BN);
    //lw.printLedger("../Logs/log.txt");
}
