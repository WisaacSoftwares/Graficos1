/* cSpell:disable */
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 30
#define ARRAYLENGHT(x) (sizeof(x)/ sizeof((x)[0]))

// Declarar Variables Globales
extern SDL_Window *WINDOW;
extern SDL_Renderer *RENDERER;
extern int W_WIDTH;
extern int W_HEIGHT;
extern SDL_Point W_CENTER;
extern TTF_Font *FONT_MAIN;
extern TTF_Font *FONT_BOLD;
extern TTF_Font *FONT_SMALL;

// Colores
extern SDL_Color COLOR_TRANSPARENTE;
extern SDL_Color COLOR_NEGRO;
extern SDL_Color COLOR_BLANCO;
extern SDL_Color COLOR_GRIS;
extern SDL_Color COLOR_GRIS_CLARO;
extern SDL_Color COLOR_GRIS_OSCURO;
extern SDL_Color COLOR_ROJO;
extern SDL_Color COLOR_VERDE;
extern SDL_Color COLOR_VERDE_OSCURO;
extern SDL_Color COLOR_AZUL;
extern SDL_Color COLOR_AMARILLO;
extern SDL_Color COLOR_NARANJA;
extern SDL_Color COLOR_CYAN;
extern SDL_Color COLOR_CREMA;
extern SDL_Color COLOR_MORADO;
extern SDL_Color COLOR_KHAKI;


void IniciarVentana ();
void CerrarVentana ();
void EscribirTexto(char *texto, int x, int y, TTF_Font *font, SDL_Color textColor, bool fondo);
void EscribirTextoCentrado(char *texto, int x, int y, TTF_Font *font, SDL_Color textColor, bool fondo);
void EscribirTextoDerecha(char *texto, int x, int y, TTF_Font *font, SDL_Color textColor, bool fondo);
void EsperarTiempo(int milisegundos);
void EsperarTecla();
void LiberarInput();