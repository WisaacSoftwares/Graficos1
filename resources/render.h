#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#define PIXEL_UNIT_MIN 12
#define PIXEL_UNIT_VIS 30
#define PIXEL_UNIT_MAX 100

extern SDL_Point CENTER;
extern int PIXELES_UNIDAD;

void IniciarRender();
void SetRenderDrawColor(SDL_Color color);
// Dibuja un rectángulo
void RenderRect(int x, int y, int w, int h, bool filled);
void DibujarIntro();
void DibujarGrafica();