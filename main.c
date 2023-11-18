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
#include <stdbool.h>
#include <math.h>
#include "resources/library.h"
#include "resources/functions.h"
#include "resources/vectores.h"

#define PIXEL_UNIT_MIN 12
#define PIXEL_UNIT_VIS 30
#define PIXEL_UNIT_MAX 100

bool isRunning = true;
bool mostrarMenu = false;
SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font *font;
TTF_Font * font_sm;
int windowWidth, windowHeight;
SDL_Point center;
int pixelsPerUnit = 50;

float flecha_pts[3][2] = {
    {0, 0},
    {-5, 10},
    {5, 10}
};

struct Vector vectores[10];
struct Vector vectorNulo = {NULL, 0.0f, 0.0f, 0.0f, {0, 0, 0}};

// Declaración de funciones
void CheckInput ();
void Render();
void DrawIntro (int delay);
void DrawPlano ();
void DrawVector (struct Vector vector);
void DrawVectores ();
void DrawMenu ();

int main(int argc, char *argv[]) {
    IniciarVentana(&window, &renderer, &windowWidth, &windowHeight, &font);
    SDL_Point _center = {(int)(windowWidth/2), (int)(windowHeight/2)};
    center = _center;
    font_sm = TTF_OpenFont("resources/Roboto-Regular.ttf", 16);

    // Intro
    // DrawIntro(1000);

    struct Vector vector1 = {"Vector Azul", 1, 2, 1, {0, 0, 255, 255}};
    struct Vector vector2 = {"Vector Amarillo", -2, 1, 1, {255, 255, 0, 255}};
    struct Vector vector3 = {"Vector Rojo", 1, -3, 5, {255, 0, 0, 255}};
    vectores[0] = vector1;
    vectores[1] = vector2;
    vectores[2] = vector3;
    vectores[3] = vectorNulo;

    Render();

    // Bucle Principal
    while (isRunning)
    {
        CheckInput();
    }

    // Close Events
    CerrarVentana(window, renderer, font);

    return 0;
}

void CheckInput (){
    SDL_Event event;
    SDL_PollEvent (&event);

    if (event.type == SDL_QUIT){
        isRunning = false;
    }
    else if (event.type == SDL_MOUSEWHEEL && !mostrarMenu){
        // Manejar el desplazamiento del ratón aquí
        int scrollDirection = event.wheel.y;
        if (scrollDirection < 0){
            if (pixelsPerUnit > PIXEL_UNIT_MIN) pixelsPerUnit = pixelsPerUnit - 1;
        } else {
            if (pixelsPerUnit < PIXEL_UNIT_MAX) pixelsPerUnit = pixelsPerUnit + 1;
        }
        // printf("Mouse Scroll Direction: %d\n", scrollDirection);
        // fflush(stdout);
        Render();
        // SDL_Delay(10);
    }
    else if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym)
        {
            case SDLK_PLUS:
            case SDLK_KP_PLUS:
                if (pixelsPerUnit < PIXEL_UNIT_MAX && !mostrarMenu) pixelsPerUnit = pixelsPerUnit + 2;
                // printf("Presionaste mas! pixelsPerUnit = %d\n", pixelsPerUnit);
                Render();
                break;
            case SDLK_MINUS:
            case SDLK_KP_MINUS:
                if (pixelsPerUnit > PIXEL_UNIT_MIN && !mostrarMenu) pixelsPerUnit = pixelsPerUnit - 2;
                // printf("Presionaste menos! pixelsPerUnit = %d\n", pixelsPerUnit);
                Render();
                break;
            case SDLK_ESCAPE:
                isRunning = false;
                break;
            case SDLK_RETURN:
                // printf("Presionaste enter!\n");
                Render();
                break;
            case SDLK_SPACE:
                // printf("Presionaste espacio!\n");
                Render();
                break;
            case SDLK_m:
                if (mostrarMenu) mostrarMenu = false;
                else mostrarMenu = true;
                // printf("mostrarMenu: %d\n", mostrarMenu);
                Render();
                break;
            default:
                break;
        }
    }
}

void Render(){
    // Plano Cartesiano
    DrawPlano();

    // Vectores
    DrawVectores();

    // Menu
    if (mostrarMenu) DrawMenu();

    SDL_RenderPresent(renderer);
    fflush(stdout);
}

void DrawIntro (int delay){
    // Background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Dibujar texto blanco en (100, 500)
    SDL_Color textColor = {225, 225, 255, 255};
    char *texto[] = {
        "GRAFICADOR DE FUNCIONES",
        "Luis Isaac Tavera Zarate",
        "Leonardo Alejandro Roldan Alvarado",
        "Angel Gael Milantoni Perez",
        "Joseph Alfonso Jasso Estrada",
        "Angel Owen Torres Martinez",
        NULL
    };
    int i = 0;
    while(texto[i] != NULL){
        EscribirCanvasCentrado(texto[i], center.x, center.y - 75 + (i*25), renderer, font_sm, textColor);

        i++;
    }

    SDL_RenderPresent(renderer);

    #pragma Delay

    EsperarTiempo(delay);

    SDL_Color textColor2 = {225, 225, 255, 150};
    EscribirCanvasCentrado("Presiona ENTER para continuar", center.x, windowHeight - 50, renderer, font_sm, textColor2);
    SDL_RenderPresent(renderer);
}

void DrawPlano (){
    // Background
    SDL_SetRenderDrawColor(renderer, 10, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Texto
    SDL_Color textColor = {225, 225, 255, 255};
    SDL_Color textColor2 = {225, 225, 255, 80};
    EscribirCanvas("Graficador", 10, 5, renderer, font, textColor);

    // Dibujar Plano Cartesiano
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 127);
    SDL_RenderDrawLine(renderer, (int)(windowWidth/2), 0, (int)(windowWidth/2), windowHeight);
    SDL_RenderDrawLine(renderer, 0, (int)(windowHeight/2), windowWidth, (int)(windowHeight/2));

    int cuadricula = (int)(10 * pixelsPerUnit / PIXEL_UNIT_MAX);

    // X AXIS
    for (int i = 0; i < windowWidth; i++){
        int x = i -(int)(windowWidth/2);
        int f = x;

        int j = -f + (int)(windowHeight/2);

        int opacity = 255 - (int)(255.0*(i-100)/(windowWidth-200));
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, opacity);

        SDL_RenderDrawPoint(renderer, i, j);

        if ((i - center.x) % (pixelsPerUnit/2) == 0 && i > center.x){
            int sim_i = 2*center.x - i;
            int sim_j = 2*center.y - j;
            SDL_RenderDrawLine(renderer, i + cuadricula , j, i - cuadricula, j);
            opacity = (int)(255.0*(i-100)/(windowWidth-200));
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, opacity);
            SDL_RenderDrawLine(renderer, sim_i + cuadricula , sim_j, sim_i - cuadricula, sim_j);
            // Numeración
            if (pixelsPerUnit > PIXEL_UNIT_VIS && (i - center.x) % (pixelsPerUnit/2)*5 == 0){
                char num_s1[4];
                snprintf(num_s1, sizeof(num_s1), "%d", -(int)((i - center.x) / (pixelsPerUnit/2)));
                EscribirCanvasCentrado(num_s1, i - 15, j - 15, renderer, font_sm, textColor2);
                char num_s2[4];
                snprintf(num_s2, sizeof(num_s2), "%d", (int)((i - center.x) / (pixelsPerUnit/2)));
                EscribirCanvasCentrado(num_s2, sim_i - 15, sim_j - 15, renderer, font_sm, textColor2);
            }
        }
    }
    EscribirCanvasCentrado("+X", 90, windowHeight - 40, renderer, font, textColor);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 127);
    // Y AXIS
    for (int i = 0; i < windowWidth; i++){
        if ((i - center.x) % pixelsPerUnit == 0 && i > center.x){
            int sim_i = 2*center.x - i;
            SDL_RenderDrawLine(renderer, i, center.y + cuadricula, i, center.y - cuadricula);
            SDL_RenderDrawLine(renderer, sim_i, center.y + cuadricula, sim_i, center.y - cuadricula);
            if (pixelsPerUnit > PIXEL_UNIT_VIS && (i - center.x) % pixelsPerUnit*5 == 0){
                char num_s1[4];
                snprintf(num_s1, sizeof(num_s1), "%d", (int)((i - center.x) / pixelsPerUnit));
                EscribirCanvasCentrado(num_s1, i, center.y - 15, renderer, font_sm, textColor2);
                char num_s2[4];
                snprintf(num_s2, sizeof(num_s2), "%d", -(int)((i - center.x) / pixelsPerUnit));
                EscribirCanvasCentrado(num_s2, sim_i, center.y - 15, renderer, font_sm, textColor2);
            }
        }
    }
    EscribirCanvasCentrado("+Y", windowWidth - 35, center.y + 25, renderer, font, textColor);
    // Z AXIS
    for (int k = 0; k < windowHeight; k++){
        if ((k - center.y) % pixelsPerUnit == 0 && k > center.y){
            int sim_k = 2*center.y - k;
            SDL_RenderDrawLine(renderer, center.x + cuadricula, k, center.x - cuadricula, k);
            SDL_RenderDrawLine(renderer, center.x + cuadricula, sim_k, center.x - cuadricula, sim_k);
            if (pixelsPerUnit > PIXEL_UNIT_VIS && (k - center.y) % pixelsPerUnit*5 == 0){
                char num_s1[4];
                snprintf(num_s1, sizeof(num_s1), "%d", -(int)((k - center.y) / pixelsPerUnit));
                EscribirCanvasCentrado(num_s1, center.x - 15, k, renderer, font_sm, textColor2);
                char num_s2[4];
                snprintf(num_s2, sizeof(num_s2), "%d", (int)((k - center.y) / pixelsPerUnit));
                EscribirCanvasCentrado(num_s2, center.x - 15, sim_k, renderer, font_sm, textColor2);
            }
        }
    }
    EscribirCanvasCentrado("+Z", center.x - 35, 25, renderer, font, textColor);

    // SDL_RenderPresent(renderer);
}

void DrawVector (struct Vector vector){
    int fase = (int)(vector.x*(pixelsPerUnit/2));
    int point[2];
    point[0] = (int)((vector.y*pixelsPerUnit) + center.x);
    point[1] = (int)(-(vector.z*pixelsPerUnit) + center.y);

    // Linea Principal
    SDL_SetRenderDrawColor(renderer, vector.color.r, vector.color.g, vector.color.b, vector.color.a);
    SDL_RenderDrawLine(renderer, center.x, center.y, point[0] - fase, point[1] + fase);

    // Guías
    if (vector.x > 0) SDL_SetRenderDrawColor(renderer, vector.color.r, vector.color.g, vector.color.b, 100);
    else SDL_SetRenderDrawColor(renderer, vector.color.r, vector.color.g, vector.color.b, 50);
    
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
    
    SDL_SetRenderDrawColor(renderer, vector.color.r, vector.color.g, vector.color.b, vector.color.a);
    SDL_RenderDrawLines(renderer, points, 4);
}

void DrawVectores (){
    int i = 0;
    while (vectores[i].nombre != NULL){
        DrawVector(vectores[i]);
        i++;
    }
    // SDL_RenderPresent(renderer);
}

void DrawMenu (){
    // Dibujar fondo del menu
    SDL_Rect filledRect = {center.x - 200, center.y - 150, 400, 300};
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &filledRect);
}

