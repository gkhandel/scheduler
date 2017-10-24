/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#pragma once

#include <scheduler/algorithms/optimization/state/state.hpp>
#include <scheduler/entities/shop.hpp>

namespace specops {

class InitialState : public State {
    public:
        InitialState(Shop*);
        ~InitialState() = default;
};

}
