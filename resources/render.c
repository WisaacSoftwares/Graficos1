#include "render.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "library.h"
#include "vectores.h"

SDL_Point CENTER;
int PIXELES_UNIDAD = 50;
int OPACIDAD_CENTRO;

float flecha_pts[3][2] = {
    {0, 0},
    {-5, 10},
    {5, 10}
};

void IniciarRender(){
    CENTER.x = (int)(W_WIDTH/2);
    CENTER.y = (int)(W_HEIGHT/2);
}

void SetRenderDrawColor(SDL_Color color){
    SDL_SetRenderDrawColor(RENDERER, color.r, color.g, color.b, color.a);
}

void RenderRect(int x, int y, int w, int h, bool filled){
    SDL_Rect rect = {x, y, w, h};
    if (filled) SDL_RenderFillRect(RENDERER, &rect);
    else SDL_RenderDrawRect(RENDERER, &rect);
}

void DibujarIntro(){
    // Fondo
    SetRenderDrawColor(COLOR_NEGRO);
    SDL_RenderClear(RENDERER);

    // Créditos
    EscribirTextoCentrado("Graficador", W_CENTER.x, 100, FONT_BOLD, COLOR_BLANCO, false);
}

void DibujarGrilla(){
    int grilla[] = {
        CENTER.x - 5*PIXELES_UNIDAD,
        CENTER.y + 5*PIXELES_UNIDAD,
        CENTER.x + 5*PIXELES_UNIDAD,
        CENTER.y - 5*PIXELES_UNIDAD
    };
    int grillaH[] = {
        CENTER.x - 10*PIXELES_UNIDAD,
        CENTER.y,
        CENTER.x + 10*PIXELES_UNIDAD,
        CENTER.y
    };
    SDL_SetRenderDrawColor(RENDERER, 255, 255, 255, 15);
    for (int i = 1; i <= 10; i++)
    {
        SDL_RenderDrawLine(RENDERER, grilla[0] + (i*PIXELES_UNIDAD), grilla[1], grilla[2] + (i*PIXELES_UNIDAD), grilla[3]);
        SDL_RenderDrawLine(RENDERER, grilla[0] - (i*PIXELES_UNIDAD), grilla[1], grilla[2] - (i*PIXELES_UNIDAD), grilla[3]);
    }
    for (int i = 1; i <= 10; i++)
    {
        int desface = (int)(i*PIXELES_UNIDAD/2);
        SDL_RenderDrawLine(RENDERER, grillaH[0] - desface, grillaH[1] + desface, grillaH[2] - desface, grillaH[3] + desface);
        SDL_RenderDrawLine(RENDERER, grillaH[0] + desface, grillaH[1] - desface, grillaH[2] + desface, grillaH[3] - desface);
    }
}

void DibujarEjes(){
    SDL_Color textColor2 = {225, 225, 255, OPACIDAD_CENTRO};
    SDL_Color textColorX = {225, 225, 255, OPACIDAD_CENTRO};

    int cuadricula = (int)(10 * PIXELES_UNIDAD / PIXEL_UNIT_MAX);
    int opacidad;
    // X AXIS
    for (int i = 0; i < W_WIDTH; i++){
        int x = i - CENTER.x;
        int j = -x + CENTER.y;
        // Efecto Opacidad
        if (abs(i-CENTER.x) < W_WIDTH/2 && abs(i-CENTER.x) != 0) opacidad = OPACIDAD_CENTRO*(1-abs(i-CENTER.x)*1.0/(W_WIDTH/2));
        else opacidad = 0;
        // printf("Opacity: %d\t", opacidad);
        SDL_SetRenderDrawColor(RENDERER, 255, 255, 255, opacidad);
        if (opacidad > 0) textColorX.a = opacidad;
        else textColorX.a = 1;
        // Dibujar punto
        if (opacidad != 0) SDL_RenderDrawPoint(RENDERER, i, j);
        // Cuadricula
        if (opacidad != 0 && (i - CENTER.x) % (PIXELES_UNIDAD/2) == 0){
            SDL_RenderDrawLine(RENDERER, i + cuadricula , j, i - cuadricula, j);
            // Numeración
            if (PIXELES_UNIDAD > PIXEL_UNIT_VIS && (i - CENTER.x) % (PIXELES_UNIDAD/2)*5 == 0 && i > CENTER.x){
                char num_s[4];
                snprintf(num_s, sizeof(num_s), "%d", -(int)((i - CENTER.x) / (PIXELES_UNIDAD/2))); // -(int)((i - CENTER.x) / (PIXELES_UNIDAD/2))
                
                EscribirTextoCentrado(num_s, i - 15, j - 15, FONT_SMALL, textColorX, false);
            }
        }
    }
    for (int i = W_WIDTH; i >= 0; i--){
        int x = i - CENTER.x;
        int j = -x + CENTER.y;
        // Cuadricula
        if ((i - CENTER.x) % (PIXELES_UNIDAD/2) == 0 && i < CENTER.x){
            // Efecto Opacidad
            if (abs(i-CENTER.x) < W_WIDTH/2 && abs(i-CENTER.x) != 0) opacidad = OPACIDAD_CENTRO*(1-abs(i-CENTER.x)*1.0/(W_WIDTH/2));
            else opacidad = 0;
            SDL_SetRenderDrawColor(RENDERER, 255, 255, 255, opacidad);
            if (opacidad > 0) textColorX.a = opacidad;
            else textColorX.a = 1;
            // Numeración
            if (opacidad != 0 && PIXELES_UNIDAD > PIXEL_UNIT_VIS && (i - CENTER.x) % (PIXELES_UNIDAD/2)*5 == 0){
                char num_s[4];
                snprintf(num_s, sizeof(num_s), "%d", -(int)((i - CENTER.x) / (PIXELES_UNIDAD/2)));
                EscribirTextoCentrado(num_s, i - 15, j - 15, FONT_SMALL, textColorX, false);
            }
        }
    }
    
    SDL_SetRenderDrawColor(RENDERER, 255, 255, 255, OPACIDAD_CENTRO);
    // Y AXIS
    for (int i = 0; i < W_WIDTH; i++){
        if ((i - CENTER.x) % PIXELES_UNIDAD == 0 && i > CENTER.x){
            SDL_RenderDrawLine(RENDERER, i, CENTER.y + cuadricula, i, CENTER.y - cuadricula);
            if (PIXELES_UNIDAD > PIXEL_UNIT_VIS && (i - CENTER.x) % PIXELES_UNIDAD*5 == 0){
                char num_s1[4];
                snprintf(num_s1, sizeof(num_s1), "%d", (int)((i - CENTER.x) / PIXELES_UNIDAD));
                EscribirTextoCentrado(num_s1, i, CENTER.y - 15, FONT_SMALL, textColor2, false);
            }
        }
    }
    for (int i = CENTER.x - 1; i > 0; i--){
        if ((i - CENTER.x) % PIXELES_UNIDAD == 0){
            SDL_RenderDrawLine(RENDERER, i, CENTER.y + cuadricula, i, CENTER.y - cuadricula);
            if (PIXELES_UNIDAD > PIXEL_UNIT_VIS && (i - CENTER.x) % PIXELES_UNIDAD*5 == 0){
                char num_s1[4];
                snprintf(num_s1, sizeof(num_s1), "%d", (int)((i - CENTER.x) / PIXELES_UNIDAD));
                EscribirTextoCentrado(num_s1, i, CENTER.y - 15, FONT_SMALL, textColor2, false);
            }
        }
    }
    // Z AXIS
    for (int k = 0; k < W_HEIGHT; k++){
        if ((k - CENTER.y) % PIXELES_UNIDAD == 0 && k > CENTER.y){
            SDL_RenderDrawLine(RENDERER, CENTER.x + cuadricula, k, CENTER.x - cuadricula, k);
            if (PIXELES_UNIDAD > PIXEL_UNIT_VIS && (k - CENTER.y) % PIXELES_UNIDAD*5 == 0){
                char num_s1[4];
                snprintf(num_s1, sizeof(num_s1), "%d", -(int)((k - CENTER.y) / PIXELES_UNIDAD));
                EscribirTextoCentrado(num_s1, CENTER.x - 15, k, FONT_SMALL, textColor2, false);
            }
        }
    }
    for (int k = CENTER.y - 1; k > 0; k--){
        if ((k - CENTER.y) % PIXELES_UNIDAD == 0){
            SDL_RenderDrawLine(RENDERER, CENTER.x + cuadricula, k, CENTER.x - cuadricula, k);
            if (PIXELES_UNIDAD > PIXEL_UNIT_VIS && (k - CENTER.y) % PIXELES_UNIDAD*5 == 0){
                char num_s1[4];
                snprintf(num_s1, sizeof(num_s1), "%d", -(int)((k - CENTER.y) / PIXELES_UNIDAD));
                EscribirTextoCentrado(num_s1, CENTER.x - 15, k, FONT_SMALL, textColor2, false);
            }
        }
    }

    // Textos
    int xLabelPos = CENTER.y+CENTER.x-500;
    if (xLabelPos < CENTER.x) EscribirTextoCentrado("+X", xLabelPos - 30, W_HEIGHT - 25, FONT_BOLD, COLOR_BLANCO, false);
    EscribirTextoCentrado("+Y", W_WIDTH - 35, CENTER.y + 25, FONT_BOLD, COLOR_BLANCO, false);
    EscribirTextoCentrado("+Z", CENTER.x - 35, 25, FONT_BOLD, COLOR_BLANCO, false);
    EscribirTexto("Graficador", 10, 5, FONT_BOLD, COLOR_BLANCO, false);
}

void DibujarPlano(){
    // Background
    SetRenderDrawColor(COLOR_NEGRO);
    SDL_RenderClear(RENDERER);
    // Opacidad General
    OPACIDAD_CENTRO = (int)(255.0*PIXELES_UNIDAD/PIXEL_UNIT_MAX);
    // Dibujar Plano Cartesiano
    SDL_SetRenderDrawColor(RENDERER, 255, 255, 255, OPACIDAD_CENTRO);
    SDL_RenderDrawLine(RENDERER, CENTER.x, 0, CENTER.x, W_HEIGHT);
    SDL_RenderDrawLine(RENDERER, 0, CENTER.y, W_WIDTH, CENTER.y);
    // Grilla
    DibujarGrilla();
    // Ejes
    DibujarEjes();
}

void DibujarVector(int ID){
    int fase = (int)(VECTORES[ID].x*(PIXELES_UNIDAD/2));
    int point[2];
    point[0] = (int)((VECTORES[ID].y*PIXELES_UNIDAD) + CENTER.x);
    point[1] = (int)(-(VECTORES[ID].z*PIXELES_UNIDAD) + CENTER.y);

    // Guías
    SDL_SetRenderDrawColor(RENDERER, VECTORES[ID].color.r, VECTORES[ID].color.g, VECTORES[ID].color.b, 100);
    
    SDL_RenderDrawLine(RENDERER, CENTER.x, CENTER.y, point[0] - fase, CENTER.y + fase); // del origen hasta la proyección YX
    RenderRect(CENTER.x, point[1], (int)(VECTORES[ID].y*PIXELES_UNIDAD), (int)(VECTORES[ID].z*PIXELES_UNIDAD), false);
    RenderRect(CENTER.x - fase, point[1] + fase, (int)(VECTORES[ID].y*PIXELES_UNIDAD), (int)(VECTORES[ID].z*PIXELES_UNIDAD), false);
    SDL_RenderDrawLine(RENDERER, point[0], CENTER.y, point[0] - fase, CENTER.y + fase); // union 1
    SDL_RenderDrawLine(RENDERER, point[0], point[1], point[0] - fase, point[1] + fase); // union 2
    SDL_RenderDrawLine(RENDERER, CENTER.x, point[1], CENTER.x - fase, point[1] + fase); // union 2

    // Flecha
    float a_y = (CENTER.y - (point[1] + fase))*1.0;
    float a_x = (point[0] - fase - CENTER.x)*1.0;
    float a = atan(a_y/a_x);
    if (a_x < 0) a += M_PI;

    float h1 = sqrt(pow(flecha_pts[1][0], 2) + pow(flecha_pts[1][1], 2));
    float h2 = sqrt(pow(flecha_pts[2][0], 2) + pow(flecha_pts[2][1], 2));
    float b1 = asin(flecha_pts[1][0]/h1);
    float b2 = asin(flecha_pts[2][0]/h1);

    float x1 = h1*sin(b1 - a);
    float y1 = h1*cos(b1 -a);

    float flecha[3][2] = {
        {0, 0},
        {h1*sin(b1 - (M_PI/2 - a)), h1*cos(b1 - (M_PI/2 - a))},
        {h2*sin(b2 - (M_PI/2 - a)), h2*cos(b2 - (M_PI/2 - a))}
    };
    SDL_Point points[] = {
        {point[0] + flecha[0][0] - fase, point[1] + flecha[0][1] + fase},
        {point[0] + flecha[1][0] - fase, point[1] + flecha[1][1] + fase},
        {point[0] + flecha[2][0] - fase, point[1] + flecha[2][1] + fase},
        {point[0] + flecha[0][0] - fase, point[1] + flecha[0][1] + fase}
    };
    
    // Linea Principal
    SetRenderDrawColor(VECTORES[ID].color);
    SDL_RenderDrawLine(RENDERER, CENTER.x, CENTER.y, point[0] - fase, point[1] + fase);
    // Flecha
    SDL_RenderDrawLines(RENDERER, points, 4);
}

void DibujarVectores(){
    for (int i = 0; i < NumeroVectores(); i++)
    {
        DibujarVector(i);
    }
}

void DibujarGrafica(){
    DibujarPlano();
    DibujarVectores();
}