/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#pragma once

#include <scheduler/entities/alternative.hpp>
#include <scheduler/utils/types.hpp>

namespace specops {

class State;

class StateObserver {
    public:
        using ptr = std::shared_ptr<StateObserver>;
        virtual ~StateObserver() = 0;
        virtual void start(State*) {};
        virtual void update(identifier, Alternative*, timestamp, bool) = 0;
        virtual void end() {};
};

}
