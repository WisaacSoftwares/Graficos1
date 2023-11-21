#include "vectores.h"

#include "library.h"

struct Vector VECTOR_NULO = {NULL, 0, 0, 0, {255, 255, 255, 255}};
struct Vector VECTORES_PREF[VECTORES_MAX];
struct Vector VECTORES[VECTORES_MAX];

void IniciarVectores () {
    struct Vector _vectoresPref[VECTORES_MAX] = {
        {"Vector 1", 1, 2, 1, COLOR_AZUL},
        {"Vector 2", -2, 1, 1, COLOR_AMARILLO},
        {"Vector 3", 1, -3, 5, COLOR_ROJO},
        {"Vector 4", 1, 1, 1, COLOR_VERDE_OSCURO},
        {"Vector 5", 1, 1, 1, COLOR_NARANJA},
        {"Vector 6", 1, 1, 1, COLOR_CYAN},
        {"Vector 7", 1, 1, 1, COLOR_CREMA},
        {"Vector 8", 1, 1, 1, COLOR_MORADO},
        {"Vector 9", 1, 1, 1, COLOR_KHAKI},
        {"Vector 10", 1, 1, 1, COLOR_BLANCO}
    };
    VECTORES_PREF[0] = _vectoresPref[0];
    VECTORES_PREF[1] = _vectoresPref[1];
    VECTORES_PREF[2] = _vectoresPref[2];
    VECTORES_PREF[3] = _vectoresPref[3];
    VECTORES_PREF[4] = _vectoresPref[4];
    VECTORES_PREF[5] = _vectoresPref[5];
    VECTORES_PREF[6] = _vectoresPref[6];
    VECTORES_PREF[7] = _vectoresPref[7];
    VECTORES_PREF[8] = _vectoresPref[8];
    VECTORES_PREF[9] = _vectoresPref[9];

    // VECTORES = malloc(sizeof(struct Vector)*VECTORES_MAX);

    VECTORES[0] = VECTORES_PREF[0];
    VECTORES[1] = VECTORES_PREF[1];
    VECTORES[2] = VECTORES_PREF[2];
    VECTORES[3] = VECTOR_NULO;
}

int NumeroVectores(){
    int i = 0;

    while (VECTORES[i].nombre != NULL)
    {
        i++;
    }
    
    return i;
}

int CrearVector (){
    if (NumeroVectores() < VECTORES_MAX) VECTORES[NumeroVectores()] = VECTORES_PREF[NumeroVectores()];
    return NumeroVectores() - 1;
}

void EliminarVector(int id) {
    if (VECTORES[id].nombre != NULL) {
        struct Vector tempPREF = VECTORES_PREF[id];

        for (int i = id; i < NumeroVectores() - 1; i++)
        {
            VECTORES[i] = VECTORES[i+1];
            VECTORES_PREF[i] = VECTORES_PREF[i+1];
        }
        VECTORES_PREF[NumeroVectores()-1] = tempPREF;
        VECTORES[NumeroVectores()-1] = VECTOR_NULO;
    }
    fflush(stdout);
}

struct Vector Suma(struct Vector v1, struct Vector v2){
    struct Vector resultado;

    // Operación
    return resultado;
}

struct Vector MultiplicarCte(struct Vector v1, float cte){
    struct Vector resultado;

    // Operación
    return resultado;
}

float ProductoPunto(struct Vector v1, struct Vector v2){
    float resultado;

    // Operación
    return resultado;
}

struct Vector ProductoCruz(struct Vector v1, struct Vector v2){
    struct Vector resultado;

    // Operación
    return resultado;
}