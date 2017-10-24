#pragma once

#include <scheduler/algorithms/optimization/state/state.hpp>
#include <scheduler/algorithms/optimization/cutoff/cutoff.hpp>
#include <scheduler/utils/types.hpp>

namespace specops {

class TabuSearch {
    public:
        TabuSearch();
        ~TabuSearch() = default;
        State::ptr search(State::ptr);
    private:
        Cutoff::ptr cutoff;
        tenure_type tenure;
};

}
