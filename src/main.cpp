#include "simulator.h"
#include <iostream>
#include <cstdio>
#include <cassert>
using namespace std;
int main() {
    BlockchainNetwork BN;
    //log_writer lw(&BN);
    //lw.printLedger("../Logs/log.txt");
    freopen("input.txt", "r", stdin);

    string initial_node_count_string;
    cin >> initial_node_count_string;
    assert(initial_node_count_string == "initial_node_count:");

    int initial_node_count;
    cin >> initial_node_count;

    string simulation_time_string;
    cin >> simulation_time_string;
    assert(simulation_time_string == "simulation_time:");
    int simulation_time;
    cin >> simulation_time;


    string mine_rate_string;
    cin >> mine_rate_string;
    assert(mine_rate_string == "expected_mine_rate:");
    cin >> BN.expectedMineTime;

    string difficulty_update_interval_string;
    cin >> difficulty_update_interval_string;
    assert(difficulty_update_interval_string == "difficulty_update_interval:");
    cin >> BN.difficultyUpdateInterval;

    string new_node_arrival_rate_string;
    cin >> new_node_arrival_rate_string;
    assert(new_node_arrival_rate_string == "new_node_arrival_rate:");
    cin >> BN.newNodeArrivalRate;


    BN.generate(initial_node_count);
    BN.simulate(simulation_time);

}
