#pragma once

#include <memory>
#include <random>

#include "IInitializer.h"

namespace fck 
{
    class uniform_initializer : public IInitializer
    {
    public:
        uniform_initializer(size_t _count):count(_count)
        {
            position = new float[count * 3];
            assert(position != nullptr);
        }

        ~uniform_initializer()
        {
            delete[] position;
        }

        void initialize() override
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0.0f, 100.0);
            
            for (int i = 0; i < count; i++)
            {
                position[i * 3] = dis(gen);
                position[i * 3 + 1] = dis(gen);
                position[i * 3 + 2] = dis(gen);
            }
        }

        float* get_pos() const override
        {
            return position;
        }

        size_t get_count() const
        {
            return count;
        }

    private:
        size_t count;
        float* position;
    };
}
