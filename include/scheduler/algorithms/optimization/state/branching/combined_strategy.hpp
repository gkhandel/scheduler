/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#pragma once

#include <scheduler/algorithms/optimization/state/branching/strategy.hpp>
#include <scheduler/algorithms/optimization/state/state.hpp>
#include <scheduler/entities/alternative.hpp>
#include <scheduler/utils/types.hpp>

namespace specops {

class CombinedStrategy : public BranchingStrategy {
    public:
        CombinedStrategy(std::initializer_list<BranchingStrategy::ptr>);
        ~CombinedStrategy() = default;
        void start(State*) override;
        void update(identifier, Alternative*, timestamp, bool) override;
    private:
        std::vector<BranchingStrategy::ptr> strategies;
};

}
