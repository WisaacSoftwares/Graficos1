#include "vectores.h"

#include "library.h"

struct Vector VECTOR_NULO = {NULL, 0, 0, 0, {255, 255, 255, 255}};
struct Vector VECTORES_PREF[VECTORES_MAX];
struct Vector VECTORES[VECTORES_MAX];

void IniciarVectores () {
    struct Vector _vectoresPref[VECTORES_MAX] = {
        {"A", 1, 2, 1, COLOR_AZUL},
        {"B", -2, 1, 1, COLOR_AMARILLO},
        {"C", 1, 1, 1, COLOR_ROJO},
        {"D", 1, 1, 1, COLOR_VERDE_OSCURO},
        {"E", 1, 1, 1, COLOR_NARANJA},
        {"F", 1, 1, 1, COLOR_CYAN},
        {"G", 1, 1, 1, COLOR_CREMA},
        {"H", 1, 1, 1, COLOR_MORADO},
        {"I", 1, 1, 1, COLOR_KHAKI},
        {"J", 1, 1, 1, COLOR_BLANCO}
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
    VECTORES[2] = VECTOR_NULO;
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

int CrearVectorDatos(char * nombre, double x, double y, double z){
    int id;
    if (NumeroVectores() < VECTORES_MAX) VECTORES[NumeroVectores()] = VECTORES_PREF[NumeroVectores()];
    id = NumeroVectores() - 1;
    VECTORES[id].nombre = nombre;
    VECTORES[id].x = x;
    VECTORES[id].y = y;
    VECTORES[id].z = z;

    return id;
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

char * ConcatenarNombre(char * nombre1, char ope, char * nombre2){
    // Define el tamaño del nombre
    int sizeChar = snprintf(NULL, 0, "%s %c %s", nombre1, ope, nombre2);
    // Asigna el espacio
    char * str = (char *)malloc(sizeChar + 1);
    // Concatena el nombre
    sprintf(str, "%s %c %s", nombre1, ope, nombre2);
    return str; // Devuelvo
}

struct Vector Suma(struct Vector v1, struct Vector v2){
    struct Vector resultado;

    resultado.nombre = ConcatenarNombre(v1.nombre, '+', v2.nombre);
    resultado.x=v1.x+v2.x;
    resultado.y=v1.y+v2.y;
    resultado.z=v1.z+v2.z;
    // Operación
    return resultado;
}

struct Vector MultiplicarCte(struct Vector v1, float cte){
    struct Vector resultado;
    
    resultado.nombre = ConcatenarNombre(v1.nombre, '*', DoubleToStr(cte));
    resultado.x = v1.x * cte;
    resultado.y = v1.y * cte;
    resultado.z = v1.z * cte;
    // Operación
    return resultado;
}

double ProductoPunto(struct Vector v1, struct Vector v2){
    double resultado;
    resultado = (v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z); 
    // Operación
    return resultado;
}

struct Vector ProductoCruz(struct Vector v1, struct Vector v2){
    struct Vector resultado;

    resultado.nombre = ConcatenarNombre(v1.nombre, 'x', v2.nombre);
    resultado.x = (v1.y*v2.z)-(v1.z*v2.y); 
    resultado.y = ((v1.x*v2.z)-(v1.z*v2.x))*(-1); 
    resultado.z = (v1.x*v2.y)-(v1.y*v2.x); 
    // Operación
    return resultado;
}