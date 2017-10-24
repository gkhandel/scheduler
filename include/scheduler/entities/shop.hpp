#pragma once

#include <istream>
#include <list>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

#include <scheduler/entities/alternative.hpp>
#include <scheduler/entities/job.hpp>
#include <scheduler/entities/operation.hpp>
#include <scheduler/entities/tool_library.hpp>
#include <scheduler/utils/types.hpp>

#include "message.pb.h"

namespace specops {

struct FixedJob {
    identifier machine;
    timestamp start, end;

    bool operator<(const FixedJob& other) const {
        return start < other.start;
    }
};

class Shop {
    public:
        using unique_ptr = std::unique_ptr<Shop>;
        using location_key = std::pair<identifier, identifier>;
        using machines_map = std::unordered_map<std::string, identifier>;
        Shop() = default;
        ~Shop() = default;
        void addFixedJob(identifier machine, timestamp start, timestamp end);
        void addTravelTime(identifier fromMachine, identifier toMachine, timestamp travelTime);
        timestamp delayStart(timestamp makespan, const Alternative* alternative, bool skip_setup) const;
        inline Alternative* getAlternative(identifier job,
                                           identifier operation,
                                           identifier alternative) noexcept {
            return getJob(job)->getAlternative(operation, alternative);
        }
        inline Job* getJob(identifier job) noexcept { return jobs[job].get(); }
        inline identifier getJobCount() const noexcept { return jobs.size(); }
        inline const std::list<FixedJob>* getFixedJobs() const noexcept {
            return &fixedJobs;
        }
        inline identifier getMachineCount() const noexcept { return machines; }
        inline Operation* getOperation(identifier job,
                                       identifier operation) noexcept {
            return getJob(job)->getOperation(operation);
        }
        identifier getOperationCount() const;
        timerange getTravelTime(identifier fromMachine, identifier toMachine) const;
        std::istream& read (std::istream&);

        void read(specops::proto::SchedulerMessage* msg);

        std::vector<timestamp> getJobMakespan() { return jobMakespan; }
        std::vector<identifier> getJobMachines() { return jobMachines; }
        std::vector<timestamp> getMachineMakespan() { return machineMakespan; }
        std::vector<partid> getMachineParts() { return machineParts; }
        std::vector<identifier> getMachineOperations() { return machineOperations; }
        std::vector<timerange> getMachineRemainingLife() { return machineRemainingLife; }
        ToolLibrary getToolLibrary() { return toolLibrary; }

        timestamp getMinTimeToSchedule() { return delay; }
        void allocatedOperation(Job* job,
                                identifier operationId,
                                std::string machine,
                                timestamp start,
                                timestamp end);
    private:
        std::vector<Job::ptr> jobs;
        identifier machines;
        std::map<location_key, timerange> travelTimes;
        std::list<FixedJob> fixedJobs;

        timerange defaultTravel = 0.0;
        timerange defaultSameMachineTravel = 0.0;

        timestamp delay = 0;

        std::vector<timestamp> jobMakespan;
        std::vector<identifier> jobMachines;
        std::vector<timestamp> machineMakespan;
        std::vector<partid> machineParts;
        std::vector<identifier> machineOperations;

        machines_map mm;
        std::vector<timerange> machineRemainingLife;
        ToolLibrary toolLibrary;
};

}

namespace std {

istream& operator >> (istream&, specops::Shop&);

}
