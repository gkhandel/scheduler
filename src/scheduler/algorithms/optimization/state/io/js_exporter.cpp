/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#include <scheduler/algorithms/optimization/state/io/js_exporter.hpp>

#include <scheduler/algorithms/optimization/state/state.hpp>

namespace specops {

JSExporter::JSExporter(std::ostream& stream):
        out(&stream) {
}

void JSExporter::start(State* state) {
    machines = state->getShop()->getMachineCount();
    (*out) << "var tasks = [";
    for (auto fixedJob : *(state->getShop()->getFixedJobs())) {
        (*out) << "{\"startDate\":" << fixedJob.start
               << ",\"endDate\":" << fixedJob.end
               << ",\"taskName\":\"Machine " << fixedJob.machine
               << "\",\"text\":\"\",\"class\":\"nojob\"},";
    }
    (*out) << std::endl;
}

void JSExporter::update(identifier, Alternative* alternative, timestamp start, bool skip_setup) {
    timestamp end = start + alternative->getDuration(skip_setup);
    identifier machine = alternative->getMachine();
    identifier job = alternative->getJobId();
    identifier operation = alternative->getOperationId();

    (*out) << "{\"startDate\":" << start
           << ",\"endDate\":" << end
           << ",\"taskName\":\"Machine " << machine
           << "\",\"text\":\"J" << job << "-" << operation
           << "\",\"class\":\"job" << job <<"\"},";
    (*out) << std::endl;
}

void JSExporter::end() {
    (*out) << "];";
    (*out) << std::endl;
    (*out) << "var machineNames = [";
    for (identifier i = 0; i < machines; i++) {
        (*out) << "\"Machine " << i << "\", ";
    }
    (*out) << "];";
    (*out) << std::endl;
}

}
