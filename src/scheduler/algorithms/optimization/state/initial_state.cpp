/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#include <scheduler/algorithms/optimization/state/initial_state.hpp>

#include <scheduler/algorithms/optimization/state/move.hpp>

namespace specops {

InitialState::InitialState(Shop* shop):
        State{shop,
              std::make_shared<const InitialMove>(),
              State::allocation_list()} {

    const identifier jobNumber = this->shop->getJobCount();
    std::vector<identifier> jobOperations(jobNumber, 0);

    while (true) {
        specops::Alternative* alloc = nullptr;
        timerange duration = -1;

        for (identifier j = 0; j < jobNumber; j++) {
            identifier op = jobOperations[j];
            identifier operation_count = shop->getJob(j)->getOperationCount();
            if (op < operation_count) {
                auto* alternative = shop->getOperation(j, op)->getMaxDurationAlternative();
                if (alternative != nullptr) {
                    timerange d = alternative->getDuration(false);
                    if (d < duration || duration == -1) {
                        alloc = alternative;
                        duration = d;
                    }
                } else if (shop->getOperation(j, op)->isBlocked()) {
                    jobOperations[j]++;
                } else {
                    jobOperations[j] = operation_count;
                }

            }
        }

        if (alloc != nullptr) {
            jobOperations[alloc->getJobId()]++;
            solution.push_back(alloc);
        } else {
            break;
        }
    }
}

}
