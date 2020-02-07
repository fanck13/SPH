#include "basic_solver.h"

namespace fck
{
    void basic_solver::calc_position(particle* particles, size_t count)
    {
        for (size_t i = 0; i < count; i++)
        {
            particles[i].position = particles[i].position
                + particles[i].velocity * para->delta_time                         //v*t
                + 0.5f*particles[i].acceleration*math::square(para->delta_time);   //1/2*a*t*t
        }
    }

    void basic_solver::calc_acceleration(particle* particles, size_t count)
    {
        for (size_t i = 0; i < count; i++)
        {
            particles[i].acceleration = particles[i].acceleration
                + particles[i].force * para->mass;
        }
    }

    vec3f basic_solver::calc(const vec3f& lhs, const vec3f& rhs)
    {
        return vec3f{ 0.0f, 0.0f, 0.0f };
    }

    void basic_solver::calc_velocity(particle* particles, size_t count)
    {
        for (size_t i = 0; i < count; i++)
        {
            particles[i].velocity = particles[i].velocity + particles[i].acceleration * para->delta_time;
        }
    }

    void basic_solver::clac_force(particle* particles, size_t count)
    {
        for (size_t i = 0; i < count; i++)
        {
            const auto& neighbours = particles[i].neighbours;
            for (auto start = neighbours.begin(); start != neighbours.end(); start++)
            {
                size_t neighbour_id = *start;
                particles[i].force = calc(particles[i].position, particles[neighbour_id].position) + para->external_force;
            }
        }
    }
}