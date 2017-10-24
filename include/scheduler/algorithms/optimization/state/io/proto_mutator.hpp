/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#pragma once

#include <ostream>

#include <scheduler/algorithms/optimization/state/state_observer.hpp>
#include <scheduler/utils/types.hpp>

namespace specops {

class ProtoMutator : public StateObserver {
    public:
        ProtoMutator() = default;
        ~ProtoMutator() = default;
        void update(identifier, Alternative*, timestamp, bool) override;
};

}
