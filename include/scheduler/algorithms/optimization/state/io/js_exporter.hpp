#pragma once

#include <ostream>

#include <scheduler/algorithms/optimization/state/state_observer.hpp>
#include <scheduler/utils/types.hpp>

namespace specops {

class JSExporter : public StateObserver {
    public:
        JSExporter(std::ostream&);
        ~JSExporter() = default;
        void start(State*) override;
        void update(identifier, Alternative*, timestamp, bool) override;
        void end() override;
    private:
        std::ostream* out;
        identifier machines;
};

}
