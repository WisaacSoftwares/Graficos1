#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void IniciarVentana (SDL_Window **window, SDL_Renderer **renderer, int *windowWidth, int *windowHeight, TTF_Font **font);

void EsperarTiempo(int tiempoEspera);

void EscribirCanvas(char *texto, int x, int y, SDL_Renderer *renderer, TTF_Font *font, SDL_Color textColor);