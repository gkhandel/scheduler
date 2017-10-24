#include <scheduler/algorithms/optimization/state/io/proto_mutator.hpp>

#include <scheduler/entities/alternative.hpp>
#include <scheduler/entities/operation.hpp>

namespace specops {

void ProtoMutator::update(identifier, Alternative* alternative, timestamp start, bool skip_setup) {
    timestamp end = start + alternative->getDuration(skip_setup);
    Alternative::mproto mproto = alternative->getMachineProto();
    Operation::proto proto = alternative->getOperation()->getProto();
    if (proto != nullptr && mproto != nullptr) {
        proto->set_start_time(start);
        proto->set_end_time(end);
        proto->set_allocated(true);
        proto->set_machine_id(mproto->id());
    }
}

}
