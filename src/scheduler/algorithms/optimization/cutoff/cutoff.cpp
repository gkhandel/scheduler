/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#include <scheduler/algorithms/optimization/cutoff/cutoff.hpp>

namespace specops {

Cutoff::~Cutoff() {
}

MultipleCutoff::MultipleCutoff(std::initializer_list<Cutoff::ptr> list) {
    for (auto c : list) {
        cutoffs.push_back(c);
    }
}

void MultipleCutoff::reset() {
    for (auto c : cutoffs) {
        c->reset();
    }
}

bool MultipleCutoff::stop(score s) {
    for (auto c : cutoffs) {
        if(c->stop(s)) {
            return true;
        }
    }
    return false;
}

}
