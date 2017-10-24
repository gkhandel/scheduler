#include <scheduler/entities/operation.hpp>

#include <scheduler/entities/job.hpp>
#include <scheduler/entities/shop.hpp>

namespace specops {

Operation::Operation(Job* job, identifier id):
        Entity{id}, job{job}, process_step_proto{nullptr}, blocked{false} {
}

Alternative* Operation::getMaxDurationAlternative() {
    if (blocked) {
        return nullptr;
    }

    Alternative* alternative = nullptr;
    timerange duration = -1;

//    for (const auto& current : alternatives) {
//        if (current->getDuration(false) < duration || duration == -1) {
//            alternative = current.get();
//            duration = current->getDuration(false);
//        }
//    }

    std::vector<Alternative*> listOfAlternatives;
    std::vector<timerange> listOfDurations;

    for (const auto& current : alternatives) {
        if (current->getDuration(false) <= duration || duration == -1) {
            listOfAlternatives.push_back(current.get());
            listOfDurations.push_back(current->getDuration(false));
            duration = current->getDuration(false);
        }
    }
    if(listOfAlternatives.size() == 0) { return alternative; }

    int index = rand() % listOfAlternatives.size();
    alternative = listOfAlternatives.at(index);
    return alternative;
}

std::istream& Operation::read(std::istream& is) {
    alternatives.clear();

    identifier alternativesNumber;
    is >> alternativesNumber;

    for (identifier a = 0; a < alternativesNumber; a++) {
        auto alternative = std::make_shared<Alternative>(this, a);
        is >> *alternative;
        alternatives.push_back(alternative);
    }
    return is;
}

void Operation::read(Shop* shop,
                     specops::proto::SchedulerMessage* msg,
                     specops::proto::ProcessStep* process_step_proto) {
    this->process_step_proto = process_step_proto;

    std::string* allocated_machine_id = nullptr;
    timestamp execution_window = msg->current_timestamp() + msg->execution_delay();

    if (process_step_proto->allocated()) {
        timestamp start = process_step_proto->start_time();
        if (process_step_proto->status() != specops::proto::ProcessStep::NOT_STARTED) {
            blocked = true;
            shop->allocatedOperation(job,
                                     getId(),
                                     process_step_proto->machine_id(),
                                     start,
                                     process_step_proto->end_time());
            return;
        } else if (start < execution_window) {
            in_schedule_window = true;
            allocated_machine_id = process_step_proto->mutable_machine_id();
        }
    }

    rpm required_rpm = process_step_proto->required_rpm();
    auto machine_type = process_step_proto->machine_type();
    identifier machines = msg->machines_size();
    identifier alternative_id = 0;

    while (true) {
        for (identifier m = 0; m < machines; ++m) {
            auto* machine_proto = msg->mutable_machines(m);
            if (machine_type == machine_proto->machine_type() &&
                machine_proto->status() == specops::proto::Machine::ONLINE &&
                required_rpm <= machine_proto->current_max_rpm()) {

                if (allocated_machine_id != nullptr &&
                    allocated_machine_id->compare(machine_proto->id()) != 0) {
                    continue;
                }

                auto alternative = std::make_shared<Alternative>(this, alternative_id++);
                alternative->read(msg, process_step_proto, m, machine_proto);
                alternatives.push_back(alternative);
            }
        }
        if (in_schedule_window && alternatives.empty()) {
            in_schedule_window = false;
            allocated_machine_id = nullptr;
            continue;
        }
        break;
    }

    identifier tool_size = process_step_proto->tool_types_size();
    for (identifier t = 0; t < tool_size; ++t) {
        tools.push_back(process_step_proto->tool_types(t));
    }

}

}
