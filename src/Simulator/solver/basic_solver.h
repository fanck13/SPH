#pragma once

#include <iostream>

#include "ISolver.h"
#include "particle.h"
#include "parameter.h"

namespace fck
{
    class basic_solver :public ISolver
    {
    public:
        basic_solver()
        {
            para = parameter::get_para();
        }
        void calc_position(particle* particles, size_t count) override;

        void calc_acceleration(particle* particles, size_t count) override;

        vec3f calc(const vec3f& lhs, const vec3f& rhs);

        void calc_velocity(particle* particles, size_t count) override;

        void clac_force(particle* particles, size_t count) override;

    private:
        parameter *para;
    };
}
