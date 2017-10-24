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
