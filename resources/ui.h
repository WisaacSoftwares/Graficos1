#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MENU_WIDTH 420
#define MENU_HEIGHT 500
#define MENU_CONTROL_W 400
#define MENU_CONTROL_H 30

extern int OPC_SELECCIONADA;

// Dibuja un pequeño menu para que el usuario escriba y retorna el texto
char* ObtenerTexto(char * titulo, int numChar, char * texto, bool soloNumeros);
// Dibuja un menu y retorna un id de la opcion que el usuario selecciono
int DibujarMenu(char * titulo, char **opciones, int numOpciones);
// Dibuja un menu especial para vectores y retorna un id del vector seleccionado
int DibujarMenuVectores(char * titulo, char *primerOpcion, bool mostrarNuevo);
// Dibuja un menu de segundo tipo y retorna un id de la opcion que el usuario selecciono
int DibujarMenuSecundario(char * titulo, char **opciones, int numOpciones);
int DibujarMenuVectorPropiedades(char * titulo, char *primerOpcion, int idVector);
void DibujarMuchoTexto(char * titulo, char **texto, int numFilas);