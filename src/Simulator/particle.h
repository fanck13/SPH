#pragma once

#include <list>
#include "../Utils/math.h"
#include "../Utils/vec.h"

namespace fck
{
    struct particle
    {
        size_t id;
        vec3f position;
        vec3f velocity;
        vec3f acceleration;
        vec3f force;
        std::list<size_t> neighbours;
    };
}

