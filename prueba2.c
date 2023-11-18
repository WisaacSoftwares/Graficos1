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
#include <math.h>
#include "resources/library.h"
#include "resources/functions.h"
#include "resources/vectores.h"

SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font *font;
int windowWidth, windowHeight;
int pixelsPerUnit = 50;
SDL_Point center;

float flecha_pts[3][2] = {
    {0, 0},
    {-5, 10},
    {5, 10}
};

// Declaración de funciones
void DrawIntro (int delay);
void DrawPlano ();
void GraficarCuadratica (struct FuncionCuadratica funcion, SDL_Color color);
void GraficarLineal (struct FuncionLineal funcion, SDL_Color color);
void DrawVector (struct Vector vector, SDL_Color color);
void DrawFunciones ();
void DrawVectores ();

int main(int argc, char *argv[]) {
    IniciarVentana(&window, &renderer, &windowWidth, &windowHeight, &font);
    SDL_Point _center = {(int)(windowWidth/2), (int)(windowHeight/2)};
    center = _center;

    // Dibujos
    DrawIntro(1000);

    // Plano Cartesiano
    DrawPlano();

    // Funciones Matemáticas
    DrawFunciones();

    // Vectores
    DrawVectores();

    // fflush(stdout);

    // Close Events
    CerrarVentana(window, renderer, font);

    return 0;
}

void DrawIntro (int delay){
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

    EsperarTiempo(delay);
}

void DrawPlano (){
    // Background
    SDL_SetRenderDrawColor(renderer, 10, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Texto
    SDL_Color textColor = {225, 225, 255, 255};
    EscribirCanvas("Graficador", 10, 5, renderer, font, textColor);

    // Dibujar Plano Cartesiano
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 127);
    SDL_RenderDrawLine(renderer, (int)(windowWidth/2), 0, (int)(windowWidth/2), windowHeight);
    SDL_RenderDrawLine(renderer, 0, (int)(windowHeight/2), windowWidth, (int)(windowHeight/2));

    // X AXIS
    for (int i = 0; i < windowWidth; i++){
        int x = i -(int)(windowWidth/2);
        int f = x;

        int j = -f + (int)(windowHeight/2);

        int opacity = 255 - (int)(255.0*(i-100)/(windowWidth-200));
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, opacity);

        SDL_RenderDrawPoint(renderer, i, j);

        if (i % (pixelsPerUnit/2) == 0){
            SDL_RenderDrawLine(renderer, i + 10 , j, i - 10, j);
        }
    }
    EscribirCanvas("X", 80, windowHeight - 50, renderer, font, textColor);
    // Y AXIS
    for (int i = 0; i < windowWidth; i++){
        if (i % pixelsPerUnit == 0){
            // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderDrawLine(renderer, i, center.y + 10, i, center.y - 10);
        }
    }
    EscribirCanvas("Y", windowWidth - 30, center.y + 10, renderer, font, textColor);
    // Z AXIS
    for (int k = 0; k < windowHeight; k++){
        if (k % pixelsPerUnit == 0){
            // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderDrawLine(renderer, center.x + 10, k, center.x - 10, k);
        }
    }
    EscribirCanvas("Z", center.x - 20, 10, renderer, font, textColor);

    SDL_RenderPresent(renderer);
}

void GraficarCuadratica (struct FuncionCuadratica function, SDL_Color color){
    // printf("Function, p: %0.2f, h: %0.2f, k: %0.2f\n", function.p, function.h, function.k);

    SDL_Point points[windowWidth];
    for (int i = 0; i < windowWidth; i++){
        float x = (i - (windowWidth/2))*1.0/pixelsPerUnit;
        float y = EvaularFuncionCuadratica(function, x);

        int j = (int)(-(y*pixelsPerUnit) + (windowHeight/2));
        // printf("INPUT: %0.2f %0.2f, OUTPUT: %d %d\n", x, y, i, j);
        // Guardar punto
        SDL_Point point = {i, j};
        points[i] = point;

        // SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        // SDL_RenderDrawPoint(renderer, i, j);
    }
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLines(renderer, points, windowWidth);

    SDL_RenderPresent(renderer);
}

void GraficarLineal (struct FuncionLineal function, SDL_Color color){
    // printf("Function, p: %0.2f, h: %0.2f, k: %0.2f\n", function.p, function.h, function.k);

    SDL_Point points[windowWidth];
    for (int i = 0; i < windowWidth; i++){
        float x = (i - (windowWidth/2))*1.0/pixelsPerUnit;
        float y = EvaularFuncionLineal(function, x);

        int j = (int)(-(y*pixelsPerUnit) + (windowHeight/2));
        // printf("INPUT: %0.2f %0.2f, OUTPUT: %d %d\n", x, y, i, j);
        // Guardar punto
        SDL_Point point = {i, j};
        points[i] = point;

        // SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        // SDL_RenderDrawPoint(renderer, i, j);
    }
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLines(renderer, points, windowWidth);

    SDL_RenderPresent(renderer);
}

void DrawVector (struct Vector vector, SDL_Color color){
    int fase = (int)(vector.x*(pixelsPerUnit/2));
    int point[2];
    point[0] = (int)((vector.y*pixelsPerUnit) + center.x);
    point[1] = (int)(-(vector.z*pixelsPerUnit) + center.y);

    // Linea Principal
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, center.x, center.y, point[0] - fase, point[1] + fase);

    // Guías
    if (vector.x > 0) SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
    else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 50);
    
    SDL_RenderDrawLine(renderer, center.x, center.y, point[0] - fase, center.y + fase); // del origen hasta la proyección YX
    SDL_Rect rect1 = {center.x, point[1], (int)(vector.y*pixelsPerUnit), (int)(vector.z*pixelsPerUnit)};
    SDL_RenderDrawRect(renderer, &rect1);
    SDL_Rect rect2 = {center.x - fase, point[1] + fase, (int)(vector.y*pixelsPerUnit), (int)(vector.z*pixelsPerUnit)};
    SDL_RenderDrawRect(renderer, &rect2);
    SDL_RenderDrawLine(renderer, point[0], center.y, point[0] - fase, center.y + fase); // union 1
    SDL_RenderDrawLine(renderer, point[0], point[1], point[0] - fase, point[1] + fase); // union 2
    SDL_RenderDrawLine(renderer, center.x, point[1], center.x - fase, point[1] + fase); // union 2

    // Flecha
    float a_y = (center.y - (point[1] + fase))*1.0;
    float a_x = (point[0] - fase - center.x)*1.0;
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

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLines(renderer, points, 4);
    
    SDL_RenderPresent(renderer);
}

void DrawFunciones (){
    // Dibujar una recta
    struct FuncionLineal funcion1;
    funcion1.m = -2;
    funcion1.b = 1;
    SDL_Color funcion1_col = {0, 150, 0, 255};
    GraficarLineal(funcion1, funcion1_col);

    // Dibujar una parabola
    struct FuncionCuadratica funcion2;
    funcion2.p = 1;
    funcion2.h = 3;
    funcion2.k = -5;
    SDL_Color funcion2_col = {0, 0, 150, 255};
    GraficarCuadratica(funcion2, funcion2_col);
}

void DrawVectores (){
    struct Vector vector1;
    vector1.nombre = "Vector Amarillo";
    vector1.x = 1;
    vector1.y = 4;
    vector1.z = 2;
    SDL_Color vector1_col = {255, 255, 0, 255};

    struct Vector vector2;
    vector2.nombre = "Vector Azul";
    vector2.x = -2;
    vector2.y = 2;
    vector2.z = 3;
    SDL_Color vector2_col = {0, 0, 255, 255};

    struct Vector vector3;
    vector3.nombre = "Vector Rojo";
    vector3.x = 4;
    vector3.y = -4;
    vector3.z = -2;
    SDL_Color vector3_col = {255, 0, 0, 255};

    DrawVector(vector1, vector1_col);
    DrawVector(vector2, vector2_col);
    DrawVector(vector3, vector3_col);
}