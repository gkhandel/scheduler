/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

#pragma once

#include <istream>
#include <memory>

#include <scheduler/utils/types.hpp>

namespace specops {

class Entity {
    public:
        using ptr = std::shared_ptr<Entity>;
        Entity(identifier);
        ~Entity() = default;
        inline identifier getId() const noexcept { return id; }
        virtual std::istream& read (std::istream&) = 0;
    private:
        identifier id;
};

}

namespace std {

istream& operator >> (istream&, specops::Entity&);

}
