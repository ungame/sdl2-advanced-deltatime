#include <chrono>
#include "Time.hpp"

double Time::Since(Time* t)
{
    std::chrono::duration<double> elapsed = Now() - t->Clock();

    return elapsed.count();
}
