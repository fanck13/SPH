#pragma once
#include <type_traits>
#include <iterator>
#include <cassert>

#include "math.h"

namespace fck
{
    template<class T, size_t N>
    class vec
    {
    public:
        vec()
        {
            std::memset(data, static_cast<T>(0), sizeof(T)*N);
        }

        vec(const std::initializer_list<T>& list)
        {
            static_assert(std::is_arithmetic<T>::value && !std::is_void<T>::value, "test");

            std::memset(data, static_cast<T>(0), sizeof(T)*N);

            auto init_list_length = list.size();
            auto actual_length = std::min(init_list_length, N);
            auto list_begin = list.begin();
            std::copy(list_begin, list.begin() + actual_length, std::begin(data));
        }

        ~vec()
        { }

        friend vec operator+(const vec& lhs, const vec& rhs)
        {
            vec<T, N> a;

            for (size_t i = 0; i < N; i++)
            {
                a[i] = lhs[i] + rhs[i];
            }
            return a;
        }

        friend vec operator*(const vec& lhs, float rhs)
        {
            vec<T, N> a;

            for (size_t i = 0; i < N; i++)
            {
                a[i] = lhs[i]*rhs;
            }
            return a;
        }

        friend vec operator*(float lhs, const vec& rhs)
        {
            return operator*(rhs, lhs);
        }

        //what is the difference if friend and static 
        friend vec operator-(const vec& lhs, const vec& rhs)
        {
            vec<T, N> a;

            for (size_t i = 0; i < N; i++)
            {
                a[i] = lhs[i] - rhs[i];
            }

            return a;
        }


        T& x() { return this->operator[](0); }
        T x() const { return this->operator[](0); }

        T& y() { return this->operator[](1); }
        T y() const { return this->operator[](1); }

        T& z() { return this->operator[](2); }
        T z() const { return this->operator[](2); }

        T& w() { return this->operator[](3); }
        T w() const { return this->operator[](3); }


        T& operator[](size_t index)
        {
#ifdef _DEBUG
            assert(index < N);
#endif // DEBUG
            return data[index];
        }

        T operator[](size_t index) const
        {
            assert(index < N);
            return data[index];
        }

        float length()
        {
            //std::accu
            T sum = static_cast<T>(0);
            for (size_t i = 0; i < N; i++)
            {
                sum += math::square(data[i]);
            }
#if 0
            sum = std::accumulate(std::begin(data), std::end(data), static_cast<T>(0), [](const T init, const T elem) {return init + elem * elem; });
#endif // 0

            return std::sqrtf(static_cast<float>(sum));
        }

        void print()
        {
            std::ostream_iterator<T> out(std::cout, " ");
            std::copy(std::begin(data), std::end(data), out);
            std::cout << std::endl;
        }

    private:
        T data[N];
    };

    using vec3f = vec<float, 3>;
    using vec3ui = vec<unsigned int, 3>;
    using vec3i = vec<signed int, 3>;
}
