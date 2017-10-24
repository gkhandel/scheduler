#include <scheduler/entities/entity.hpp>

namespace specops {

Entity::Entity(identifier id):
        id{id} {
}

}

namespace std {

istream& operator >> (istream& is, specops::Entity& entity) {
    return entity.read(is);
}

}
