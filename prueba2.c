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

// Declaración de funciones
void IniciarVentana (SDL_Window **window, SDL_Renderer **renderer, int *windowWidth, int *windowHeight, TTF_Font **font);

void EsperarTiempo(int tiempoEspera);

void EscribirCanvas(char *texto, SDL_Renderer *renderer, TTF_Font *font);

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    int windowWidth, windowHeight;

    IniciarVentana(&window, &renderer, &windowWidth, &windowHeight, &font);

    // printf("Ancho de la ventana: %d\n", windowWidth);
    // printf("Alto de la ventana: %d\n", windowHeight);

    #pragma Dibujos

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
    SDL_Point points[] = {{100, 100}, {150, 150}, {50, 50}};
    SDL_RenderDrawLines(renderer, points, 3);

    // Dibujar texto blanco en (100, 500)
    EscribirCanvas("Hola SDL2", renderer, font);

    #pragma Delay

    SDL_RenderPresent(renderer);
    // SDL_Delay(3000);

    Uint32 startTime = SDL_GetTicks();  // Obtiene el tiempo de inicio

    EsperarTiempo(3000);

    #pragma Plano Cartesiano

    // Background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Texto
    EscribirCanvas("Prueba de texto", renderer, font);

    // Dibujar Plano Cartesiano
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, (int)(windowWidth/2), 0, (int)(windowWidth/2), windowHeight);
    SDL_RenderDrawLine(renderer, 0, (int)(windowHeight/2), windowWidth, (int)(windowHeight/2));

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

void IniciarVentana (SDL_Window **window, SDL_Renderer **renderer, int *windowWidth, int *windowHeight, TTF_Font **font){
    // SDL_Init(SDL_INIT_VIDEO);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        // return 1;
        printf("Ocurrió un error al inicializar SDL\n");
    }

    *window = SDL_CreateWindow("Mi Programa Graficador",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    800, 600, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        printf("Ocurrió un error al crear la ventana\n");
        // return 1;
    }

    SDL_GetWindowSize(*window, windowWidth, windowHeight);

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

    // Fuentes
    if (TTF_Init() != 0) {
        fprintf(stderr, "Error initializing SDL_ttf: %s\n", TTF_GetError());
        printf("Ocurrió un error al crear la ventana\n");
        // return 1;
    }

    // font = TTF_OpenFont("Arial", 24);
    *font = TTF_OpenFont("resources/Roboto-Regular.ttf", 24);

    if (font == NULL) {
        fprintf(stderr, "Error loading font: %s\n", TTF_GetError());
        // return 1;
        printf("Ocurrió un error al cargar las fuentes\n");
    }
}

// Implementación de la función
void EsperarTiempo(int tiempoEspera) {
    Uint32 startTime = SDL_GetTicks();  // Obtiene el tiempo de inicio

    Uint32 waitTime = tiempoEspera;
    // Espera hasta que haya pasado el tiempo deseado
    while (SDL_GetTicks() - startTime < waitTime) {
        // Manejar eventos para evitar que la aplicación parezca congelada
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                // Manejar eventos de cierre de ventana aquí si es necesario
                break;
            }
        }
    }
}

void EscribirCanvas(char *texto, SDL_Renderer *renderer, TTF_Font *font) {
    // Dibujar texto blanco en (100, 500)
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, texto, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    SDL_Rect textRect = {100, 500, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
}