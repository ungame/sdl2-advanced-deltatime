#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SDL2/SDL.h>

class Object
{
    private:
        int _width;
        int _height;

    public:
        SDL_Color Color;
        SDL_FPoint Position;
        SDL_FPoint Direction;
        float Speed;

    public:
        Object(int w, int h, float x, float y);
        void Update();
        void Draw(SDL_Renderer* renderer);
};

#endif
