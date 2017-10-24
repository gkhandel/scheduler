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
