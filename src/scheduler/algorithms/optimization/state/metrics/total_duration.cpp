#include <scheduler/algorithms/optimization/state/metrics/total_duration.hpp>

namespace specops {

TotalDurationMetric::TotalDurationMetric(const TotalDurationMetric& metric) :
        current{metric.current} {
}

void TotalDurationMetric::start(State*) {
    current = 0;
}

void TotalDurationMetric::update(identifier, Alternative* alternative, timestamp start, bool skip_setup) {
    current += start + alternative->getDuration(skip_setup);
}

score TotalDurationMetric::getScore() {
    return current;
}

Metric::ptr TotalDurationMetric::copy() const {
    return std::make_shared<TotalDurationMetric>(*this);
}

}
