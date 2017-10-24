#include <scheduler/algorithms/optimization/state/branching/combined_strategy.hpp>

#include <algorithm>
#include <iterator>

namespace specops {

CombinedStrategy::CombinedStrategy(std::initializer_list<BranchingStrategy::ptr> init):
        BranchingStrategy() {
    for(auto s : init) {
        strategies.push_back(s);
        s->setNeighborhood(this->neighbors);
    }
}

void CombinedStrategy::start(State* state) {
    for(auto s : strategies) {
        s->start(state);
    }
}

void CombinedStrategy::update(identifier id, Alternative* alternative, timestamp value, bool skip_setup) {
    for(auto s : strategies) {
        s->update(id, alternative, value, skip_setup);
    }
}

}
