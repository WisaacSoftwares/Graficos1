#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

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

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(*renderer, SDL_BLENDMODE_BLEND);

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

void CerrarVentana (SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font){
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

void EscribirCanvas(char *texto, int x, int y, SDL_Renderer *renderer, TTF_Font *font, SDL_Color textColor) {
    // Dibujar texto blanco en (100, 500)
    SDL_Surface* surface = TTF_RenderText_Solid(font, texto, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    SDL_Rect textRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
}

