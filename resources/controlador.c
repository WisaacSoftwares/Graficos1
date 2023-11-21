#include "controlador.h"

// #include <stdio.h>
// #include <string.h>
#include "library.h"
#include "ui.h"
#include "vectores.h"
#include "render.h"

char *TITULO = "Menu";

bool InputGeneral (){
    bool termino = false;
    SDL_Event e;

    OPC_SELECCIONADA = 0;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT){
            // Cerrar Programa
            termino = true;
            // CerrarVentana();
            // exit(0);
        } else if (e.type == SDL_MOUSEWHEEL){
            // Manejar el desplazamiento del ratón aquí
            if (e.wheel.x != 0 || e.wheel.y != 0) {
                int scrollDirection = e.wheel.y;
                SDL_Keymod keyModState = SDL_GetModState();
                if (keyModState & KMOD_SHIFT) {
                    // Realizar acciones específicas para el scrolling con Shift
                    if (scrollDirection > 0) CENTER.x+=6;
                    else CENTER.x-=6;
                } else if (keyModState & KMOD_CTRL) {
                    if (scrollDirection > 0 && PIXELES_UNIDAD < PIXEL_UNIT_MAX) PIXELES_UNIDAD = PIXELES_UNIDAD + 2;
                    else if (scrollDirection < 0 && PIXELES_UNIDAD > PIXEL_UNIT_MIN) PIXELES_UNIDAD = PIXELES_UNIDAD - 2;
                }
                else {
                    if (scrollDirection > 0) CENTER.y+=6;
                    else CENTER.y-=6;
                }
            }
        } 
        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
            GenerarMenuPrincipal();
            return false;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym)
            {
                case SDLK_r:
                    CENTER = W_CENTER;
                default:
                    break;
            }
        }
    }

    return termino;
}

void GenerarMenuPrincipal (){
    char *opciones[4] = {
        "Vectores",
        "Operar vectores",
        "Ayuda",
        "Salir"
    };
    int num = DibujarMenu(TITULO, opciones, 4);
    // printf("Selecciono opcion %d: %s\n", num, opciones[num]);
    // fflush(stdout);
    if (num == -1){
        return;
    } else if (num == 0){
        GenerarMenuVectores();
    } else if (num == 1){
        char *opciones2[5] = {
            "Regresar",
            "Suma con vector",
            "Multiplicar por escalar",
            "Producto punto",
            "Producto cruz"
        };
        int opc = 0;
        int vector1, vector2;
        while (opc == 0){
            int vector1 = DibujarMenuVectores("Elije el primer vector", "Regresar", false);

            if (vector1 != -1){
                int opc = DibujarMenuSecundario("Elije la operacion", opciones2, 5);

                while (opc != 0 && opc != -1){
                    if (opc == 2){ // Multiplicar escalar
                        char * resp = ObtenerTexto("Escribe el escalar", 10, NULL, true);
                        if (resp != NULL){
                            // float numero = strtof(resp, NULL);
                            double numero = strtod(resp, NULL);
                            printf("Felicidades vas a hacer la multiplicación escalar entre %s y %s, %s = %0.2f\n", VECTORES[vector1].nombre, resp, resp, numero);
                            fflush(stdout);
                            return;
                        } else {
                            opc = DibujarMenuSecundario("Elije la operacion", opciones2, 5);
                        }
                    } else{
                        vector2 = DibujarMenuVectores("Elije el segundo vector", "Regresar", false);

                        if (vector2 != -1) {
                            printf("Felicidades vas a hacer la operacion %d entre %s y %s\n", opc, VECTORES[vector1].nombre, VECTORES[vector2].nombre);
                            fflush(stdout);
                            return;
                        } else {
                            opc = DibujarMenuSecundario("Elije la operacion", opciones2, 5);
                        }
                    }
                    
                }
            } else opc = -1;
        }
        GenerarMenuPrincipal ();
    } else if (num == 2){
        char * info[] = {
            "Para desplazarte verticalmente usa",
            "la rueda del mouse",
            "Manten presionado CTRL para acercar",
            "y alejar la vista",
            "Manten presionado SHIFT para",
            "desplazarte horizontalmente",
            " ",
            " ",
            " ",
            "Creditos:",
            "Luis Isaac Tavera Zarate",
            "Leonardo Alejandro Roldan Alvarado",
            "Angel Gael Milantoni Perez",
            "Joseph Alfonso Jasso Estrada",
            "Angel Owen Torres Martinez",
            "UNIVERSIDAD DE GUANAJUATO DCI Leon",
            "Noviembre 2023"
        };
        DibujarMuchoTexto("Ayuda", info, 17);
        GenerarMenuPrincipal ();
    } else if (num == 3){
        CerrarVentana();
        exit(0);
    } else {
        GenerarMenuPrincipal ();
    }
}

void GenerarMenuVectores (){
    int vectorID = 0;

    vectorID = DibujarMenuVectores("Vectores", "Regresar", true);

    if (vectorID == -1) {
        GenerarMenuPrincipal();
    } else {
        if (vectorID >= NumeroVectores()) vectorID = CrearVector();
        int propiedad = DibujarMenuVectorPropiedades("Editar vector", "Regresar", vectorID);
        while (propiedad != 0 && propiedad != -1){
            char buffer[10];
            switch (propiedad)
            {
            case 1:
                VECTORES[vectorID].nombre = ObtenerTexto("Cambiar nombre", MAX_LEN, VECTORES[vectorID].nombre, false);
                break;
            case 2:
                sprintf(buffer, "%0.2f", VECTORES[vectorID].x);
                VECTORES[vectorID].x = strtod(ObtenerTexto("Valor de X", 10, buffer, true), NULL);
                break;
            case 3:
                sprintf(buffer, "%0.2f", VECTORES[vectorID].y);
                VECTORES[vectorID].y = strtod(ObtenerTexto("Valor de Y", 10, buffer, true), NULL);
                break;
            case 4:
                sprintf(buffer, "%0.2f", VECTORES[vectorID].z);
                VECTORES[vectorID].z = strtod(ObtenerTexto("Valor de Z", 10, buffer, true), NULL);
                break;
            case 5:
                EliminarVector(vectorID);
                GenerarMenuVectores();
                return;
                break;
            default:
                break;
            }
            propiedad = DibujarMenuVectorPropiedades("Editar vector", "Regresar", vectorID);
        }

        GenerarMenuVectores();
    }
}

