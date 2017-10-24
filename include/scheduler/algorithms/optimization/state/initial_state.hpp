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
