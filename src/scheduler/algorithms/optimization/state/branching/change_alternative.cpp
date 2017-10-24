#include <scheduler/algorithms/optimization/state/branching/change_alternative.hpp>

#include <memory>
#include <utility>

#include <scheduler/algorithms/optimization/state/move.hpp>

namespace specops {

ChangeAlternativeStrategy::ChangeAlternativeStrategy():
        BranchingStrategy{}, solution{nullptr}, shop{nullptr} {
}

void ChangeAlternativeStrategy::start(State* state) {
    BranchingStrategy::start(state);
    solution = &(state->getSolution());
    shop = state->getShop();
}

void ChangeAlternativeStrategy::update(identifier i, Alternative* alternative, timestamp, bool) {
    if (solution == nullptr) {
        return;
    }

    identifier numAlternatives = alternative->getOperation()->getAlternativeCount();
    identifier operationId = alternative->getOperationId();
    identifier jobId = alternative->getJobId();

    for (identifier a = 0; a < numAlternatives; a++) {
        if (a != alternative->getId()) {
            auto move = std::make_shared<const ChangeAlternativeMove>(jobId,
                                                                      operationId,
                                                                      a);
            auto* newAlternative = shop->getAlternative(jobId, operationId, a);

            State::allocation_list newSolution(*solution);
            newSolution[i] = newAlternative;
            neighbors->push_back(
                std::make_shared<State>(
                    shop,
                    move,
                    std::move(newSolution)));
        }
    }
}

}
