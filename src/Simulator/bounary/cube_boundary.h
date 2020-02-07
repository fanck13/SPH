#pragma once

#include "IBoundary.h"
#include "../Utils/vec.h"

namespace fck
{
    class cube_boundary:public IBoundary
    {
    public:
        cube_boundary(const vec3f& domain)
            :xmin(0.0f), xmax(domain.x()),
             ymin(0.0f), ymax(domain.y()),
             zmin(0.0f), zmax(domain.z())
        {}

        ~cube_boundary() {}

        bool is_in(const vec3f& position) override;

        bool is_out(const vec3f& position) override;

        bool is_near(const vec3f& position, float distance) override;

        float near_distance(const vec3f& position) override;

        void set_x(float min, float max)
        {
            xmin = min;
            xmax = max;
        }

        void set_y(float min, float max)
        {
            ymin = min;
            ymax = max;
        }

        void set_z(float min, float max)
        {
            zmin = min;
            zmax = max;
        }

        void get_position_after_collision(vec3f& position) override;

    private:
        float xmin;
        float xmax;
        float ymin;
        float ymax;
        float zmin;
        float zmax;
    };
}


