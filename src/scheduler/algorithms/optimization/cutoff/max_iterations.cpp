#include <scheduler/algorithms/optimization/cutoff/max_iterations.hpp>

namespace specops {

MaxIterationsCutoff::MaxIterationsCutoff(identifier max) :
        maxIterations{max}, current{0} {
}

void MaxIterationsCutoff::reset() {
    current = 0;
}

bool MaxIterationsCutoff::stop(score) {
    return ++current > maxIterations;
}

MaxNonImprovingIterationsCutoff::MaxNonImprovingIterationsCutoff(identifier max) :
        MaxIterationsCutoff{max}, currentScore{score_max} {
}

void MaxNonImprovingIterationsCutoff::reset() {
    currentScore = score_max;
    MaxIterationsCutoff::reset();
}

bool MaxNonImprovingIterationsCutoff::stop(score s) {
    if (s < currentScore) {
        currentScore = s;
        MaxIterationsCutoff::reset();
    }
    return MaxIterationsCutoff::stop(s);
}

}
