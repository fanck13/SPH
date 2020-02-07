#pragma once

#include <array>
#include <thread>
#include <cmath>
#include <valarray>
#include <algorithm>

#include "particle.h"
#include "./initializer/uniform_initializer.h"
#include "./bounary/cube_boundary.h"
#include "./solver/basic_solver.h"
#include "mesh.h"
#include "parameter.h"
#include "../Utils/vec.h"


namespace fck
{
    vec3f simulated_domain = { 100.0f, 100.0f, 100.0f };

    class simulator
    {
    public:

        //constructor/destructor
        simulator() :initializer(nullptr),
            boundary(nullptr),
            solver(nullptr),
            para(nullptr),
            is_initialized(false)
        {
        }

        ~simulator()
        {
            delete initializer;
            delete boundary;
            delete solver;
        }

        //setter/getter
        void set_initializer(IInitializer* _initializer)
        {
            initializer = _initializer;
        }

        void set_boundary(IBoundary* _boundary)
        {
            boundary = _boundary;
        }

        void set_solver(ISolver* _solver)
        {
            solver = _solver;
        }

        const mesh& get_grid() const
        {
            return grid;
        }

        
        void initialize();

        void mt_init_particles_position();

        void init_particles_position();

        void fill_grid();

        void clear_particle_neighbours();

        void find_neighbours();

        void display_particle_position();

        void simulate();

        void check_boundary();

        void print_neighbours();

        /*
        void set_parameter(const parameter& _para)
        {
            para = _para;
        }
        */

    private:
        IInitializer* initializer;
        IBoundary* boundary;
        ISolver* solver;
        mesh grid;
        const static size_t _count = 200;
        std::array<particle, _count> particles;
        bool is_initialized;
        parameter *para;
    };
}



