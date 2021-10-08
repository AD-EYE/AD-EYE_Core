//
// Created by adeye on 2021-10-08.
//

#include <iostream>

#include "active_nodes_checker.h"

void TestIncrement() {
    ActiveNodeChecker active_node_checker(1,1,4,4);
    std::cout << "active_node_checker value: " << active_node_checker.isFaulty() << std::endl;
    active_node_checker.updateCounter();
    active_node_checker.updateCounter();
    active_node_checker.updateCounter();
    active_node_checker.updateCounter();
    std::cout << "active_node_checker value: " << active_node_checker.isFaulty() << std::endl;
    active_node_checker.updateCounter();

}


int main(void) {
    TestIncrement();
}