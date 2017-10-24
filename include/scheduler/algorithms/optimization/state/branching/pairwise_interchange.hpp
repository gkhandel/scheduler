/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#pragma once

#include <vector>

#include <scheduler/algorithms/optimization/state/branching/strategy.hpp>
#include <scheduler/algorithms/optimization/state/state.hpp>
#include <scheduler/entities/alternative.hpp>
#include <scheduler/entities/shop.hpp>
#include <scheduler/utils/types.hpp>

namespace specops {

class PairwiseInterchangeStrategy : public BranchingStrategy {
    public:
        PairwiseInterchangeStrategy();
        ~PairwiseInterchangeStrategy() = default;
        void start(State*) override;
        void update(identifier, Alternative*, timestamp, bool) override;
    private:
        const State::allocation_list* solution;
        Shop* shop;
};

}
