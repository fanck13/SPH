#include "simulator.h"

namespace fck
{
    void simulator::initialize()
    {
        set_initializer(new fck::uniform_initializer(_count));
        set_boundary(new fck::cube_boundary(simulated_domain));
        set_solver(new fck::basic_solver());
        para = parameter::get_para();
        initializer->initialize();
        grid.set_dim3({ 10, 10, 10 });
        grid.set_lengths({ 10.0f, 10.0f, 10.0f });

#ifdef _MULTI_THREAD
        mt_init_particles_position();
#else
        init_particles_position();
#endif

        is_initialized = true;
    }

    void simulator::mt_init_particles_position()
    {
        auto positions = initializer->get_pos();

        auto thread_count = std::thread::hardware_concurrency();
        auto particle_count_per_thread = static_cast<size_t>(std::ceil(static_cast<float>(_count) / thread_count));

        for (int i = 0; i < thread_count; i++)
        {
            std::thread([&](size_t begin_index)
            {
                for (size_t i = 0; i < particle_count_per_thread; i++)
                {
                    particles[i].id = i;
                    particles[i].position.x() = positions[i * 3];
                    particles[i].position.y() = positions[i * 3 + 1];
                    particles[i].position.z() = positions[i * 3 + 2];
                }
            }, i*particle_count_per_thread).join();
        }
    }

    void simulator::init_particles_position()
    {
        auto positions = initializer->get_pos();

        for (size_t i = 0; i < _count; i++)
        {
            particles[i].id = i;
            particles[i].position.x() = positions[i * 3];
            particles[i].position.y() = positions[i * 3 + 1];
            particles[i].position.z() = positions[i * 3 + 2];
        }
    }

    void simulator::fill_grid()
    {
        grid.clear();
        /*
        for (size_t i = 0; i < _count; i++)
        {
            grid.add(particles[i].id, particles[i].position);
        }
        */
        auto& g = grid;
        std::for_each(std::begin(particles), std::end(particles), [this](particle& p) {grid.add(p.id, p.position); });
    }

    void simulator::clear_particle_neighbours()
    {
        std::for_each(std::begin(particles), std::end(particles), [](particle& p) { p.neighbours.clear(); });
    }

    void simulator::find_neighbours()
    {
        clear_particle_neighbours();
        for (size_t i = 0; i < _count; i++)
        {
            for (size_t j = 0; j < _count; j++)
            {
                if (i >= j) continue;
                auto delta = particles[i].position - particles[j].position;
                if (delta.length() < para->neighbour_distance_threshold)
                {
                    particles[i].neighbours.push_back(j);
                    particles[j].neighbours.push_back(i);
                }
            }
        }
    }

    void simulator::display_particle_position()
    {
        for (size_t i = 0; i < _count; i++)
        {
            std::cout << particles[i].id << "  "
                << particles[i].position.x() << "  "
                << particles[i].position.y() << "  "
                << particles[i].position.z()
                << std::endl;
        }
    }



    void simulator::simulate()
    {
        fill_grid();
        find_neighbours();

        solver->calc_acceleration(particles.data(), _count);
        solver->calc_velocity(particles.data(), _count);
        solver->calc_position(particles.data(), _count);

        check_boundary();
    }

    void simulator::check_boundary()
    {
        for (size_t i = 0; i < _count; i++)
        {
            boundary->get_position_after_collision(particles[i].position);
        }
    }

    void simulator::print_neighbours()
    {
        for (size_t i = 0; i < _count; i++)
        {
            std::cout << i << ":";
            const auto& neighbours = particles[i].neighbours;
            for (auto start = neighbours.begin(); start != neighbours.end(); start++)
            {
                std::cout << *start << "  ";
            }
            std::cout << std::endl;
        }
    }
}