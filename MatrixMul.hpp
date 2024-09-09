#pragma once

#include <iostream>
#include <SDL2/SDL.h>

struct Point3d {
    float x;
    float y;
    float z;
};

Point3d matmul_st(float projMat[][3], unsigned int size, Point3d points){
    Point3d result;
    float arr[3] {0,0,0};
    for(std::size_t i = 0; i < size; ++i){
        float sum = 0;
        sum += projMat[i][0] * points.x;
        sum += projMat[i][1] * points.y;
        sum += projMat[i][2] * points.z;
        arr[i] = sum;
    }

    result.x = arr[0];
    result.y = arr[1];
    result.z = arr[2];

    return result;
}

Point3d* Scale_pt(Point3d* points, float val){
    points->x *= val;
    points->y *= val;
    points->z *= val;

    return points;
}

void Point_connect(SDL_Renderer* Renderer, int i, int j, Point3d projected[]){
    Point3d a = projected[i];
    Point3d b = projected[j];
    SDL_RenderDrawLineF(Renderer, 300 + a.x, 240 + a.y, 300 + b.x, 240 + b.y);
}