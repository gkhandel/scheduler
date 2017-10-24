/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#pragma once

#include <memory>

#include <scheduler/algorithms/optimization/state/state_observer.hpp>
#include <scheduler/utils/types.hpp>

namespace specops {

class Metric : public StateObserver {
    public:
        using ptr = std::shared_ptr<Metric>;
        virtual ~Metric() = 0;
        virtual void start(State*) override = 0;
        virtual void update(identifier, Alternative*, timestamp, bool) override = 0;
        virtual score getScore() = 0;
        virtual ptr copy() const = 0;
};

}
