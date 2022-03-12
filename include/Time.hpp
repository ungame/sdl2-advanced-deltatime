#ifndef TIME_HPP
#define TIME_HPP

#include <chrono>

class Time
{
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> _clock;

    public:
        Time() { _clock = Now(); }
        inline std::chrono::time_point<std::chrono::high_resolution_clock> Clock() { return _clock; }

    public:
        inline static std::chrono::time_point<std::chrono::high_resolution_clock> Now() { return std::chrono::high_resolution_clock::now(); }

    public:
        static double Since(Time* t);
};

#endif
