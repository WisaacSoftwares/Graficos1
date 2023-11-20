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
#define VECTOR_MAX 10

bool isRunning = true;
bool mostrarMenu = false;
SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font *font;
TTF_Font * font_sm;
int windowWidth, windowHeight;
SDL_Point middleScreen;
SDL_Point center;
int pixelsPerUnit = 50;
int opcion = 0;
int num_opciones = 3;

char * titulo_m;
char * opciones[VECTOR_MAX + 2];

float flecha_pts[3][2] = {
    {0, 0},
    {-5, 10},
    {5, 10}
};

struct Vector vectores[VECTOR_MAX];
struct Vector vectoresPref[VECTOR_MAX];
struct Vector vectorNulo = {NULL, 0.0f, 0.0f, 0.0f, {0, 0, 0}};
int vector_select = -1;

// Declaración de funciones
void Iniciar();
void CheckInput ();
void Accion ();
void Render();
void DrawIntro (int delay);
void DrawPlano ();
void DrawVector (struct Vector vector);
void DrawVectores ();
void SwitchMenu ();
void DrawMenu (char *titulo, char *opciones[VECTOR_MAX]);
char *TextInput ();
int NumVectores ();
void SetVectoresMenu ();
void SetVectorMenu ();
void SetModificarMenu ();
void CrearVectorAleatorio ();

int main(int argc, char *argv[]) {
    IniciarVentana(&window, &renderer, &windowWidth, &windowHeight, &font);
    SDL_Point _center = {(int)(windowWidth/2), (int)(windowHeight/2)};
    middleScreen = _center;
    center = _center;
    font_sm = TTF_OpenFont("resources/Roboto-Regular.ttf", 16);

    // Intro
    DrawIntro(1000);

    Iniciar();

    // Render();

    // Bucle Principal
    while (isRunning)
    {
        CheckInput();
    }

    // Close Events
    CerrarVentana(window, renderer, font);

    return 0;
}

void Iniciar(){
    titulo_m = "MENU";
    num_opciones = 4;
    opciones[0] = "Vectores";
    opciones[1] = "Hacer operacion";
    opciones[2] = "Ayuda";
    opciones[3] = "Salir";
    opciones[4] = NULL;

    struct Vector vector1 = {"Vector Azul", 1, 2, 1, {0, 0, 255, 255}};
    struct Vector vector2 = {"Vector Amarillo", -2, 1, 1, {255, 255, 0, 255}};
    struct Vector vector3 = {"Vector Rojo", 1, -3, 5, {255, 0, 0, 255}};
    struct Vector vector4 = {"Vector Verde", 1, 1, 1, {66, 170, 66, 255}};
    struct Vector vector5 = {"Vector Naranja", 1, 1, 1, {255, 130, 0, 255}};
    struct Vector vector6 = {"Vector Cyan", 1, 1, 1, {0, 125, 255, 255}};
    struct Vector vector7 = {"Vector Crema", 1, 1, 1, {255, 190, 127, 255}};
    struct Vector vector8 = {"Vector Media Noche", 1, 1, 1, {99, 103, 140, 255}};
    struct Vector vector9 = {"Vector Khaki", 1, 1, 1, {240, 230, 140, 255}};
    struct Vector vector10 = {"Vector Blanco", 1, 1, 1, {255, 255, 255, 255}};
    vectoresPref[0] = vector1;
    vectoresPref[1] = vector2;
    vectoresPref[2] = vector3;
    vectoresPref[3] = vector4;
    vectoresPref[4] = vector5;
    vectoresPref[5] = vector6;
    vectoresPref[6] = vector7;
    vectoresPref[7] = vector8;
    vectoresPref[8] = vector9;
    vectoresPref[9] = vector10;

    vectores[0] = vectoresPref[0];
    vectores[1] = vectoresPref[1];
    vectores[2] = vectoresPref[2];
    vectores[3] = vectorNulo;
}

void CheckInput (){
    SDL_Event event;
    SDL_PollEvent (&event);

    if (event.type == SDL_QUIT){
        isRunning = false;
    }
    else if (event.type == SDL_MOUSEWHEEL && !mostrarMenu){
        // Manejar el desplazamiento del ratón aquí
        if (event.wheel.x != 0 || event.wheel.y != 0) {
            int scrollDirection = event.wheel.y;
            SDL_Keymod keyModState = SDL_GetModState();
            if (keyModState & KMOD_SHIFT) {
                // Realizar acciones específicas para el scrolling con Shift
                if (scrollDirection > 0) center.x+=6;
                else center.x-=6;
            } else if (keyModState & KMOD_CTRL) {
                if (scrollDirection > 0 && pixelsPerUnit < PIXEL_UNIT_MAX && !mostrarMenu) pixelsPerUnit = pixelsPerUnit + 2;
                else if (scrollDirection < 0 && pixelsPerUnit > PIXEL_UNIT_MIN && !mostrarMenu) pixelsPerUnit = pixelsPerUnit - 2;
            }
            else {
                if (scrollDirection > 0) center.y+=6;
                else center.y-=6;
            }
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
                SwitchMenu();
                Render();
                break;
            case SDLK_SPACE:
                // printf("Presionaste espacio!\n");
                Render();
                break;
            case SDLK_m:
                SwitchMenu();
                Render();
                break;
            case SDLK_RIGHT:
                Render();
                break;
            case SDLK_LEFT:
                Render();
                break;
            case SDLK_UP:
                if (mostrarMenu && opcion > 0) opcion--;
                else opcion = num_opciones - 1;
                Render();
                break;
            case SDLK_DOWN:
                if (mostrarMenu && opcion < num_opciones - 1) opcion++;
                else opcion = 0;
                Render();
                break;
            case SDLK_RETURN:
                Accion();
                Render();
                break;
            case SDLK_r:
                if (!mostrarMenu) center = middleScreen;
                Render();
                break;
            default:
                break;
        }
    }
}

void Accion (){
    if (titulo_m == "MENU"){
        switch (opcion)
        {
            case 0:
                SetVectoresMenu();
                break;
            case 3:
                isRunning = false;
                return;
                break;
            default:
                break;
        }
    } else if (titulo_m == "Vectores"){
        if (opcion == 0){
            titulo_m = "MENU";
            num_opciones = 4;
            opciones[0] = "Vectores";
            opciones[1] = "Hacer operacion";
            opciones[2] = "Ayuda";
            opciones[3] = "Salir";
            opciones[4] = NULL;
        } else{
            SetVectorMenu(-1);
        }
    } else if (titulo_m == "Vector"){
        switch (opcion)
        {
            case 0:
                SetVectoresMenu();
                break;
            case 1:
                SetModificarMenu();
                break;
            default:
                // printf("Hola");
                break;
        }
    } else if (titulo_m == "Nuevo Vector"){
        switch (opcion)
        {
            case 0:
                SetVectoresMenu();
                break;
            case 1:
                CrearVectorAleatorio();
                SwitchMenu();
                break;
            default:
                // printf("Hola");
                break;
        }
    } else if (titulo_m == "Modificar"){
        switch (opcion)
        {
            case 0:
                SetVectorMenu(vector_select);
                break;
            case 1:
                // vectores[vector_select].nombre = TextInput();
                break;
            default:
                // printf("Hola");
                break;
        }
    }

    opcion = 0;
}

void Render(){
    // printf("Entra en render\n");
    // fflush(stdout);
    // Plano Cartesiano
    DrawPlano();
    // printf("Finaliza Plano\n");
    // fflush(stdout);

    // Vectores
    DrawVectores();
    // printf("Finaliza Dibujar Vectores\n");
    // fflush(stdout);

    // printf("mostrar Menu: %d\n", mostrarMenu);
    // fflush(stdout);

    // Menu
    if (mostrarMenu) DrawMenu(titulo_m, opciones);
    // printf("Finaliza Mostrar menu\n");
    // fflush(stdout);

    SDL_RenderPresent(renderer);
    // printf("Finaliza Render\n");
    // fflush(stdout);

    fflush(stdout);
}

void DrawIntro (int delay){
    // Background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Dibujar texto blanco en (100, 500)
    SDL_Color textColor = {225, 225, 255, 255};
    char *texto[] = {
        "GRAFICADOR DE VECTORES",
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
    // Opacidad General
    int opacidadCentro = (int)(255.0*pixelsPerUnit/PIXEL_UNIT_MAX);
    // Color Texto
    SDL_Color textColor = {225, 225, 255, 255};
    SDL_Color textColor2 = {225, 225, 255, opacidadCentro};
    SDL_Color textColorX = {225, 225, 255, opacidadCentro};
    // Dibujar Plano Cartesiano
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, opacidadCentro);
    SDL_RenderDrawLine(renderer, center.x, 0, center.x, windowHeight);
    SDL_RenderDrawLine(renderer, 0, center.y, windowWidth, center.y);
    int grilla[] = {
        center.x - 5*pixelsPerUnit,
        center.y + 5*pixelsPerUnit,
        center.x + 5*pixelsPerUnit,
        center.y - 5*pixelsPerUnit
    };
    int grillaH[] = {
        center.x - 10*pixelsPerUnit,
        center.y,
        center.x + 10*pixelsPerUnit,
        center.y
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 15);
    for (int i = 1; i <= 10; i++)
    {
        // printf("%d: %d, %d -> %d, %d\n", i, grilla[0] + (i*pixelsPerUnit), grilla[1], grilla[2] + (i*pixelsPerUnit), grilla[3]);
        SDL_RenderDrawLine(renderer, grilla[0] + (i*pixelsPerUnit), grilla[1], grilla[2] + (i*pixelsPerUnit), grilla[3]);
        SDL_RenderDrawLine(renderer, grilla[0] - (i*pixelsPerUnit), grilla[1], grilla[2] - (i*pixelsPerUnit), grilla[3]);
    }
    for (int i = 1; i <= 10; i++)
    {
        int desface = (int)(i*pixelsPerUnit/2);
        // printf("%d: %d, %d -> %d, %d\n", i, grilla[0] + (i*pixelsPerUnit), grilla[3], grilla[2] + (i*pixelsPerUnit), grilla[1]);
        SDL_RenderDrawLine(renderer, grillaH[0] - desface, grillaH[1] + desface, grillaH[2] - desface, grillaH[3] + desface);
        SDL_RenderDrawLine(renderer, grillaH[0] + desface, grillaH[1] - desface, grillaH[2] + desface, grillaH[3] - desface);
    }

    int cuadricula = (int)(10 * pixelsPerUnit / PIXEL_UNIT_MAX);
    int opacidad;
    // X AXIS
    for (int i = 0; i < windowWidth; i++){
        int x = i - center.x;
        int j = -x + center.y;
        // Efecto Opacidad
        if (abs(i-center.x) < windowWidth/2 && abs(i-center.x) != 0) opacidad = opacidadCentro*(1-abs(i-center.x)*1.0/(windowWidth/2));
        else opacidad = 0;
        // printf("Opacity: %d\t", opacidad);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, opacidad);
        if (opacidad > 0) textColorX.a = opacidad;
        else textColorX.a = 1;
        // Dibujar punto
        if (opacidad != 0) SDL_RenderDrawPoint(renderer, i, j);
        // Cuadricula
        if (opacidad != 0 && (i - center.x) % (pixelsPerUnit/2) == 0){
            SDL_RenderDrawLine(renderer, i + cuadricula , j, i - cuadricula, j);
            // Numeración
            if (pixelsPerUnit > PIXEL_UNIT_VIS && (i - center.x) % (pixelsPerUnit/2)*5 == 0 && i > center.x){
                char num_s[4];
                snprintf(num_s, sizeof(num_s), "%d", -(int)((i - center.x) / (pixelsPerUnit/2))); // -(int)((i - center.x) / (pixelsPerUnit/2))
                
                EscribirCanvasCentrado(num_s, i - 15, j - 15, renderer, font_sm, textColorX);
            }
        }
    }
    for (int i = windowWidth; i >= 0; i--){
        int x = i - center.x;
        int j = -x + center.y;
        // Cuadricula
        if ((i - center.x) % (pixelsPerUnit/2) == 0 && i < center.x){
            // Efecto Opacidad
            if (abs(i-center.x) < windowWidth/2 && abs(i-center.x) != 0) opacidad = opacidadCentro*(1-abs(i-center.x)*1.0/(windowWidth/2));
            else opacidad = 0;
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, opacidad);
            if (opacidad > 0) textColorX.a = opacidad;
            else textColorX.a = 1;
            // Numeración
            if (opacidad != 0 && pixelsPerUnit > PIXEL_UNIT_VIS && (i - center.x) % (pixelsPerUnit/2)*5 == 0){
                char num_s[4];
                snprintf(num_s, sizeof(num_s), "%d", -(int)((i - center.x) / (pixelsPerUnit/2)));
                EscribirCanvasCentrado(num_s, i - 15, j - 15, renderer, font_sm, textColorX);
            }
        }
    }
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, opacidadCentro);
    // Y AXIS
    for (int i = 0; i < windowWidth; i++){
        if ((i - center.x) % pixelsPerUnit == 0 && i > center.x){
            SDL_RenderDrawLine(renderer, i, center.y + cuadricula, i, center.y - cuadricula);
            if (pixelsPerUnit > PIXEL_UNIT_VIS && (i - center.x) % pixelsPerUnit*5 == 0){
                char num_s1[4];
                snprintf(num_s1, sizeof(num_s1), "%d", (int)((i - center.x) / pixelsPerUnit));
                EscribirCanvasCentrado(num_s1, i, center.y - 15, renderer, font_sm, textColor2);
            }
        }
    }
    for (int i = center.x - 1; i > 0; i--){
        if ((i - center.x) % pixelsPerUnit == 0){
            SDL_RenderDrawLine(renderer, i, center.y + cuadricula, i, center.y - cuadricula);
            if (pixelsPerUnit > PIXEL_UNIT_VIS && (i - center.x) % pixelsPerUnit*5 == 0){
                char num_s1[4];
                snprintf(num_s1, sizeof(num_s1), "%d", (int)((i - center.x) / pixelsPerUnit));
                EscribirCanvasCentrado(num_s1, i, center.y - 15, renderer, font_sm, textColor2);
            }
        }
    }
    // Z AXIS
    for (int k = 0; k < windowHeight; k++){
        if ((k - center.y) % pixelsPerUnit == 0 && k > center.y){
            SDL_RenderDrawLine(renderer, center.x + cuadricula, k, center.x - cuadricula, k);
            if (pixelsPerUnit > PIXEL_UNIT_VIS && (k - center.y) % pixelsPerUnit*5 == 0){
                char num_s1[4];
                snprintf(num_s1, sizeof(num_s1), "%d", -(int)((k - center.y) / pixelsPerUnit));
                EscribirCanvasCentrado(num_s1, center.x - 15, k, renderer, font_sm, textColor2);
            }
        }
    }
    for (int k = center.y - 1; k > 0; k--){
        if ((k - center.y) % pixelsPerUnit == 0){
            SDL_RenderDrawLine(renderer, center.x + cuadricula, k, center.x - cuadricula, k);
            if (pixelsPerUnit > PIXEL_UNIT_VIS && (k - center.y) % pixelsPerUnit*5 == 0){
                char num_s1[4];
                snprintf(num_s1, sizeof(num_s1), "%d", -(int)((k - center.y) / pixelsPerUnit));
                EscribirCanvasCentrado(num_s1, center.x - 15, k, renderer, font_sm, textColor2);
            }
        }
    }

    // Textos
    int xLabelPos = center.y+center.x-500;
    if (xLabelPos < center.x) EscribirCanvasCentrado("+X", xLabelPos - 30, windowHeight - 25, renderer, font, textColor);
    EscribirCanvasCentrado("+Y", windowWidth - 35, center.y + 25, renderer, font, textColor);
    EscribirCanvasCentrado("+Z", center.x - 35, 25, renderer, font, textColor);
    EscribirCanvas("Graficador", 10, 5, renderer, font, textColor);
    // SDL_RenderPresent(renderer);
}

void DrawVector (struct Vector vector){
    int fase = (int)(vector.x*(pixelsPerUnit/2));
    int point[2];
    point[0] = (int)((vector.y*pixelsPerUnit) + center.x);
    point[1] = (int)(-(vector.z*pixelsPerUnit) + center.y);

    // Guías
    SDL_SetRenderDrawColor(renderer, vector.color.r, vector.color.g, vector.color.b, 100);
    
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
    
    // Linea Principal
    SDL_SetRenderDrawColor(renderer, vector.color.r, vector.color.g, vector.color.b, vector.color.a);
    SDL_RenderDrawLine(renderer, center.x, center.y, point[0] - fase, point[1] + fase);
    // Flecha
    SDL_SetRenderDrawColor(renderer, vector.color.r, vector.color.g, vector.color.b, vector.color.a);
    SDL_RenderDrawLines(renderer, points, 4);
    
}

void DrawVectores (){
    for (int i = 0; i < NumVectores(); i++)
    {
        DrawVector(vectores[i]);
    }
    // SDL_RenderPresent(renderer);
}

void SwitchMenu (){
    if (mostrarMenu) mostrarMenu = false;
    else {
        titulo_m = "MENU";
        num_opciones = 4;
        opciones[0] = "Vectores";
        opciones[1] = "Hacer operacion";
        opciones[2] = "Ayuda";
        opciones[3] = "Salir";
        opciones[4] = NULL;

        mostrarMenu = true;
        opcion = 0;
    }
}

void DrawMenu (char *titulo, char *opc[VECTOR_MAX]){
    // printf("Entra en menu\n");
    // fflush(stdout);

    // Dibujar fondo del menu
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_Rect filledRect = {middleScreen.x - 200, middleScreen.y - 250, 400, 500};
    SDL_RenderFillRect(renderer, &filledRect);

    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Color textColor_Sel = {255, 255, 255, 255};
    SDL_Color bkColor = {168, 168, 168, 255};
    SDL_Color bkColor_Sel = {255, 132, 0, 255};

    // printf("Entra condicional menu\n");
    // fflush(stdout);
    
    if (titulo_m == "Vector" && vector_select > -1 && vector_select < NumVectores()) {
        titulo = vectores[vector_select].nombre;
    }

    // printf("Finaliza condicional menu, title %s\n", titulo);
    // fflush(stdout);

    // Title
    EscribirCanvasCentrado(titulo, middleScreen.x, middleScreen.y - 220, renderer, font, textColor);
    // Opciones
    SDL_SetRenderDrawColor(renderer, bkColor.r, bkColor.g, bkColor.b, bkColor.a);

    // printf("Finaliza titulo\n");
    // fflush(stdout);

    int salto = 30 + 6;
    // int yStart = middleScreen.y - (int)(salto*num_opciones*1.0/2);
    int yStart = middleScreen.y - 190;

    // printf("Inicia opciones, #opc: %d\n", num_opciones);
    // fflush(stdout);

    for (int i = 0; i < num_opciones; i++)
    {
        // printf("i: %d, opc: %s", i, opc[i]);
        // fflush(stdout);
        if (i == opcion) SDL_SetRenderDrawColor(renderer, bkColor_Sel.r, bkColor_Sel.g, bkColor_Sel.b, bkColor_Sel.a);
        else SDL_SetRenderDrawColor(renderer, bkColor.r, bkColor.g, bkColor.b, bkColor.a);

        SDL_Rect filledRect1 = {middleScreen.x - 150, yStart + i*salto, 300, 30};
        SDL_RenderFillRect(renderer, &filledRect1);

        if (i == opcion) EscribirCanvasCentrado(opc[i], middleScreen.x, yStart + i*salto + 12, renderer, font, textColor_Sel);
        else EscribirCanvasCentrado(opc[i], middleScreen.x, yStart + i*salto + 12, renderer, font, textColor);
        // printf("fin i: %d\n", i);
    }

    // printf("Finaliza Menu\n");
    // fflush(stdout);
}

char *TextInput (){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("TextInput", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    SDL_StartTextInput();

    SDL_Color textColor = {0, 0, 0, 255};

    char input[100] = "";
    int index = 0;

    SDL_Event e;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_TEXTINPUT) {
                if (index < 100 - 1) {
                    input[index] = e.text.text[0];
                    index++;
                    input[index] = '\0';
                    printf("Texto ingresado: %s\n", input);
                }
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RETURN) {
                    printf("Texto ingresado: %s\n", input);
                    index = 0;
                    input[0] = '\0';
                } else if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = 1;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_Surface* surface = TTF_RenderText_Solid(font, input, textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        SDL_Rect textRect = {10, 10, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &textRect);

        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    // Devolver una copia de la cadena (nueva memoria asignada)
    return strdup(input);

    // SDL_StartTextInput();

    // bool termino = false;
    // char input[100];
    // int index = 0;
    // SDL_Event event;

    // while (!termino){
    //     if (event.type == SDL_TEXTINPUT){
    //         // Leer lo que escribe
    //         if (index < sizeof(input) - 1){
    //             input[index] = event.text.text[0];
    //             index++;
    //             input[index] = '\0'; //Cerrar cadena
    //         }
    //     } else if (event.type == SDL_KEYDOWN){
    //         switch (event.key.keysym.sym)
    //         {
    //             case SDLK_ESCAPE:
    //                 termino = true;
    //                 isRunning = true;
    //                 break;
    //             case SDLK_RETURN:
    //                 printf("Texto ingresado: %s\n", input);
    //                 input[0] = '\0';
    //                 index = 0;
    //                 termino = true;
    //                 SDL_StopTextInput();
    //                 break;
    //             default:
    //                 break;
    //         }
    //     }

    //     // Dibujar fondo del menu
    //     SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //     SDL_Rect filledRect = {middleScreen.x - 125, middleScreen.y - 20, 250, 40};
    //     SDL_RenderFillRect(renderer, &filledRect);

    //     // Dibujar la cadena actual en la ventana (opcional)
    //     SDL_Color textColor = {0, 0, 0, 255};
    //     EscribirCanvasCentrado(input, middleScreen.x, middleScreen.y, renderer, font, textColor);

    //     printf("Texto ingresado: %s\n", input);
    //     fflush(stdout);

    //     SDL_RenderPresent(renderer);
    // }
    // char * result;
    // strcpy(result, input);
    // return result;
}

int NumVectores (){
    int i = 0;
    for (i; i < VECTOR_MAX; i++)
    {
        if (vectores[i].nombre == NULL) return i;
    }
    
    return i;
}

void SetVectoresMenu (){
    titulo_m = "Vectores";
    opciones[0] = "Regresar";

    // printf("#Vectores: %d\n", NumVectores());
    // fflush(stdout);

    if (NumVectores() < 10){
        num_opciones = NumVectores() + 2;
    } else{
        num_opciones = NumVectores() + 1;
    }
    for (int i = 0; i < num_opciones; i++)
    {
        opciones[i+1] = vectores[i].nombre;
        // printf("i: %d, # Opc: %d\n", i, num_opciones);
        // fflush(stdout);
    }
    if (NumVectores() < 10) opciones[num_opciones-1] = "Nuevo";
    // printf("Finaliza SetVectores\n");
    // fflush(stdout);
}

void SetVectorMenu (int _vector){
    if (_vector != -1) opcion = _vector + 1;

    if (opcion > 0 && opcion <= NumVectores()){
        vector_select = opcion - 1;

        titulo_m = "Vector";
        num_opciones = 4;
        opciones[0] = "Regresar";
        opciones[1] = "Modificar";
        opciones[2] = "Duplicar";
        opciones[3] = "Borrar";
        opciones[4] = NULL;
    }
    else {
        vector_select = -1;
        titulo_m = "Nuevo Vector";
        num_opciones = 3;
        opciones[0] = "Regresar";
        opciones[1] = "Generar aleatorio";
        opciones[2] = "Definir datos";
        opciones[3] = NULL;
    }
}

void SetModificarMenu (){
    titulo_m = "Modificar";
    num_opciones = 4;
    opciones[0] = "Regresar";
    opciones[1] = "Nombre";
    opciones[2] = "x, y, z";
    opciones[3] = "Color";
    opciones[4] = NULL;
}

void CrearVectorAleatorio(){
    // printf("Inicia Crear VectorA\n");
    // fflush(stdout);
    vectores[NumVectores()] = vectoresPref[NumVectores()];
    // printf("NumVect: %d\n", NumVectores());
    // fflush(stdout);
    if (NumVectores() < VECTOR_MAX - 1) vectores[NumVectores() + 1] = vectorNulo;
    // printf("Finaliza Crear VectorA\n");
    // fflush(stdout);
}

