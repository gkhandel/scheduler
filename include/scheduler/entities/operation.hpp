#pragma once

#include <istream>
#include <memory>
#include <string>
#include <vector>

#include <scheduler/entities/alternative.hpp>
#include <scheduler/entities/entity.hpp>
#include <scheduler/utils/types.hpp>

#include "message.pb.h"

namespace specops {

class Job;
class Shop;

class Operation : public Entity {
    public:
        using ptr = std::shared_ptr<Operation>;
        using proto = specops::proto::ProcessStep*;
        Operation(Job* job, identifier);
        ~Operation() = default;
        inline Alternative* getAlternative(identifier alternative) noexcept {
            return alternatives[alternative].get();
        }
        inline identifier getAlternativeCount() const noexcept { return alternatives.size(); }
        inline Job* getJob() noexcept { return job; }
        Alternative* getMaxDurationAlternative();
        std::istream& read (std::istream&) override;

        void read(Shop* shop,
                  specops::proto::SchedulerMessage* msg,
                  proto process_step_proto);
        proto getProto() { return process_step_proto; }
        bool isBlocked() { return blocked; }
        const std::vector<std::string>* getTools() { return &tools; }
        bool inScheduleWindow() { return in_schedule_window || blocked; }
    private:
        Job* job;
        std::vector<Alternative::ptr> alternatives;
        proto process_step_proto;
        bool blocked;
        std::vector<std::string> tools;
        bool in_schedule_window = false;
};

}
