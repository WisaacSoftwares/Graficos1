// Correr con el siguiente comando
// gcc prueba2.c -o prueba2 -I"./lib/SDL2-2.28.5/i686-w64-mingw32/include" -L"./lib/SDL2-2.28.5/i686-w64-mingw32/lib" -lSDL2
// # Para Ubuntu o Debian
// sudo apt-get install libsdl2-dev
// # Para Fedora
// sudo dnf install SDL2-devel

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#include "resources/library.h"

// Declaración de funciones
void DrawIntro (SDL_Renderer *renderer, TTF_Font *font, int delay);

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    int windowWidth, windowHeight;

    IniciarVentana(&window, &renderer, &windowWidth, &windowHeight, &font);

    // printf("Ancho de la ventana: %d\n", windowWidth);
    // printf("Alto de la ventana: %d\n", windowHeight);

    #pragma Dibujos

    DrawIntro(renderer, font, 3000);

    #pragma Plano Cartesiano

    // Background
    SDL_SetRenderDrawColor(renderer, 10, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Texto
    SDL_Color textColor = {225, 225, 255, 255};
    EscribirCanvas("Graficador", 10, 5, renderer, font, textColor);

    // Dibujar Plano Cartesiano
    int pixelsPerUnit = 50;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 127);
    SDL_RenderDrawLine(renderer, (int)(windowWidth/2), 0, (int)(windowWidth/2), windowHeight);
    SDL_RenderDrawLine(renderer, 0, (int)(windowHeight/2), windowWidth, (int)(windowHeight/2));

    SDL_Point center = {(int)(windowWidth/2), (int)(windowHeight/2)};
    for (int i = 0; i < windowWidth; i++){
        if (i % pixelsPerUnit == 0){
            // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderDrawLine(renderer, i, center.y + 10, i, center.y - 10);
        }
    }
    for (int j = 0; j < windowHeight; j++){
        if (j % pixelsPerUnit == 0){
            // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderDrawLine(renderer, center.x + 10, j, center.x - 10, j);
        }
    }

    // Dibujar una recta
    for (int i = 0; i < windowWidth; i++){
        int x = i -(int)(windowWidth/2);
        int f = x;

        int j = -f + (int)(windowHeight/2);

        SDL_SetRenderDrawColor(renderer, 225, 255, 0, 255);
        SDL_RenderDrawPoint(renderer, i, j);
    }

    // Dibujar una parabola
    

    SDL_Point points[windowWidth];
    for (int i = 0; i < windowWidth; i++){
        float x = (i - (windowWidth/2))*1.0/pixelsPerUnit;
        float f = x * x;

        int j = (int)(-(f*pixelsPerUnit) + (windowHeight/2));
        // printf("INPUT: %0.2f %0.2f, OUTPUT: %d %d\n", x, f, i, j);
        // Guardar punto
        SDL_Point point = {i, j};
        points[i] = point;

        SDL_SetRenderDrawColor(renderer, 225, 255, 0, 255);
        SDL_RenderDrawPoint(renderer, i, j);
    }
    SDL_SetRenderDrawColor(renderer, 225, 0, 0, 255);
    SDL_RenderDrawLines(renderer, points, windowWidth);

    SDL_RenderPresent(renderer);

    #pragma Close Events

    // SDL_Delay(3000);  // Espera 3000 milisegundos (3 segundos)
    // getchar();  // Espera a que se presione Enter antes de salir
    // system("PAUSE");
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_CloseFont(font);
    TTF_Quit();

    return 0;
}

void DrawIntro (SDL_Renderer *renderer, TTF_Font *font, int delay){
    // Background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Dibujar un punto rojo en (100, 100)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawPoint(renderer, 100, 100);

    // Dibujar una línea verde de (200, 200) a (300, 300)
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer, 200, 200, 300, 300);

    // Dibujar un rectángulo azul en (400, 400) con ancho 50 y alto 50
    SDL_Rect rect = {400, 400, 50, 50};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);

    // Dibujar un rectángulo relleno amarillo en (500, 500) con ancho 50 y alto 50
    SDL_Rect filledRect = {500, 500, 50, 50};
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &filledRect);

    // Dibujar un polígono púrpura
    SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
    SDL_Point points[] = {{100, 100}, {150, 100}, {50, 50}, {100, 100}};
    SDL_RenderDrawLines(renderer, points, 4);

    // Dibujar texto blanco en (100, 500)
    SDL_Color textColor = {225, 225, 255, 255};
    EscribirCanvas("Hola SDL2", 100, 500, renderer, font, textColor);

    #pragma Delay

    SDL_RenderPresent(renderer);
    // SDL_Delay(3000);

    // Uint32 startTime = SDL_GetTicks();  // Obtiene el tiempo de inicio

    EsperarTiempo(delay);
}