/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#pragma once

#include <istream>
#include <memory>

#include <scheduler/entities/entity.hpp>
#include <scheduler/utils/types.hpp>

#include "message.pb.h"

namespace specops {

class Operation;

class Alternative : public Entity {
    public:
        using ptr = std::shared_ptr<Alternative>;
        using mproto = specops::proto::Machine*;
        Alternative(Operation*, identifier);
        inline timerange getDuration() const noexcept { return duration; }
        inline timerange getDuration(bool skip_setup) const noexcept {
            return duration + (skip_setup ? 0 : setup);
        }
        inline identifier getJobId() const noexcept { return jobId; }
        inline identifier getMachine() const noexcept { return machine; }
        inline Operation* getOperation() noexcept { return operation; }
        inline identifier getOperationId() const noexcept { return operationId; }
        inline timerange getSetup() const noexcept { return setup; }
        std::istream& read (std::istream&) override;

        void read(specops::proto::SchedulerMessage* msg,
                  specops::proto::ProcessStep* process_step_proto,
                  identifier machine,
                  mproto machine_proto);
        mproto getMachineProto() { return machine_proto; }
    private:
        Operation* operation;
        identifier operationId, jobId;
        identifier machine;
        timerange duration, setup;
        mproto machine_proto;
};

}
