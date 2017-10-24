/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#pragma once

#include <scheduler/algorithms/optimization/state/state.hpp>
#include <scheduler/algorithms/optimization/state/state_observer.hpp>
#include <scheduler/entities/alternative.hpp>
#include <scheduler/utils/types.hpp>

namespace specops {

class BranchingStrategy : public StateObserver {
    public:
        using ptr = std::shared_ptr<BranchingStrategy>;
        BranchingStrategy();
        BranchingStrategy(State::neighborhood);
        ~BranchingStrategy() = default;
        virtual void start(State*) override;
        virtual void update(identifier, Alternative*, timestamp, bool) override = 0;
        State::neighborhood getNeighbors();
        void setNeighborhood(State::neighborhood);
    protected:
        State::neighborhood neighbors;
};

}
