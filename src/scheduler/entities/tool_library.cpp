#include <scheduler/entities/tool_library.hpp>

namespace specops {

void ToolLibrary::addToolType(std::string type, count quantity) {
    tool_timestamps[type] = std::vector<timestamp>(quantity, 0);
}

timestamp ToolLibrary::getMinMakespan(const std::vector<std::string>* tools) {
    std::vector<std::string>::const_iterator it = tools->begin();

    timestamp t = timestamp_min;

    for (; it != tools->end(); ++it) {
        tool_map::iterator current_type = tool_timestamps.find(*it);

        if (current_type != tool_timestamps.end()) {
            auto& type_ts = current_type->second;

            identifier size = type_ts.size();
            if (size > 0) {
                timestamp current = type_ts[0];
                for (identifier i = 1; i < size; ++i) {
                    current = std::min(current, type_ts[i]);
                }
                t = std::max(t, current);
            }
        }
    }

    return t;
}

void ToolLibrary::updateMakespan(const std::vector<std::string>* tools, timestamp makespan) {
    std::vector<std::string>::const_iterator it = tools->begin();

    for (; it != tools->end(); ++it) {
        tool_map::iterator current_type = tool_timestamps.find(*it);
        if (current_type != tool_timestamps.end()) {
            auto& type_ts = current_type->second;

            identifier size = type_ts.size();
            if (size > 0) {
                identifier index = 0;

                for (identifier i = 1; i < size; ++i) {
                    if (type_ts[index] >= type_ts[i]) {
                        index = i;
                    }
                }

                type_ts[index] = makespan;
            }
        }
    }
}

}
