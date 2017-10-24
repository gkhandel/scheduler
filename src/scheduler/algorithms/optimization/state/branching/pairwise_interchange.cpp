/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#include <scheduler/algorithms/optimization/state/branching/pairwise_interchange.hpp>

#include <memory>
#include <utility>

#include <scheduler/algorithms/optimization/state/move.hpp>

namespace specops {

PairwiseInterchangeStrategy::PairwiseInterchangeStrategy():
        BranchingStrategy{}, solution{nullptr}, shop{nullptr} {
}

void PairwiseInterchangeStrategy::start(State* state) {
    BranchingStrategy::start(state);
    solution = &(state->getSolution());
    shop = state->getShop();
}

void PairwiseInterchangeStrategy::update(identifier i, Alternative*, timestamp, bool) {
    identifier size = solution->size();
    if (solution == nullptr || i >= (size - 1)) {
        return;
    }

    identifier jobId = (*solution)[i]->getJobId();
    identifier operationId = (*solution)[i]->getOperationId();

    identifier nextJobId = (*solution)[i+1]->getJobId();
    identifier nextOperationId = (*solution)[i+1]->getOperationId();

    if(jobId != nextJobId) {
        State::allocation_list newSolution(*solution);
        auto source = newSolution[i];
        newSolution[i] = newSolution[i+1];
        newSolution[i+1] = source;

        auto move = std::make_shared<const PairwiseInterchangeMove>(jobId,
                                                                    operationId,
                                                                    nextJobId,
                                                                    nextOperationId);
        neighbors->push_back(
            std::make_shared<State>(shop,
                                    move,
                                    std::move(newSolution)));

    }

}

}
