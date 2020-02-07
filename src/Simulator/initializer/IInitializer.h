#pragma once

namespace fck
{
    class IInitializer
    {
    public:
        virtual void initialize() = 0;
        virtual float* get_pos() const = 0;
    };
}
