#include <scheduler/algorithms/optimization/tabu_search.hpp>

#include <iterator>
#include <list>
#include <unordered_set>

#include <scheduler/algorithms/optimization/cutoff/max_iterations.hpp>
#include <scheduler/algorithms/optimization/state/branching/change_alternative.hpp>
#include <scheduler/algorithms/optimization/state/branching/combined_strategy.hpp>
#include <scheduler/algorithms/optimization/state/branching/pairwise_interchange.hpp>
#include <scheduler/algorithms/optimization/state/metrics/total_duration.hpp>
#include <scheduler/algorithms/optimization/state/metrics/makespan.hpp>
#include <scheduler/algorithms/optimization/state/move.hpp>
#include <iostream>

namespace specops {

TabuSearch::TabuSearch():
        cutoff{std::make_shared<MaxNonImprovingIterationsCutoff>(2000)},
        tenure{0} {
}

State::ptr TabuSearch::search(State::ptr initialState) {

    if (tenure == 0) {
        tenure = initialState->getShop()->getOperationCount();
    }

    std::unordered_set<Move::const_ptr,
                       MoveHashFunctor,
                       MoveEqualToFunctor> tabuLookup;
    std::list<Move::const_ptr> tabuList;

    Metric::ptr metric = std::make_shared<MakespanMetric>();
    BranchingStrategy::ptr strategy1 = std::make_shared<ChangeAlternativeStrategy>();
    BranchingStrategy::ptr strategy2 = std::make_shared<PairwiseInterchangeStrategy>();
    BranchingStrategy::ptr combinedStrategy =
        std::make_shared<CombinedStrategy>(
            std::initializer_list<BranchingStrategy::ptr>{strategy1, strategy2});


    State::ptr best = initialState;
    State::ptr current = initialState;

    score bestScore = best->getScore(metric.get());

    cutoff->reset();
    while(!cutoff->stop(bestScore)) {
        State::ptr currentBest = nullptr;
        score currentBestScore = score_max;

        for (auto state : *(current->getNeighbors(combinedStrategy.get()))) {

            score stateScore = state->getScore(metric.get());
            bool lookup = tabuLookup.find(state->getMove()) == std::end(tabuLookup) ||
                          stateScore < bestScore;

            if (lookup && stateScore < currentBestScore) {
                currentBest = state;
                currentBestScore = stateScore;
            }
        }

        if(currentBest != nullptr) {
            tabuLookup.insert(currentBest->getMove());
            tabuList.push_back(currentBest->getMove());
            while (!tabuList.empty() && tabuList.size() > tenure) {
                auto move = tabuList.front();
                tabuLookup.erase(move);
                tabuList.pop_front();
            }

            if(currentBestScore <= bestScore) {
                best = currentBest;
                bestScore = currentBestScore;
            }

            current = currentBest;
        } else {
            break;
        }
    }

    return best;
}

}
