#include <SDL2/SDL.h>
#include "Object.hpp"

Object::Object(int w, int h, float x, float y)
{
    _width = w;
    _height = h;

    Color = { 189, 189, 189, SDL_ALPHA_TRANSPARENT };
    Position = { x, y };
    Direction = { 0, 0 };
    Speed = 1;
}

void Object::Update()
{

}

void Object::Draw(SDL_Renderer* renderer)
{
    int x = Position.x;
    int y = Position.y;
    SDL_Rect rect = { x, y, _width, _height };

    SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, Color.a);
    SDL_RenderFillRect(renderer, &rect);
}
