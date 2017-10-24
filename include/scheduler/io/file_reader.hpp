/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#pragma once

#include <fstream>
#include <string>

#include <scheduler/entities/shop.hpp>

namespace specops {

class FileReader {
    public:
        FileReader(const std::string&);
        ~FileReader();
        Shop::unique_ptr read();
    private:
        std::ifstream ifs;
};

}
