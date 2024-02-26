#include "simulator.h"
#include <iostream>
using namespace std;
int main() {
    BlockchainNetwork BN;
    BN.generate(100);
    BN.simulate(1000);
}
