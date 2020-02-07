#pragma once

#include "../Utils/vec.h"

namespace fck
{
    struct IBoundary
    {
        virtual bool is_in(const vec3f& position) = 0;

        virtual bool is_out(const vec3f& position) = 0;

        virtual bool is_near(const vec3f& position, float distance) = 0;

        virtual float near_distance(const vec3f& position) = 0;

        virtual void get_position_after_collision(vec3f& position) = 0;
    };

}
