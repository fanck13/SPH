#include "mesh.h"

namespace fck
{
    void mesh::add(const size_t id, const vec3f& pos)
    {
        auto index = get_mesh_index_by_pos(pos);
        _grid[index].push_back(id);
    }

    size_t mesh::get_mesh_index_by_pos(const vec3f& pos)
    {
        auto x = pos.x() / lengths.x();
        auto y = pos.y() / lengths.y();
        auto z = pos.z() / lengths.z();

        return (dim3.z()*dim3.y())*x + dim3.x() * y + z;
    }

    void mesh::print()
    {
        for (auto current = _grid.cbegin(); current != _grid.cend(); current++)
        {
            std::cout << current->first << ": ";

            for (auto id : current->second)
            {
                std::cout << id << " ";
            }
            std::cout << std::endl;
        }
    }
}
