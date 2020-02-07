#include "cube_boundary.h"

namespace fck
{
    void cube_boundary::get_position_after_collision(vec3f& position)
    {

        if (position.x() < xmin)
        {
            position.x() = xmin - position.x();
        }

        if (position.x() > xmax)
        {
            position.x() = position.x() - xmax;
        }

        if (position.y() < ymin)
        {
            position.y() = ymin - position.y();
        }

        if (position.y() > ymax)
        {
            position.y() = position.y() - ymax;
        }

        if (position.z() < zmin)
        {
            position.z() = zmin - position.z();
        }

        if (position.z() > zmax)
        {
            position.z() = position.z() - zmax;
        }
    }

    bool cube_boundary::is_in(const vec3f& position)
    {
        const auto x = position.x(), y = position.y(), z = position.z();
        return (x > xmin && x < xmax) && (y > ymin && y < ymax) && (z > zmin && z < zmax);
    }

    bool cube_boundary::is_out(const vec3f& position)
    {
        return !is_in(position);
    }

    bool cube_boundary::is_near(const vec3f& position, float distance)
    {
        return near_distance(position) < distance;
    }

    float cube_boundary::near_distance(const vec3f& position)
    {
        if (is_out(position)) return false;
        const auto x = position.x(), y = position.y(), z = position.z();

        auto x_offset = std::min(x - xmin, xmax - x);
        auto y_offset = std::min(y - ymin, ymax - y);
        auto z_offset = std::min(z - zmin, zmax - z);

        return std::min(x_offset, std::min(y_offset, z_offset));
    }
}
