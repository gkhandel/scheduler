/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#pragma once

#include <scheduler/algorithms/optimization/state/metrics/metric.hpp>
#include <scheduler/algorithms/optimization/state/state.hpp>
#include <scheduler/entities/alternative.hpp>
#include <scheduler/utils/types.hpp>

namespace specops {

class TotalDurationMetric : public Metric {
    public:
        TotalDurationMetric() = default;
        TotalDurationMetric(const TotalDurationMetric&);
        ~TotalDurationMetric() = default;
        void start(State*) override;
        void update(identifier, Alternative*, timestamp, bool) override;
        score getScore() override;
        Metric::ptr copy() const override;
    private:
        score current;
};

}
