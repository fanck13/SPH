#pragma once

#include "particle.h"
namespace fck
{
    struct ISolver
    {
        virtual void calc_position(particle* particles, size_t count) = 0;
        virtual void calc_acceleration(particle* particles, size_t count) = 0;
        virtual void calc_velocity(particle* particles, size_t count) = 0;
        virtual void clac_force(particle* particles, size_t count) = 0;
    };
}
