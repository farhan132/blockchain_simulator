#include "simulator.h"
#include <iostream>
using namespace std;
int main() {
    BlockchainNetwork BN;
    BN.generate(100);
    BN.simulate(50000);
    log_writer lw(&BN);
    lw.printLedger("../Logs/log.txt");
}
