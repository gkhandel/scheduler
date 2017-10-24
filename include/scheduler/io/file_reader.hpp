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
