/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#pragma once

#include <istream>
#include <memory>
#include <string>
#include <vector>

#include <scheduler/entities/alternative.hpp>
#include <scheduler/entities/entity.hpp>
#include <scheduler/entities/operation.hpp>
#include <scheduler/utils/types.hpp>

#include "message.pb.h"

namespace specops {

class Shop;

class Job : public Entity {
    public:
        using ptr = std::shared_ptr<Job>;
        Job(identifier);
        ~Job() = default;

        inline Alternative* getAlternative(identifier operation,
                                           identifier alternative) noexcept {
            return getOperation(operation)->getAlternative(alternative);
        }

        inline timestamp getDueDate() const noexcept { return due; }
        inline void setDueDate(timestamp dueDate) { due = dueDate; }

        inline partid getPartId() const noexcept { return part; }
        inline void setPartId(const std::string& p) {
            part = std::make_shared<std::string>(p);
        }

        inline Operation* getOperation(identifier operation) noexcept {
            return operations[operation].get();
        }

        inline identifier getOperationCount() const noexcept { return operations.size(); }
        std::istream& read (std::istream&) override;

        void read(Shop* shop,
                  specops::proto::SchedulerMessage* msg,
                  specops::proto::Job* job_proto);
    private:
        std::vector<Operation::ptr> operations;
        timestamp due;
        partid part;
};

}
