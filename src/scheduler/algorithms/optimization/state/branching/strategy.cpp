/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#include <scheduler/algorithms/optimization/state/branching/strategy.hpp>

#include <memory>

namespace specops {

BranchingStrategy::BranchingStrategy():
        neighbors{std::make_shared<std::vector<State::ptr>>()} {
}

State::neighborhood BranchingStrategy::getNeighbors() {
    return neighbors;
}

void BranchingStrategy::start(State*) {
    neighbors->clear();
}

void BranchingStrategy::setNeighborhood(State::neighborhood n) {
    neighbors = n;
}

}
