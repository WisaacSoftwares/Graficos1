#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

#define VECTORES_MAX 10

struct Vector{
    char * nombre;
    double x, y, z;
    SDL_Color color;
};

extern struct Vector VECTOR_NULO;
extern struct Vector VECTORES[];

void IniciarVectores ();
int NumeroVectores();
int CrearVector ();
void EliminarVector(int id);

struct Vector Suma (struct Vector v1, struct Vector v2);
struct Vector MultiplicarCte (struct Vector v1, float cte);
float ProductoPunto (struct Vector v1, struct Vector v2);
struct Vector ProductoCruz (struct Vector v1, struct Vector v2);