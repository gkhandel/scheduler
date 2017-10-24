/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#include <scheduler/entities/job.hpp>

namespace specops {

Job::Job(identifier id):
        Entity{id}, due(-1), part(nullptr) {
}

std::istream& Job::read(std::istream& is) {
    operations.clear();

    identifier operationsNumber;
    is >> operationsNumber;

    for (identifier o = 0; o < operationsNumber; o++) {
        auto operation = std::make_shared<Operation>(this, o);
        is >> *operation;
        operations.push_back(operation);
    }
    return is;
}

void Job::read(Shop* shop, specops::proto::SchedulerMessage* msg, specops::proto::Job* job_proto) {
    operations.clear();

    identifier operationsNumber = job_proto->process_steps_size();

    timestamp deadline = job_proto->deadline();
    if (deadline > 0) {
        due = deadline;
    }

    const std::string& part_id = job_proto->part_id();
    if (part_id.size() > 0) {
        part = std::make_shared<std::string>(part_id);
    }

    for (identifier o = 0; o < operationsNumber; ++o) {
        auto* process_step_proto = job_proto->mutable_process_steps(o);
        auto operation = std::make_shared<Operation>(this, o);
        operation->read(shop, msg, process_step_proto);
        operations.push_back(operation);
    }
}

}
