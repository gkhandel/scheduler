/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#pragma once

#include <memory>
#include <ostream>
#include <utility>
#include <vector>

#include <scheduler/algorithms/optimization/state/metrics/metric.hpp>
#include <scheduler/algorithms/optimization/state/move.hpp>
#include <scheduler/algorithms/optimization/state/state_observer.hpp>
#include <scheduler/entities/shop.hpp>
#include <scheduler/utils/types.hpp>

namespace specops {

class BranchingStrategy;

class State {
    public:
        using ptr = std::shared_ptr<State>;
        using allocation_list = std::vector<Alternative*>;
        using neighborhood = std::shared_ptr<std::vector<ptr>>;
        State(Shop*, Move::const_ptr, allocation_list);
        ~State() = default;
        Move::const_ptr getMove() const;
        neighborhood getNeighbors(BranchingStrategy*);
        score getScore(Metric*);
        Shop* getShop();
        const allocation_list& getSolution();
        void notify(StateObserver*);
        std::ostream& write(std::ostream&) const;
    protected:
        Shop* shop;
        Move::const_ptr move;
        allocation_list solution;
};

}

namespace std {

ostream& operator << (ostream&, const specops::State&);

}
