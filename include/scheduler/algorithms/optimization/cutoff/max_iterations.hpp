/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#pragma once

#include <scheduler/algorithms/optimization/cutoff/cutoff.hpp>
#include <scheduler/utils/types.hpp>

namespace specops {

class MaxIterationsCutoff : public Cutoff {
    public:
        MaxIterationsCutoff(identifier);
        ~MaxIterationsCutoff() = default;
        virtual void reset() override;
        virtual bool stop(score) override;
    private:
        const identifier maxIterations;
        identifier current;
};

class MaxNonImprovingIterationsCutoff : public MaxIterationsCutoff {
    public:
        MaxNonImprovingIterationsCutoff(identifier);
        ~MaxNonImprovingIterationsCutoff() = default;
        void reset() override;
        bool stop(score) override;
    private:
        score currentScore;
};

}
