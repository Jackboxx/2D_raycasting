#include "SDL2/SDL.h"
#include "ray.hpp"
#include "SDL2/SDL_vector2D.hpp"

#ifndef _CASTER_
#define _CASTER_

class Raycaster{
    private:
        SDL_Rect mRect;
        Ray mRays[constants::RAY_COUNT];
    public:
        Raycaster(int width, int height);
        void Draw(SDL_Renderer* renderer, Vector2D position);
        void UpdateRays(SDL_Renderer* renderer, Vector2D origin, std::vector<Line> &lines);
};

Raycaster::Raycaster(int width, int height){
    mRect = {0, 0, width, height};

    for (int i = 0; i < constants::RAY_COUNT; i++){
        float angle = (2 * i * constants::PI )/ constants::RAY_COUNT + constants::PI/4;

        float x = cos(angle);
        float y = sin(angle);

        mRays[i] = Ray(Vector2D(x, y));
    }   
}

void Raycaster::Draw(SDL_Renderer* renderer, Vector2D position){
    mRect.x = position.X;
    mRect.y = position.Y;
    SDL_RenderFillRect(renderer, &mRect);
}
void Raycaster::UpdateRays(SDL_Renderer* renderer, Vector2D origin, std::vector<Line> &lines){
    for (int i = 0; i < constants::RAY_COUNT; i++){
        mRays[i].Update(origin, lines);
        mRays[i].Draw(renderer);
    }
}

#endif