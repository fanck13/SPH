#pragma once

#include <chrono>
#include <fstream>
#include <iostream>

/*
template <typename T, typename = void>
struct is_iterable : std::false_type {};
template <typename T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin()),
    decltype(std::declval<T>().end())>>
*/

namespace fck
{
    class IPrinter
    {
    public:
        virtual void print(long long elapse) = 0;
    };

    class ConsolePrinter : public IPrinter
    {
    public:
        void print(long long elapse) override
        {
            std::cout << elapse << std::endl;
        }
    };


    template<class clock = std::chrono::high_resolution_clock,
    class accuracy = std::chrono::microseconds,
    class output = IPrinter>

    class stop_watch
    {
        using time_point = std::chrono::time_point<clock>;
    public:
        stop_watch() 
        {
            start = clock::now();
        }

        ~stop_watch()
        {
            end = clock::now();
            elapse = std::chrono::duration_cast<accuracy>(end - start);
            std::cout << elapse.count() << std::endl;
            printer.print(elapse.count());
        }

    private:
        time_point start;
        time_point end;
        accuracy elapse;
        output printer;
    };
}
