#include "ui.h"
#include "ui.h"

#include <ctype.h>
#include <stdlib.h>

#include "library.h"
#include "render.h"
#include "vectores.h"


int OPC_SELECCIONADA = 0;

bool TieneEsteCaracter (char * texto, char caracter, int longitudTexto) {
    for (int i = 0; i < longitudTexto; i++)
    {
        if (texto[i] == caracter) return true;
    }
    return false;
}

char* ObtenerTexto(char * titulo, int numChar, char * texto, bool soloNumeros){
    bool termino = false;
    SDL_Event e;
    char *input = malloc(numChar);
    memset(input, 0, numChar);
    input[0] = ' ';

    int inputLen = 0;

    if (texto != NULL) {
        // for (int i = 0; i < inputLen; i++)
        //     input[i] = texto[i];
        strcpy(input, texto);
        inputLen = strlen(input);
    }
    
    int StartPosY = W_CENTER.y - 75;
    int EndPosY = W_CENTER.y + 75;

    SDL_StartTextInput();

    while (!termino)
    {
        // fondo
        SetRenderDrawColor(COLOR_GRIS_OSCURO);
        SDL_RenderClear(RENDERER);
        // Ventana
        SetRenderDrawColor(COLOR_GRIS_CLARO);
        RenderRect(W_CENTER.x - 210, StartPosY, 420, 150, true);
        SetRenderDrawColor(COLOR_GRIS);
        RenderRect(W_CENTER.x - 210, StartPosY, 420, 150, false);
        // Titulo
        EscribirTextoCentrado(titulo, W_CENTER.x, StartPosY + 30, FONT_BOLD, COLOR_NEGRO, false);
        // Text Input
        SetRenderDrawColor(COLOR_BLANCO);
        RenderRect(W_CENTER.x - (int)(numChar*13/2), W_CENTER.y - 15, numChar*13, 30, true);
        SetRenderDrawColor(COLOR_GRIS);
        RenderRect(W_CENTER.x - (int)(numChar*13/2), W_CENTER.y - 15, numChar*13, 30, false);
        EscribirTextoCentrado(input, W_CENTER.x, W_CENTER.y, FONT_MAIN, COLOR_NEGRO, false);
        // Hint
        EscribirTextoCentrado("Presiona ENTER para guardar", W_CENTER.x, EndPosY - 30, FONT_SMALL, COLOR_GRIS_OSCURO, false);
        SDL_RenderPresent(RENDERER);
        // SDL_RenderClear(RENDERER);

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT){
                // Cerrar Programa
                CerrarVentana();
                exit(0);
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                input = NULL;
                termino = true;
            } else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    if (inputLen > 1) input[--inputLen] = '\0';
                    else {
                        input[0] = ' ';
                        inputLen = 0;
                    }
                } else if (e.key.keysym.sym == SDLK_RETURN || e.key.keysym.sym == SDLK_KP_ENTER) {
                    if (inputLen == 0) input = NULL;
                    termino = true;
                }
            } else if (e.type == SDL_TEXTINPUT && inputLen < numChar) {
                if (soloNumeros){
                    // Verifica cada carácter de la cadena de entrada
                    for (int i = 0; e.text.text[i] != '\0'; ++i) {
                        // Permite solo caracteres numéricos
                        if (isdigit(e.text.text[i]) || e.text.text[i] == '.' && !TieneEsteCaracter(input, '.', inputLen) ||
                        e.text.text[i] == '-' && inputLen == 0) {
                            // Agrega el carácter a la cadena de entrada si es numérico
                            if (input[0] == ' ' && inputLen == 0) input[0] = '\0';
                            strncat(input, &e.text.text[i], 1);
                            inputLen++;
                            input[inputLen] = '\0';
                        }
                    }
                } else {
                    strcpy(input + inputLen, e.text.text);
                    inputLen += strlen(e.text.text);
                    input[inputLen] = '\0';
                }
            }
        }
    }
    SDL_StopTextInput();

    return input;
}

int DibujarMenu(char * titulo, char **opciones, int numOpciones){
    bool termino = false;
    SDL_Event e;
    SDL_Point ventanaInicia = {W_CENTER.x - (int)(MENU_WIDTH/2), W_CENTER.y - (int)(MENU_HEIGHT/2)};
    SDL_Point ventanaTermina = {W_CENTER.x + (int)(MENU_WIDTH/2), W_CENTER.y + (int)(MENU_HEIGHT/2)};
    SDL_Point areaInicia = {ventanaInicia.x + 20, ventanaInicia.y + 40};
    SDL_Point areaTermina = {ventanaTermina.x - 20, ventanaTermina.y - 40};

    OPC_SELECCIONADA = 0;
    while (!termino) {
        // fondo
        SetRenderDrawColor(COLOR_GRIS_OSCURO);
        SDL_RenderClear(RENDERER);
        // Ventana
        SetRenderDrawColor(COLOR_GRIS_CLARO);
        RenderRect(ventanaInicia.x, ventanaInicia.y, MENU_WIDTH, MENU_HEIGHT, true);
        SetRenderDrawColor(COLOR_GRIS);
        RenderRect(ventanaInicia.x, ventanaInicia.y, MENU_WIDTH, MENU_HEIGHT, false);
        // Opciones
        for (int i = 0; i < numOpciones; i++)
        {
            if (i == OPC_SELECCIONADA) {
                SetRenderDrawColor(COLOR_AZUL);
                RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*i, areaTermina.x - areaInicia.x, MENU_CONTROL_H, true);

                EscribirTextoCentrado(opciones[i], W_CENTER.x , areaInicia.y + MENU_CONTROL_H*i + 15, FONT_MAIN, COLOR_BLANCO, false);
            }
            else {
                SetRenderDrawColor(COLOR_GRIS_CLARO);
                RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*i, areaTermina.x - areaInicia.x, MENU_CONTROL_H, true);

                EscribirTextoCentrado(opciones[i], W_CENTER.x , areaInicia.y + MENU_CONTROL_H*i + 15, FONT_MAIN, COLOR_NEGRO, false);
            }
            SetRenderDrawColor(COLOR_GRIS_OSCURO);
            RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*i, areaTermina.x - areaInicia.x, MENU_CONTROL_H, false);
        }
        // Titulo
        EscribirTextoCentrado(titulo, W_CENTER.x, ventanaInicia.y + 20, FONT_BOLD, COLOR_NEGRO, false);
        // Hint
        EscribirTextoCentrado("Selecciona una opcion y presiona ENTER", W_CENTER.x, ventanaTermina.y - 20, FONT_SMALL, COLOR_GRIS_OSCURO, false);

        SDL_RenderPresent(RENDERER);
        // SDL_RenderClear(RENDERER);

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT){
                // Cerrar Programa
                CerrarVentana();
                exit(0);
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                termino = true;
                return -1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym)
                {
                    case SDLK_UP:
                        if (OPC_SELECCIONADA > 0) OPC_SELECCIONADA--;
                        else OPC_SELECCIONADA = numOpciones - 1;
                        break;
                    case SDLK_DOWN:
                        if (OPC_SELECCIONADA < numOpciones - 1) OPC_SELECCIONADA++;
                        else OPC_SELECCIONADA = 0;
                        break;
                    case SDLK_KP_ENTER:
                    case SDLK_RETURN:
                        return OPC_SELECCIONADA;
                        break;
                    default:
                        break;
                }
            }
        }
    }
    // Retornar opc seleccionada
    return 0;
}

int DibujarMenuVectores(char * titulo, char *primerOpcion, bool mostrarNuevo){
    bool termino = false;
    SDL_Event e;
    SDL_Point ventanaInicia = {W_CENTER.x - (int)(MENU_WIDTH/2), W_CENTER.y - (int)(MENU_HEIGHT/2)};
    SDL_Point ventanaTermina = {W_CENTER.x + (int)(MENU_WIDTH/2), W_CENTER.y + (int)(MENU_HEIGHT/2)};
    SDL_Point areaInicia = {ventanaInicia.x + 20, ventanaInicia.y + 40};
    SDL_Point areaTermina = {ventanaTermina.x - 20, ventanaTermina.y - 40};

    int numOpciones;
    
    OPC_SELECCIONADA = 0;
    while (!termino) {

        // fondo
        SetRenderDrawColor(COLOR_GRIS_OSCURO);
        SDL_RenderClear(RENDERER);
        // Ventana
        SetRenderDrawColor(COLOR_GRIS_CLARO);
        RenderRect(ventanaInicia.x, ventanaInicia.y, MENU_WIDTH, MENU_HEIGHT, true);
        SetRenderDrawColor(COLOR_GRIS);
        RenderRect(ventanaInicia.x, ventanaInicia.y, MENU_WIDTH, MENU_HEIGHT, false);
        // Work area START
        SetRenderDrawColor(COLOR_BLANCO);
        RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*2, areaTermina.x - areaInicia.x, areaTermina.y - (areaInicia.y + MENU_CONTROL_H*2), true);
        // Opcion 1 - Regresar
        if (OPC_SELECCIONADA == 0) {
            SetRenderDrawColor(COLOR_AZUL);
            RenderRect(areaInicia.x, areaInicia.y, areaTermina.x - areaInicia.x, MENU_CONTROL_H, true);
            EscribirTextoCentrado(primerOpcion, W_CENTER.x , areaInicia.y + 15, FONT_MAIN, COLOR_BLANCO, false);
        }
        else {
            SetRenderDrawColor(COLOR_GRIS_CLARO);
            RenderRect(areaInicia.x, areaInicia.y, areaTermina.x - areaInicia.x, MENU_CONTROL_H, true);
            EscribirTextoCentrado(primerOpcion, W_CENTER.x , areaInicia.y + 15, FONT_MAIN, COLOR_NEGRO, false);
        }
        SetRenderDrawColor(COLOR_GRIS_OSCURO);
        RenderRect(areaInicia.x, areaInicia.y, areaTermina.x - areaInicia.x, MENU_CONTROL_H, false);
        // areaInicia.y = ventanaInicia.y + 40 + MENU_CONTROL_H;
        // Vectores
        
        if (!mostrarNuevo && NumeroVectores() < VECTORES_MAX || NumeroVectores() == VECTORES_MAX) numOpciones = NumeroVectores() + 1;
        else numOpciones = NumeroVectores() + 2;

        for (int i = 0; i < NumeroVectores(); i++)
        {
            int posicion = i+2;
            if (i + 1 == OPC_SELECCIONADA) {
                SetRenderDrawColor(COLOR_AZUL);
                RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*posicion, areaTermina.x - areaInicia.x, MENU_CONTROL_H, true);

                EscribirTexto(VECTORES[i].nombre, areaInicia.x + 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_BLANCO, false);
            }
            else {
                EscribirTexto(VECTORES[i].nombre, areaInicia.x + 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_NEGRO, false);
            }
            SetRenderDrawColor(VECTORES[i].color);
            RenderRect(areaTermina.x - 30, areaInicia.y + MENU_CONTROL_H*posicion + 5, 20, 20, true);
            SetRenderDrawColor(COLOR_NEGRO);
            RenderRect(areaTermina.x - 30, areaInicia.y + MENU_CONTROL_H*posicion + 5, 20, 20, false);
        }
        // Nuevo Vector
        if (NumeroVectores() < VECTORES_MAX && mostrarNuevo){
            if (numOpciones - 1 == OPC_SELECCIONADA) {
                SetRenderDrawColor(COLOR_AZUL);
                RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*numOpciones, areaTermina.x - areaInicia.x, MENU_CONTROL_H, true);

                EscribirTexto("Nuevo vector", areaInicia.x + 10 , areaInicia.y + MENU_CONTROL_H*numOpciones + 5, FONT_MAIN, COLOR_BLANCO, false);
            }
            else {
                EscribirTexto("Nuevo vector", areaInicia.x + 10 , areaInicia.y + MENU_CONTROL_H*numOpciones + 5, FONT_MAIN, COLOR_NEGRO, false);
            }
            SetRenderDrawColor(COLOR_BLANCO);
            RenderRect(areaTermina.x - 30, areaInicia.y + MENU_CONTROL_H*numOpciones + 5, 20, 20, true);
            SetRenderDrawColor(COLOR_NEGRO);
            RenderRect(areaTermina.x - 30, areaInicia.y + MENU_CONTROL_H*numOpciones + 5, 20, 20, false);
        }
    
        // Work area END
        SetRenderDrawColor(COLOR_GRIS);
        RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*2, areaTermina.x - areaInicia.x, areaTermina.y - (areaInicia.y + MENU_CONTROL_H*2), false);
        // Titulo
        EscribirTextoCentrado(titulo, W_CENTER.x, ventanaInicia.y + 20, FONT_BOLD, COLOR_NEGRO, false);
        // Hint
        EscribirTextoCentrado("Selecciona una opcion y presiona ENTER", W_CENTER.x, ventanaTermina.y - 20, FONT_SMALL, COLOR_GRIS_OSCURO, false);

        SDL_RenderPresent(RENDERER);
        // SDL_RenderClear(RENDERER);

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT){
                // Cerrar Programa
                CerrarVentana();
                exit(0);
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                termino = true;
                return -1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym)
                {
                    case SDLK_UP:
                        if (OPC_SELECCIONADA > 0) OPC_SELECCIONADA--;
                        else OPC_SELECCIONADA = numOpciones - 1;
                        break;
                    case SDLK_DOWN:
                        if (OPC_SELECCIONADA < numOpciones - 1) OPC_SELECCIONADA++;
                        else OPC_SELECCIONADA = 0;
                        break;
                    case SDLK_KP_ENTER:
                    case SDLK_RETURN:
                        return OPC_SELECCIONADA - 1;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    // Retornar opc seleccionada
    return 0;
}

int DibujarMenuSecundario(char * titulo, char **opciones, int numOpciones){
    bool termino = false;
    SDL_Event e;
    SDL_Point ventanaInicia = {W_CENTER.x - (int)(MENU_WIDTH/2), W_CENTER.y - (int)(MENU_HEIGHT/2)};
    SDL_Point ventanaTermina = {W_CENTER.x + (int)(MENU_WIDTH/2), W_CENTER.y + (int)(MENU_HEIGHT/2)};
    SDL_Point areaInicia = {ventanaInicia.x + 20, ventanaInicia.y + 40};
    SDL_Point areaTermina = {ventanaTermina.x - 20, ventanaTermina.y - 40};

    OPC_SELECCIONADA = 0;
    while (!termino) {
        // fondo
        SetRenderDrawColor(COLOR_GRIS_OSCURO);
        SDL_RenderClear(RENDERER);
        // Ventana
        SetRenderDrawColor(COLOR_GRIS_CLARO);
        RenderRect(ventanaInicia.x, ventanaInicia.y, MENU_WIDTH, MENU_HEIGHT, true);
        SetRenderDrawColor(COLOR_GRIS);
        RenderRect(ventanaInicia.x, ventanaInicia.y, MENU_WIDTH, MENU_HEIGHT, false);
        // Work area START
        SetRenderDrawColor(COLOR_BLANCO);
        RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*2, areaTermina.x - areaInicia.x, areaTermina.y - (areaInicia.y + MENU_CONTROL_H*2), true);
        // Opcion 1 - Regresar
        if (OPC_SELECCIONADA == 0) {
            SetRenderDrawColor(COLOR_AZUL);
            RenderRect(areaInicia.x, areaInicia.y, areaTermina.x - areaInicia.x, MENU_CONTROL_H, true);
            EscribirTextoCentrado(opciones[0], W_CENTER.x , areaInicia.y + 15, FONT_MAIN, COLOR_BLANCO, false);
        }
        else {
            SetRenderDrawColor(COLOR_GRIS_CLARO);
            RenderRect(areaInicia.x, areaInicia.y, areaTermina.x - areaInicia.x, MENU_CONTROL_H, true);
            EscribirTextoCentrado(opciones[0], W_CENTER.x , areaInicia.y + 15, FONT_MAIN, COLOR_NEGRO, false);
        }
        SetRenderDrawColor(COLOR_GRIS_OSCURO);
        RenderRect(areaInicia.x, areaInicia.y, areaTermina.x - areaInicia.x, MENU_CONTROL_H, false);
        // Opciones
        for (int i = 1; i < numOpciones; i++)
        {
            int posicion = i+1;
            if (i == OPC_SELECCIONADA) {
                SetRenderDrawColor(COLOR_AZUL);
                RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*posicion, areaTermina.x - areaInicia.x, MENU_CONTROL_H, true);

                EscribirTexto(opciones[i], areaInicia.x + 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_BLANCO, false);
            }
            else {
                EscribirTexto(opciones[i], areaInicia.x + 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_NEGRO, false);
            }
        }
        // Work area END
        SetRenderDrawColor(COLOR_GRIS);
        RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*2, areaTermina.x - areaInicia.x, areaTermina.y - (areaInicia.y + MENU_CONTROL_H*2), false);
        // Titulo
        EscribirTextoCentrado(titulo, W_CENTER.x, ventanaInicia.y + 20, FONT_BOLD, COLOR_NEGRO, false);
        // Hint
        EscribirTextoCentrado("Selecciona una opcion y presiona ENTER", W_CENTER.x, ventanaTermina.y - 20, FONT_SMALL, COLOR_GRIS_OSCURO, false);

        SDL_RenderPresent(RENDERER);
        // SDL_RenderClear(RENDERER);

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT){
                // Cerrar Programa
                CerrarVentana();
                exit(0);
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                termino = true;
                return -1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym)
                {
                    case SDLK_UP:
                        if (OPC_SELECCIONADA > 0) OPC_SELECCIONADA--;
                        else OPC_SELECCIONADA = numOpciones - 1;
                        break;
                    case SDLK_DOWN:
                        if (OPC_SELECCIONADA < numOpciones - 1) OPC_SELECCIONADA++;
                        else OPC_SELECCIONADA = 0;
                        break;
                    case SDLK_KP_ENTER:
                    case SDLK_RETURN:
                        return OPC_SELECCIONADA;
                        break;
                    default:
                        break;
                }
            }
        }
    }
    // Retornar opc seleccionada
    return 0;
}

int DibujarMenuVectorPropiedades(char * titulo, char *primerOpcion, int idVector){
    bool termino = false;
    SDL_Event e;
    SDL_Point ventanaInicia = {W_CENTER.x - (int)(MENU_WIDTH/2), W_CENTER.y - (int)(MENU_HEIGHT/2)};
    SDL_Point ventanaTermina = {W_CENTER.x + (int)(MENU_WIDTH/2), W_CENTER.y + (int)(MENU_HEIGHT/2)};
    SDL_Point areaInicia = {ventanaInicia.x + 20, ventanaInicia.y + 40};
    SDL_Point areaTermina = {ventanaTermina.x - 20, ventanaTermina.y - 40};
    int numOpciones = 6;

    OPC_SELECCIONADA = 0;
    while (!termino) {
        // fondo
        SetRenderDrawColor(COLOR_GRIS_OSCURO);
        SDL_RenderClear(RENDERER);
        // Ventana
        SetRenderDrawColor(COLOR_GRIS_CLARO);
        RenderRect(ventanaInicia.x, ventanaInicia.y, MENU_WIDTH, MENU_HEIGHT, true);
        SetRenderDrawColor(COLOR_GRIS);
        RenderRect(ventanaInicia.x, ventanaInicia.y, MENU_WIDTH, MENU_HEIGHT, false);
        // Work area START
        SetRenderDrawColor(COLOR_BLANCO);
        RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*2, areaTermina.x - areaInicia.x, areaTermina.y - (areaInicia.y + MENU_CONTROL_H*2), true);
        // Opcion 1 - Regresar
        if (OPC_SELECCIONADA == 0) {
            SetRenderDrawColor(COLOR_AZUL);
            RenderRect(areaInicia.x, areaInicia.y, areaTermina.x - areaInicia.x, MENU_CONTROL_H, true);
            EscribirTextoCentrado(primerOpcion, W_CENTER.x , areaInicia.y + 15, FONT_MAIN, COLOR_BLANCO, false);
        }
        else {
            SetRenderDrawColor(COLOR_GRIS_CLARO);
            RenderRect(areaInicia.x, areaInicia.y, areaTermina.x - areaInicia.x, MENU_CONTROL_H, true);
            EscribirTextoCentrado(primerOpcion, W_CENTER.x , areaInicia.y + 15, FONT_MAIN, COLOR_NEGRO, false);
        }
        SetRenderDrawColor(COLOR_GRIS_OSCURO);
        RenderRect(areaInicia.x, areaInicia.y, areaTermina.x - areaInicia.x, MENU_CONTROL_H, false);
        // Opciones
        SetRenderDrawColor(VECTORES[idVector].color); // Color
        RenderRect(areaInicia.x + 10, areaInicia.y + MENU_CONTROL_H*2 + 10, areaTermina.x - areaInicia.x - 20, MENU_CONTROL_H - 20, true);
        SetRenderDrawColor(COLOR_NEGRO);
        RenderRect(areaInicia.x + 10, areaInicia.y + MENU_CONTROL_H*2 + 10, areaTermina.x - areaInicia.x - 20, MENU_CONTROL_H - 20, false);
        // Nombre
        int posicion = 3;
        if (OPC_SELECCIONADA == 1) {
            SetRenderDrawColor(COLOR_AZUL);
            RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*posicion, areaTermina.x - areaInicia.x, MENU_CONTROL_H, true);
            EscribirTexto("Nombre", areaInicia.x + 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_BLANCO, false);
            EscribirTextoDerecha(VECTORES[idVector].nombre, areaTermina.x - 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_BLANCO, false);
        }
        else {
            EscribirTexto("Nombre", areaInicia.x + 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_NEGRO, false);
            EscribirTextoDerecha(VECTORES[idVector].nombre, areaTermina.x - 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_NEGRO, false);
        }
        posicion = 4;
        char buffer[10];
        sprintf(buffer, "%0.2f", VECTORES[idVector].x);
        if (OPC_SELECCIONADA == 2) {
            SetRenderDrawColor(COLOR_AZUL);
            RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*posicion, areaTermina.x - areaInicia.x, MENU_CONTROL_H, true);
            EscribirTexto("X", areaInicia.x + 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_BLANCO, false);
            EscribirTextoDerecha(buffer, areaTermina.x - 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_BLANCO, false);
        }
        else {
            EscribirTexto("X", areaInicia.x + 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_NEGRO, false);
            EscribirTextoDerecha(buffer, areaTermina.x - 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_NEGRO, false);
        }
        posicion = 5;
        sprintf(buffer, "%0.2f", VECTORES[idVector].y);
        if (OPC_SELECCIONADA == 3) {
            SetRenderDrawColor(COLOR_AZUL);
            RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*posicion, areaTermina.x - areaInicia.x, MENU_CONTROL_H, true);
            EscribirTexto("Y", areaInicia.x + 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_BLANCO, false);
            EscribirTextoDerecha(buffer, areaTermina.x - 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_BLANCO, false);
        }
        else {
            EscribirTexto("Y", areaInicia.x + 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_NEGRO, false);
            EscribirTextoDerecha(buffer, areaTermina.x - 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_NEGRO, false);
        }
        posicion = 6;
        sprintf(buffer, "%0.2f", VECTORES[idVector].z);
        if (OPC_SELECCIONADA == 4) {
            SetRenderDrawColor(COLOR_AZUL);
            RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*posicion, areaTermina.x - areaInicia.x, MENU_CONTROL_H, true);
            EscribirTexto("Z", areaInicia.x + 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_BLANCO, false);
            EscribirTextoDerecha(buffer, areaTermina.x - 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_BLANCO, false);
        }
        else {
            EscribirTexto("Z", areaInicia.x + 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_NEGRO, false);
            EscribirTextoDerecha(buffer, areaTermina.x - 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_NEGRO, false);
        }
        posicion = 7;
        sprintf(buffer, "%0.2f", VECTORES[idVector].z);
        if (OPC_SELECCIONADA == 5) {
            SetRenderDrawColor(COLOR_ROJO);
            RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*posicion, areaTermina.x - areaInicia.x, MENU_CONTROL_H, true);
            EscribirTexto("Eliminar Vector", areaInicia.x + 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_BLANCO, false);
        }
        else {
            EscribirTexto("Eliminar Vector", areaInicia.x + 10 , areaInicia.y + MENU_CONTROL_H*posicion + 5, FONT_MAIN, COLOR_NEGRO, false);
        }
        
        // Work area END
        SetRenderDrawColor(COLOR_GRIS);
        RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*2, areaTermina.x - areaInicia.x, areaTermina.y - (areaInicia.y + MENU_CONTROL_H*2), false);
        // Titulo
        EscribirTextoCentrado(titulo, W_CENTER.x, ventanaInicia.y + 20, FONT_BOLD, COLOR_NEGRO, false);
        // Hint
        EscribirTextoCentrado("Selecciona una opcion y presiona ENTER", W_CENTER.x, ventanaTermina.y - 20, FONT_SMALL, COLOR_GRIS_OSCURO, false);

        SDL_RenderPresent(RENDERER);
        // SDL_RenderClear(RENDERER);

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT){
                // Cerrar Programa
                CerrarVentana();
                exit(0);
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                termino = true;
                return -1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym)
                {
                    case SDLK_UP:
                        if (OPC_SELECCIONADA > 0) OPC_SELECCIONADA--;
                        else OPC_SELECCIONADA = numOpciones - 1;
                        break;
                    case SDLK_DOWN:
                        if (OPC_SELECCIONADA < numOpciones - 1) OPC_SELECCIONADA++;
                        else OPC_SELECCIONADA = 0;
                        break;
                    case SDLK_KP_ENTER:
                    case SDLK_RETURN:
                        return OPC_SELECCIONADA;
                        break;
                    default:
                        break;
                }
            }
        }
    }
    // Retornar opc seleccionada
    return 0;
}

void DibujarMuchoTexto(char * titulo, char **texto, int numFilas){
    bool termino = false;
    SDL_Event e;
    SDL_Point ventanaInicia = {W_CENTER.x - (int)(MENU_WIDTH/2), W_CENTER.y - (int)(MENU_HEIGHT/2)};
    SDL_Point ventanaTermina = {W_CENTER.x + (int)(MENU_WIDTH/2), W_CENTER.y + (int)(MENU_HEIGHT/2)};
    SDL_Point areaInicia = {ventanaInicia.x + 20, ventanaInicia.y + 40};
    SDL_Point areaTermina = {ventanaTermina.x - 20, ventanaTermina.y - 40};

    // fondo
    SetRenderDrawColor(COLOR_GRIS_OSCURO);
    SDL_RenderClear(RENDERER);
    // Ventana
    SetRenderDrawColor(COLOR_GRIS_CLARO);
    RenderRect(ventanaInicia.x, ventanaInicia.y, MENU_WIDTH, MENU_HEIGHT, true);
    SetRenderDrawColor(COLOR_GRIS);
    RenderRect(ventanaInicia.x, ventanaInicia.y, MENU_WIDTH, MENU_HEIGHT, false);
    // Work area START
    SetRenderDrawColor(COLOR_BLANCO);
    RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*2, areaTermina.x - areaInicia.x, areaTermina.y - (areaInicia.y + MENU_CONTROL_H*2), true);
    // Unica Opcion - Regresar
    SetRenderDrawColor(COLOR_AZUL);
    RenderRect(areaInicia.x, areaInicia.y, areaTermina.x - areaInicia.x, MENU_CONTROL_H, true);
    EscribirTextoCentrado("Regresar", W_CENTER.x , areaInicia.y + 15, FONT_MAIN, COLOR_BLANCO, false);
    
    SetRenderDrawColor(COLOR_GRIS_OSCURO);
    RenderRect(areaInicia.x, areaInicia.y, areaTermina.x - areaInicia.x, MENU_CONTROL_H, false);
    
    for (int i = 0; i < numFilas; i++)
    {
        printf(texto[i]);
        printf("\n");
    }
    fflush(stdout);

    int posicion = 4+3;
        EscribirTexto(texto[4], areaInicia.x + 10 , areaInicia.y + 20*posicion + 8, FONT_SMALL, COLOR_NEGRO, false);
    
    // Opciones
    for (int i = 0; i < numFilas; i++)
    {
        LiberarInput();
        int posicion = i+3;
        EscribirTexto(texto[i], areaInicia.x + 10 , areaInicia.y + 20*posicion + 8, FONT_SMALL, COLOR_NEGRO, false);
    }
    printf("Llego aqui\n");
    fflush(stdout);
    // Work area END
    SetRenderDrawColor(COLOR_GRIS);
    RenderRect(areaInicia.x, areaInicia.y + MENU_CONTROL_H*2, areaTermina.x - areaInicia.x, areaTermina.y - (areaInicia.y + MENU_CONTROL_H*2), false);
    // Titulo
    EscribirTextoCentrado(titulo, W_CENTER.x, ventanaInicia.y + 20, FONT_BOLD, COLOR_NEGRO, false);
    // Hint
    EscribirTextoCentrado("Selecciona una opcion y presiona ENTER", W_CENTER.x, ventanaTermina.y - 20, FONT_SMALL, COLOR_GRIS_OSCURO, false);
    SDL_RenderPresent(RENDERER);

    while (!termino) {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT){
                // Cerrar Programa
                CerrarVentana();
                exit(0);
            } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                termino = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym)
                {
                    case SDLK_KP_ENTER:
                    case SDLK_RETURN:
                        termino = true;
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return;
}

