//#include <stdio.h>
#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include "Input.hpp"
#include "Object.hpp"
#include "Time.hpp"
#include "Timer.hpp"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 720
#define WINDOW_TITLE "SDL2 ADVANCED DELTATIME"

bool isNan(std::string str)
{
    int chars = str.length();

    for(int i = 0; i < chars; i++)
    {
        char c = str[i];

        if(std::isdigit(c) == 0)
            return true;
    }

    return false;
}

int main(int argc, char* argv[])
{
    float speed = 8; // object speed
    float fps = 60; // frame rate per second
    int fpsStrategy = 0; // 0 == delay, arg != 0 == deltaTime
                        
    if(argc > 1 && !isNan(std::string(argv[1])))
    {
        speed = std::stof(argv[1]);
        
        SDL_Log("Speed=%f", speed);
    }

    if(argc > 2 && !isNan(std::string(argv[2])))
    {
        fps = std::stof(argv[2]);

        SDL_Log("FPS=%f", fps);
    }

    if(argc > 3 && !isNan(std::string(argv[3])))
    {   
        fpsStrategy = std::stoi(argv[3]);

        SDL_Log("FPS_STRATEGY=%s", fpsStrategy == 1 ? "DeltaTime" : "Delay");
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {    
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to init: %s", SDL_GetError());

        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to create window: %s", SDL_GetError());

        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "sdl unable to create renderer: %s", SDL_GetError());

        return EXIT_FAILURE;
    }
    
    std::string title = "";

    Object* object = new Object(64, 64, 0, SCREEN_HEIGHT / 2 - 64);
    object->Direction.x = 1;
    object->Speed = speed;

    Time* time = new Time();
    Timer* timer = new Timer(fps);

    int iterations = 0;

    bool running = true;

    while(running)
    {
        timer->Tick();

        running = Input::Instance()->Listen();

        if(Input::Instance()->KeyPressed(SDL_SCANCODE_ESCAPE))
            running = false;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
        SDL_RenderClear(renderer);

        float horizontalMovement = object->Direction.x * object->Speed; 
        
        if(fpsStrategy == 0)
            object->Position.x += horizontalMovement;
        else
            object->Position.x += horizontalMovement * timer->DeltaTime();

        if(object->Position.x > SCREEN_WIDTH)
            running = false;
        
        title = WINDOW_TITLE;
        title += " | ";
        title += "DeltaTime=" + std::to_string(timer->DeltaTime());
        title += " | ";
        title += "Seconds=" + std::to_string(Time::Since(time));

        SDL_SetWindowTitle(window, title.c_str());

        object->Draw(renderer);

        SDL_RenderPresent(renderer);

        SDL_Log("Second=%lf, Position-X=%f, Iterations=%d", Time::Since(time), object->Position.x, iterations);

        if(fpsStrategy == 0)
            SDL_Delay(1000/fps);

        iterations++;
    }

    SDL_Log("Second=%lf, Position-X=%f, Iterations=%d", Time::Since(time), object->Position.x, iterations);
    SDL_Log("Quit: %lfs", Time::Since(time));
    
    delete object;
    delete time;
    delete timer;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
