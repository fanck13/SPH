#pragma once

#include <memory>

namespace fck
{
    class parameter
    {
    public:
        float neighbour_distance_threshold = 1.0f;
        float delta_time = 0.5f;
        float mass = 1.0f;
        vec3f external_force = {0.0f, -9.8f, 0.0f};

        static parameter* get_para()
        {
            if (para.get() == nullptr)
            {
                para = std::unique_ptr<parameter>(new parameter);
            }
            return para.get();
        }

    private:
        parameter()
        {}

        static std::unique_ptr<parameter> para;

    };
}

