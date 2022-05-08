#include "SDL2/SDL_vector2D.hpp"

#ifndef _RAY_
#define _RAY_

class Ray{
    private:
        Vector2D mDirection;
        Vector2D mOrigin;
        Vector2D mEnd;
        Vector2D mIntersect;
        float mClosestIntersect;
    public:
        Ray();
        Ray(Vector2D dir);
        void Draw(SDL_Renderer* renderer);
        void Update(Vector2D origin, std::vector<Line> &lines);
        void findIntersects(std::vector<Line> &lines);
        void findIntersect(Line line);
};

Ray::Ray(){
    mDirection = Vector2D(0, 0);
}

Ray::Ray(Vector2D dir){
    mDirection = dir;
}

void Ray::Update(Vector2D origin, std::vector<Line> &lines){
    mOrigin = origin;
    mEnd = origin + mDirection * 1000;
    mIntersect = mEnd;
    findIntersects(lines);
}

void Ray::findIntersects(std::vector<Line> &lines){    
    mClosestIntersect = INFINITY;
    for (auto &&line : lines){
        findIntersect(line);
    }    
}

void Ray::Draw(SDL_Renderer* renderer){
    SDL_RenderDrawLine(renderer, mOrigin.X, mOrigin.Y, mIntersect.X, mIntersect.Y);
}

void Ray::findIntersect(Line line){
        int x1 = mOrigin.X;
        int y1 = mOrigin.Y;
        int x2 = mEnd.X;
        int y2 = mEnd.Y;
        int x3 = line.X1();
        int y3 = line.Y1();
        int x4 = line.X2();
        int y4 = line.Y2();

        float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
        if(denominator == 0) return;

        float t = ((x1 - x3) * (y3 - y4) - (y1 -y3) * (x3 - x4)) / denominator;
        float u = ((x1 - x3) * (y1 -y2) - (y1 - y3) * (x1 - x2)) / denominator;

        if(t > 0 && t < 1 && u > 0 && u < 1){            
            int x = (int) (x1 + t * (x2 - x1));
            int y = (int) (y1 + t * (y2 - y1));

            Vector2D point(x,y);
            float distance = Vector2D(point.X - mOrigin.X, point.Y - mOrigin.Y).length();
            if(distance < mClosestIntersect){
                mClosestIntersect = distance;
                mIntersect = point;
            }
        }
}

#endif