#include <scheduler/algorithms/optimization/state/metrics/makespan.hpp>

#include <algorithm>
#include <iterator>

namespace specops {

MakespanMetric::MakespanMetric(const MakespanMetric& metric) :
        machineMakespans(metric.machineMakespans) {
}

void MakespanMetric::start(State* state) {
    machineMakespans.resize(state->getShop()->getMachineCount());
    std::fill(std::begin(machineMakespans), std::end(machineMakespans), 0);
    lateTime = 0;
}

void MakespanMetric::update(identifier, Alternative* alternative, timestamp start, bool skip_setup) {
    score finish = start + alternative->getDuration(skip_setup);
    machineMakespans[alternative->getMachine()] = finish;

    score due = alternative->getOperation()->getJob()->getDueDate();
    if (due > 0 && finish > due) {
        lateTime = finish - due;
    }
}

score MakespanMetric::getScore() {
    auto elem = std::max_element(std::begin(machineMakespans), std::end(machineMakespans));
    if (elem != std::end(machineMakespans)) {
        return *elem + (lateTime * 1000);
    }
    return score_max;
}

Metric::ptr MakespanMetric::copy() const {
    return std::make_shared<MakespanMetric>(*this);
}

}
