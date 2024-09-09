#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "MatrixMul.hpp"

void Sprite_Draw(SDL_Renderer* Renderer, float& ang){
    float projMat[2][3] {
        {1,0,0},
        {0,1,0}
    };

    float rotMatX[3][3] {
        {1,0,0},
        {0, cosf(ang), -sinf(ang)},
        {0, sinf(ang), cosf(ang)}
    };

    float rotMatY[3][3] {
        {cosf(ang), 0, sinf(ang)},
        {0, 1, 0},
        {-sinf(ang), 0, cosf(ang)}
    };

    float rotMatZ[3][3] {
        {cosf(ang), -sinf(ang), 0},
        {sinf(ang), cosf(ang), 0},
        {0, 0, 1}
    };

    Point3d points[8] {
        {-0.5, -0.5, -0.5},
        {0.5, -0.5, -0.5},
        {0.5, 0.5, -0.5},
        {-0.5, 0.5, -0.5},
        {-0.5, -0.5, 0.5},
        {0.5, -0.5, 0.5},
        {0.5, 0.5, 0.5},
        {-0.5, 0.5, 0.5},
        
    };

    Point3d projected[8];
    unsigned int i = 0;

    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    for(auto& v : points){
        Point3d rot = matmul_st(rotMatY, std::size(rotMatZ), v);
        rot = matmul_st(rotMatX, std::size(rotMatX), rot);
        rot = matmul_st(rotMatZ, std::size(rotMatZ), rot);
        Point3d pj2d = matmul_st(projMat, std::size(projMat), rot);
        Scale_pt(&pj2d, 100);
        projected[i] = pj2d;
        //SDL_RenderDrawPointF(Renderer, 300 + pj2d.x, 240 + pj2d.y);
        ++i;
    }

    for(int i = 0; i < 4; ++i){
        Point_connect(Renderer, i, (i+1) % 4, projected);
        Point_connect(Renderer, (i+4), ((i+1) % 4) + 4, projected);
        Point_connect(Renderer, i, (i+4), projected);
    }

    SDL_RenderPresent(Renderer);
}