#include <time.h>
#include <stdlib.h>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_vector2D.hpp"
#include "line.hpp"
#include "constants.hpp"
#include "raycaster.hpp"

#ifndef _MANAGER_
#define _MANAGER_

class GameManager
{
private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    std::vector<Line> mObjects;
    int init();
    void gameLoop();
    void initObjects();
public:
    GameManager();
    ~GameManager();
};

GameManager::GameManager()
{
    srand(time(0));
    if(init() == 0) gameLoop();
}

GameManager::~GameManager(){}

int GameManager::init(){
    if(SDL_Init(SDL_INIT_VIDEO) != 0) return 1;
    
    mWindow = SDL_CreateWindow("Raycasting", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, constants::WIDTH, constants::HEIGHT, 0);
    if(!mWindow) {
        SDL_Quit();
        return 1;
    }
    
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    mRenderer = SDL_CreateRenderer(mWindow, -1, render_flags);
    if(!mRenderer) {
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
        return 1;
    }
    
    return 0;
}

void GameManager::gameLoop(){
    bool running = true;

    Raycaster caster(4, 4);
    initObjects();

    SDL_Event event;
    while(running){
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT) running = false;
        }
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
        SDL_RenderClear(mRenderer);        
        SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 0);
        
        int x;
        int y;

        SDL_GetMouseState(&x, &y);
        Vector2D position(x - 2, y - 2);

        caster.Draw(mRenderer, position);
        
        for (auto &&obj : mObjects){
            obj.Draw(mRenderer);
        }

        SDL_SetRenderDrawColor(mRenderer, 78, 222, 167, 0);
        caster.UpdateRays(mRenderer, Vector2D(x, y), mObjects);

        SDL_RenderPresent(mRenderer);
        SDL_Delay(1000/constants::FPS);
    }

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void GameManager::initObjects(){
    for (int i = 0; i < constants::OBJECT_COUNT; i++){
        int x1 = rand() % constants::WIDTH;
        int y1 = rand() % constants::HEIGHT;

        int len = (rand() % 50) + 350;

        Vector2D dir(((float)rand()/(float)(RAND_MAX)) * 2 - 1, ((float)rand()/(float)(RAND_MAX)) * 2 - 1);

        while (x1 + dir.X * len > constants::WIDTH || x1 + dir.X * len < 0 || y1 + dir.Y * len > constants::HEIGHT || y1 + dir.Y * len < 0){
            dir = {(float)rand()/(float)RAND_MAX * 2 - 1, (float)rand()/(float)RAND_MAX * 2 - 1};
        }
        
        mObjects.push_back(Line(Vector2D(x1, y1), Vector2D(x1 + (int) (dir.X * len), y1 + (int) (dir.Y * len))));
    }    
}

#endif