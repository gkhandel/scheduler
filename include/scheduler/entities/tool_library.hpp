/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#pragma once

#include <istream>
#include <list>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

#include <scheduler/utils/types.hpp>

namespace specops {

class ToolLibrary {
    public:
        using tool_map = std::unordered_map< std::string, std::vector<timestamp> >;
        ToolLibrary() = default;
        ~ToolLibrary() = default;
        ToolLibrary(const ToolLibrary&) = default;
        void addToolType(std::string type, count quantity);
        timestamp getMinMakespan(const std::vector<std::string>* tools);
        void updateMakespan(const std::vector<std::string>* tools, timestamp makespan);
    private:
        tool_map tool_timestamps;
};

}
