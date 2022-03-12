#include <SDL2/SDL.h>
#include "Timer.hpp"

Timer::Timer(float fps)
{
    _fps = fps;
    _previousTime = SDL_GetTicks();
    _frameTime = 0;
}

void Timer::Tick()
{
    _frameTime = SDL_GetTicks() - _previousTime;
    _previousTime = SDL_GetTicks();
}

float Timer::DeltaTime()
{
    float deltaTime = _frameTime * (_fps / 1000);

    if(deltaTime > DEFAULT_DELTATIME)
        return DEFAULT_DELTATIME;

    return deltaTime;
}
