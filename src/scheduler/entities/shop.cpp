#include <scheduler/entities/shop.hpp>

#include <limits>
#include <utility>
#include <message.pb.h>

namespace specops {

void Shop::addFixedJob(identifier machine, timestamp start, timestamp end) {
    fixedJobs.push_back(FixedJob{machine, start, end});
    fixedJobs.sort();
}

void Shop::addTravelTime(identifier fromMachine, identifier toMachine, timerange travelTime) {
    travelTimes[std::make_pair(fromMachine, toMachine)] = travelTime;
}

timestamp Shop::delayStart(timestamp start, const Alternative* alternative, bool skip_setup) const {
    score duration = alternative->getDuration(skip_setup);
    identifier machine = alternative->getMachine();

    for (auto fixedJob : fixedJobs) {
        if (machine == fixedJob.machine) {
            if (start < fixedJob.end && start + duration > fixedJob.start) {
                start = fixedJob.end;
            }
        }
    }
    return start;
}

identifier Shop::getOperationCount() const {
    identifier count = 0;
    for (auto& job : jobs) {
        count += job->getOperationCount();
    }
    return count;
}

timestamp Shop::getTravelTime(identifier fromMachine, identifier toMachine) const {
    auto it = travelTimes.find(std::make_pair(fromMachine, toMachine));
    if (it != std::end(travelTimes)) {
        return it->second;
    }

    if (fromMachine == toMachine) {
        return defaultSameMachineTravel;
    }
    return defaultTravel;
}

std::istream& Shop::read(std::istream& is) {
    jobs.clear();

    identifier jobNumber;
    is >> jobNumber >> machines;
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (identifier j = 0; j < jobNumber; j++) {
        auto job = std::make_shared<Job>(j);
        is >> *job;
        jobs.push_back(job);
    }
    return is;
}

void Shop::read(specops::proto::SchedulerMessage* msg) {
    jobs.clear();

    timestamp current = msg->current_timestamp();
    delay = msg->current_timestamp() + msg->execution_delay();
    identifier jobNumber = msg->jobs_size();
    machines = msg->machines_size();

    jobMakespan = std::vector<timestamp>(jobNumber, -1);
    jobMachines = std::vector<identifier>(jobNumber, -1);
    machineMakespan = std::vector<timestamp>(machines, 0);
    machineParts = std::vector<partid>(machines, nullptr);
    machineOperations = std::vector<identifier>(machines, -1);
    machineRemainingLife = std::vector<timerange >(machines, LLONG_MIN);

    for (identifier m = 0; m < machines; ++m) {

	    auto* machine_proto = msg->mutable_machines(m);
        mm.insert({machine_proto->id(), m});

	    if(machine_proto->remaining_life() != 0) {
				machineRemainingLife[m] = machine_proto->remaining_life();

	    }

        identifier maintenance_size = machine_proto->maintenance_schedules_size();
        for (int s = 0; s < maintenance_size; ++s) {
            auto* maintenance_schedule_proto = machine_proto->mutable_maintenance_schedules(s);
            timestamp maintenance_start = maintenance_schedule_proto->start();
            timestamp maintenance_end = maintenance_start + maintenance_schedule_proto->duration();
            addFixedJob(m, maintenance_start, maintenance_end);
        }
    }

    for (identifier j = 0; j < jobNumber; ++j) {
        auto* job_proto = msg->mutable_jobs(j);
        auto job = std::make_shared<Job>(j);
        job->read(this, msg, job_proto);
        jobs.push_back(job);
    }

    for(auto& mk : jobMakespan) {
        if (mk < 0) {
            mk = delay;
        }
        else if (mk < current) {
            mk = current;
        }
    }

    //travel times
    identifier travel_size = msg->travel_times_size();
    for (identifier t = 0; t < travel_size; ++t) {
        auto* travel_proto = msg->mutable_travel_times(t);

        machines_map::iterator from = mm.find(travel_proto->from_machine());
        machines_map::iterator to = mm.find(travel_proto->to_machine());
        if (from != std::end(mm) && to != std::end(mm)) {
            addTravelTime(from->second, to->second, travel_proto->duration());
        }
    }

    //tool library
    identifier tool_size = msg->tools_size();
    for (identifier t = 0; t < tool_size; ++t) {
        auto* tool_proto = msg->mutable_tools(t);
        toolLibrary.addToolType(tool_proto->type(), tool_proto->quantity());
    }
}

void Shop::allocatedOperation(Job* job,
                              identifier operationId,
                              std::string machine_id,
                              timestamp,
                              timestamp end) {
    identifier job_id = job->getId();
    jobMakespan[job_id] = std::max(jobMakespan[job_id],
                                   end);
    machines_map::iterator m = mm.find(machine_id);
    if (m != std::end(mm)) {
        identifier machine = m->second;
        jobMachines[job_id] = machine;

        if (end >= machineMakespan[machine]) {
            machineMakespan[machine] = end;
            machineOperations[machine] = operationId;
            machineParts[machine] = job->getPartId();
        }
    }
}

}

namespace std {

istream& operator >> (istream& in, specops::Shop& shop) {
    return shop.read(in);
}

}
