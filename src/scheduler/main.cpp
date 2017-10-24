/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <string>

#include <scheduler/algorithms/optimization/state/initial_state.hpp>
#include <scheduler/algorithms/optimization/state/state.hpp>
#include <scheduler/algorithms/optimization/tabu_search.hpp>
#include <scheduler/entities/shop.hpp>
#include <scheduler/io/file_reader.hpp>

#include <scheduler/algorithms/optimization/state/io/proto_mutator.hpp>

#include "message.pb.h"
#include <google/protobuf/util/json_util.h>
#include <scheduler/algorithms/optimization/state/io/js_exporter.hpp>


int main(int argc, char** argv) {

    if (argc < 3) {
        std::cout << "Usage: scheduler <input-file> <output-file>" << std::endl;
        return -1;
    }

    std::string filename = argv[1];
    std::string out_filename = argv[2];

    std::ifstream ifs(filename);
    std::stringstream buffer;
    buffer << ifs.rdbuf();

    specops::proto::SchedulerMessage scheduler_message;

    google::protobuf::util::Status status =
        google::protobuf::util::JsonStringToMessage(buffer.str(), &scheduler_message);

    if (status.ok()) {
        specops::Shop::unique_ptr shop = std::make_unique<specops::Shop>();
        shop->read(&scheduler_message);

        specops::State::ptr s = std::make_shared<specops::InitialState>(shop.get());
        std::cout << "Initial state: \n" << *(s) << std::endl;

        specops::TabuSearch tabu;
        specops::State::ptr ss = tabu.search(s);
        std::cout << "Solution state: \n" << *ss << std::endl;

        specops::ProtoMutator pm;
        ss->notify(&pm);

        std::ofstream outjs("state.js");
        specops::JSExporter exporter(outjs);
        ss->notify(&exporter);

        google::protobuf::util::JsonPrintOptions json_options;
        json_options.add_whitespace = true;
        json_options.always_print_primitive_fields = true;

        std::ofstream out(out_filename);
        std::string output;
        google::protobuf::util::MessageToJsonString(scheduler_message, &output, json_options);
        out << output;
        out.close();
    } else {
        std::cout << "Could not parse input file: " << status << std::endl;
    }

    return 0;
}
