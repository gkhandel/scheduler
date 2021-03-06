/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#include <scheduler/io/file_reader.hpp>

namespace specops {

FileReader::FileReader(const std::string& filename):
        ifs{filename, std::ifstream::in} {
}

FileReader::~FileReader() {
    ifs.close();
}

Shop::unique_ptr FileReader::read() {
    Shop::unique_ptr shop = nullptr;
    if (ifs.good()) {
        shop = std::make_unique<Shop>();
        ifs >> *shop;
    }
    return shop;
}

}
