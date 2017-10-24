/*
 *  Copyright (c) 2017, Palo Alto Research Center (PARC)
 *  All rights reserved.
 *  The software herein is provided with Government Purpose Rights.
 */

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
