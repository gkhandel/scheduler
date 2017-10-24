/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#include <scheduler/algorithms/optimization/state/state.hpp>

#include <algorithm>
#include <utility>

#include <scheduler/algorithms/optimization/state/branching/strategy.hpp>
#include <iostream>

namespace specops {

State::State(Shop* shop, Move::const_ptr move, allocation_list solution):
        shop{shop}, move{move}, solution{solution} {
}

Move::const_ptr State::getMove() const {
    return move;
}

State::neighborhood State::getNeighbors(BranchingStrategy* strategy) {
    notify(strategy);
    return strategy->getNeighbors();
}

score State::getScore(Metric* metric) {
    notify(metric);
    return metric->getScore();
}

Shop* State::getShop() {
    return shop;
}

const State::allocation_list& State::getSolution() {
    return solution;
}

void State::notify(StateObserver* observer) {
    observer->start(this);

    auto jobMakespan = shop->getJobMakespan();
    auto jobMachines = shop->getJobMachines();

    auto machineMakespan = shop->getMachineMakespan();
    auto machineParts = shop->getMachineParts();
    auto machineOperations = shop->getMachineOperations();
    auto machineRemainingLife = shop->getMachineRemainingLife();
    auto toolLibrary = shop->getToolLibrary();

    for (decltype(solution)::size_type i = 0; i < solution.size(); i++) {
        auto* alternative = solution[i];

        identifier machine = alternative->getMachine();
        Job* job = alternative->getOperation()->getJob();
        const auto* tools = alternative->getOperation()->getTools();

        partid part = job->getPartId();
        identifier job_id = job->getId();

        partid machinePart = machineParts[machine];
        bool skip_setup = false;

        if (part != nullptr && machinePart != nullptr) {
            skip_setup = *part == *machinePart &&
                         alternative->getOperationId() == machineOperations[machine];
        }

        timestamp travelTime = shop->getTravelTime(jobMachines[job_id], machine);

        timestamp makespan = std::max(machineMakespan[machine],
                                      jobMakespan[job_id] + travelTime);

        if (!alternative->getOperation()->inScheduleWindow()) {
            makespan = std::max(makespan, shop->getMinTimeToSchedule());
        }

        makespan = std::max(makespan,
                            toolLibrary.getMinMakespan(tools));

        makespan = shop->delayStart(makespan, alternative, skip_setup);


        if (machineRemainingLife[machine] < alternative->getDuration(true) && machineRemainingLife[machine] > LLONG_MIN) {

//            makespan = std::max(makespan,(score)10000000000) * (score) 2;
         makespan = (makespan+(score)(24*60*60*28));

        }

        observer->update(i, alternative, makespan, skip_setup);

        makespan += alternative->getDuration(skip_setup);

        machineMakespan[machine] = makespan;
        machineParts[machine] = part;
        machineOperations[machine] = alternative->getOperationId();

		    if(machineRemainingLife[machine] > LLONG_MIN) {

			    machineRemainingLife[machine] -= alternative->getDuration(true);
//            std::cout << "MachineLife: \n" << machineRemainingLife[machine] <<" "<<machine<< std::endl;

        }
        jobMakespan[job_id] = makespan;
        jobMachines[job_id] = machine;
        toolLibrary.updateMakespan(tools, makespan);
    }

    observer->end();
}

std::ostream& State::write(std::ostream& os) const {
    os << "<<<<< STATE\n" << *move << '\n';
    for (const auto* value : solution) {
        os << value->getJobId() << ' ';
    }
    os << '\n';
    for (const auto* value : solution) {
        os << value->getId() << ' ';
    }
    os << "\n>>>>> STATE" << std::endl;
    return os;
}

}

namespace std {

ostream& operator << (ostream& os, const specops::State& state) {
    return state.write(os);
}

}
