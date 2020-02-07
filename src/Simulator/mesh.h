#pragma once

#include <map>
#include <list>
#include <iostream>

#include "../Utils/math.h"
#include "../Utils/vec.h"

namespace fck
{
    class mesh
    {
        using cell_index = size_t;
        using cell_elements = std::list<size_t>;
        using grid = std::map<cell_index, cell_elements>;
    public:
        mesh()
        { }

        mesh(const vec3i& _dim3, const vec3f& _lengths):dim3(_dim3), lengths(_lengths)
        { }

        ~mesh()
        { }

        void add(const size_t id, const vec3f& pos);

        

        size_t get_mesh_index_by_pos(const vec3f& pos);

        const cell_elements& get_cell_elements(cell_index index) //why not const
        {
            return _grid[index];
        }

        const grid& get() const
        {
            return _grid;
        }

        void print();

        void set_dim3(const vec3i& _dim3)
        {
            dim3 = _dim3;
        }

        void set_lengths(const vec3f& _lengths)
        {
            lengths = _lengths;
        }

        void clear()
        {
            _grid.clear();
        }

    private:
        grid _grid;
        vec3i dim3;
        vec3f lengths;
    };
}


