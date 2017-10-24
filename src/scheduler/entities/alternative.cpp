#include <scheduler/entities/alternative.hpp>

#include <scheduler/entities/job.hpp>
#include <scheduler/entities/operation.hpp>

namespace specops {

Alternative::Alternative(Operation* operation, identifier id):
        Entity{id},
        operation{operation},
        operationId{operation->getId()},
        jobId{operation->getJob()->getId()},
        setup{0},
        machine_proto{nullptr} {
}

std::istream& Alternative::read(std::istream& is) {
    is >> machine >> duration;
    machine--; // 1-indexed
    return is;
}

void Alternative::read(specops::proto::SchedulerMessage* msg,
                       specops::proto::ProcessStep* process_step_proto,
                       identifier machine,
                       specops::proto::Machine* machine_proto) {
    this->machine = machine;
    this->machine_proto = machine_proto;

    duration = process_step_proto->cycle_duration();
    setup = process_step_proto->setup_duration();
}

}
