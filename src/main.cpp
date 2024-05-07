#include "simulator.h"
#include <iostream>
using namespace std;
int main() {
    BlockchainNetwork BN;
    BN.generate(10);
    BN.simulate(1000);
    log_writer lw(&BN);
    lw.printLedger("../Logs/log.txt");
}
