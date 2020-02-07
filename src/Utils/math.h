#pragma once
#include <initializer_list>
#include <cassert>
#include <type_traits>
#include <iterator>
#include <algorithm>
#include <numeric>

namespace fck
{
    class math
    {
    public:

        template<class T>
        static constexpr T PI = T(3.1415926535897932385L);


        inline static float square(float x)
        {
            return x * x;
        }

        inline static float cube(float x)
        {
            return square(x)*x;
        }

        inline static float pow6(float x)
        {
            return square(cube(x));
        }

        inline static float pow9(float x)
        {
            return cube(cube(x));
        }
    };
}

