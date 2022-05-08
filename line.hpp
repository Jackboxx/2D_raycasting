#include <iostream>
#include "SDL2/SDL_vector2D.hpp"

#ifndef _LINE_
#define _LINE_

class Line{
    private:
        Vector2D mStart;
        Vector2D mEnd;
    public:
        int X1() {return mStart.X;}
        int Y1() {return mStart.Y;}
        int X2() {return mEnd.X;}
        int Y2() {return mEnd.Y;}
        Line(Vector2D start, Vector2D end);
        void Draw(SDL_Renderer* renderer);
};

Line::Line(Vector2D start, Vector2D end){
    mStart = start;
    mEnd = end;
}

void Line::Draw(SDL_Renderer* renderer){
    SDL_RenderDrawLine(renderer, mStart.X, mStart.Y, mEnd.X, mEnd.Y);
}

#endif