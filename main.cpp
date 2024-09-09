#include <iostream>
#include <thread>
#include <SDL2/SDL.h>

#include "MatrixMul.hpp"
#include "SpriteRender.cpp"

SDL_Window* Window_func(SDL_Window* window, SDL_Event& event, bool& cond){
    SDL_PollEvent(&event);
    if(event.window.event == SDL_WINDOWEVENT_CLOSE){
        cond = false;
        SDL_DestroyWindow(window);
    }
    return window;
}

SDL_Renderer* Refresh_func(SDL_Renderer* Renderer){
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderClear(Renderer);
    //SDL_RenderPresent(Renderer);
    return Renderer;
}

int main(){
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("This is SDL", 0, 0, 600, 480, 0);
    SDL_Renderer* Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;
    bool cond = true;
    float ang = 0;

    while(cond){
        Window_func(window, event, cond);
        Sprite_Draw(Renderer, ang);
        Refresh_func(Renderer);

        ang += 0.03f;
    }

    SDL_Quit();
    return 0;
}
