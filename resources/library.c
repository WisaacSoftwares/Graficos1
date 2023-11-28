#include "library.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "render.h"

// Variables Globales
SDL_Window *WINDOW = NULL;
SDL_Renderer *RENDERER = NULL;
int W_WIDTH;
int W_HEIGHT;
SDL_Point W_CENTER;
TTF_Font *FONT_MAIN = NULL;
TTF_Font *FONT_BOLD = NULL;
TTF_Font *FONT_SMALL = NULL;

// Colores
SDL_Color COLOR_TRANSPARENTE = {0, 0, 0, 0};
SDL_Color COLOR_NEGRO = {0, 0, 0, 255};
SDL_Color COLOR_BLANCO = {255, 255, 255, 255};
SDL_Color COLOR_GRIS = {140, 140, 140, 255};
SDL_Color COLOR_GRIS_CLARO = {230, 230, 230, 255};
SDL_Color COLOR_GRIS_OSCURO = {90, 90, 90, 255};
SDL_Color COLOR_ROJO = {255, 0, 0, 255};
SDL_Color COLOR_VERDE = {0, 255, 0, 255};
SDL_Color COLOR_VERDE_OSCURO = {66, 170, 66, 255};
SDL_Color COLOR_AZUL = {0, 0, 255, 255};
SDL_Color COLOR_AMARILLO = {255, 255, 0, 255};
SDL_Color COLOR_NARANJA = {255, 130, 0, 255};
SDL_Color COLOR_CYAN = {0, 125, 255, 255};
SDL_Color COLOR_CREMA = {255, 190, 127, 255};
SDL_Color COLOR_MORADO = {255, 190, 127, 255};
SDL_Color COLOR_KHAKI = {240, 230, 140, 255};

void IniciarVentana (){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error al iniciar SDL: %s\n", SDL_GetError());
    }
    WINDOW = SDL_CreateWindow("Graficador de Vectores", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    if (WINDOW == NULL) {
        fprintf(stderr, "Error al crear ventana: %s\n", SDL_GetError());
    }

    SDL_GetWindowSize(WINDOW, &W_WIDTH, &W_HEIGHT);
    W_CENTER.x = (int)(W_WIDTH/2);
    W_CENTER.y = (int)(W_HEIGHT/2);
    
    RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(RENDERER, SDL_BLENDMODE_BLEND);

    // Fuentes
    if (TTF_Init() != 0) {
        fprintf(stderr, "Error iniciando SDL_ttf: %s\n", TTF_GetError());
    }

    FONT_MAIN = TTF_OpenFont("resources/fonts/consola.ttf", 24);
    FONT_BOLD = TTF_OpenFont("resources/fonts/consolab.ttf", 26);
    FONT_SMALL = TTF_OpenFont("resources/fonts/consola.ttf", 18);
    if (FONT_MAIN == NULL || FONT_SMALL == NULL || FONT_BOLD == NULL) {
        fprintf(stderr, "Error al cargar fuente de recursos: %s\n", TTF_GetError());
    }

    fflush(stdout);
}

void CerrarVentana (){
    SDL_RenderClear(RENDERER);
    SDL_DestroyRenderer(RENDERER);
    SDL_DestroyWindow(WINDOW);
    SDL_Quit();
    TTF_CloseFont(FONT_MAIN);
    TTF_CloseFont(FONT_SMALL);
    TTF_Quit();
}

void EscribirTexto(char *texto, int x, int y, TTF_Font *font, SDL_Color textColor, bool fondo){
    if (texto == NULL || font == NULL) return;

    SDL_Surface* surface = TTF_RenderText_Solid(font, texto, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(RENDERER, surface);
    SDL_FreeSurface(surface);

    SDL_Rect textRect = {x, y, surface->w, surface->h};
    if (fondo) SDL_RenderFillRect(RENDERER, &textRect);
    SDL_RenderCopy(RENDERER, texture, NULL, &textRect);

    SDL_DestroyTexture(texture);
}

void EscribirTextoCentrado(char *texto, int x, int y, TTF_Font *font, SDL_Color textColor, bool fondo){
    if (texto == NULL || font == NULL) return;

    SDL_Surface* surface = TTF_RenderText_Solid(font, texto, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(RENDERER, surface);
    SDL_FreeSurface(surface);
    // Obtener las dimensiones del texto
    int textWidth, textHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
    // Calcular la posición para centrar el texto en la ventana
    x -= textWidth/2;
    y -= textHeight/2;
    // Imprimir texto
    SDL_Rect textRect = {x, y, surface->w, surface->h};
    if (fondo) SDL_RenderFillRect(RENDERER, &textRect);
    SDL_RenderCopy(RENDERER, texture, NULL, &textRect);

    SDL_DestroyTexture(texture);
}

void EscribirTextoDerecha(char *texto, int x, int y, TTF_Font *font, SDL_Color textColor, bool fondo){
    if (texto == NULL || font == NULL) return;

    SDL_Surface* surface = TTF_RenderText_Solid(font, texto, textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(RENDERER, surface);
    SDL_FreeSurface(surface);
    // Obtener las dimensiones del texto
    int textWidth, textHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
    // Calcular la posición para centrar el texto en la ventana
    x -= textWidth;
    // Imprimir texto
    SDL_Rect textRect = {x, y, surface->w, surface->h};
    if (fondo) SDL_RenderFillRect(RENDERER, &textRect);
    SDL_RenderCopy(RENDERER, texture, NULL, &textRect);

    SDL_DestroyTexture(texture);
}

void EsperarTiempo(int milisegundos){
    Uint32 startTime = SDL_GetTicks();  // Settear tiempo de inicio
    Uint32 waitTime = milisegundos;
    // Esperar
    while (SDL_GetTicks() - startTime < waitTime) {
        // Seguir recibiendo entrada para no trabar la ventana
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }
    }
}

void EsperarTecla(){
    bool termino = false;
    SDL_Event e;

    SetRenderDrawColor(COLOR_NEGRO);
    EscribirTextoCentrado("Presiona cualquier tecla para continuar", W_CENTER.x, W_HEIGHT - 30, FONT_SMALL, COLOR_GRIS, true);
    SDL_RenderPresent(RENDERER);

    while (!termino)
    {
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT) {
                // Cerrar Programa
                CerrarVentana();
                exit(0);
            } else if (e.type == SDL_KEYDOWN) {
                termino = true;
                SDL_RenderClear(RENDERER);
            }
        }
    }
}

void LiberarInput() {
    EscribirTextoCentrado(" ", W_CENTER.x, W_HEIGHT - 50, FONT_SMALL, COLOR_TRANSPARENTE, false);
}

char * DoubleToStr(double x){
    int size = snprintf(NULL, 0, "%0.2f", x);
    char * cteChar = (char *)malloc(size + 1);
    sprintf(cteChar, "%0.2f", x);
    return cteChar;
}