// gcc  -I"./resources/SDL2-windows/include"  -L"./resources/SDL2-windows/lib"  main.c resources/library.c resources/functions.c resources/vectores.c -o main -lSDL2 -lSDL2_ttf
// Fedora sudo dnf install SDL2-devel
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "resources/library.h"
#include "resources/vectores.h"
#include "resources/render.h"
#include "resources/ui.h"
#include "resources/controlador.h"

bool mostrarMenu = false;

int main(int argc, char *argv[]) {
    IniciarVentana();
    IniciarVectores();
    IniciarRender();
    DibujarIntro();
    // EsperarTecla();
    bool termino = false;

    while (!termino) {
        termino = InputGeneral();
        DibujarGrafica();
        SDL_RenderPresent(RENDERER);
    }
    // DibujarIntro();
    // EsperarTecla();
    
    // getchar();
    CerrarVentana();

    return 0;
}

