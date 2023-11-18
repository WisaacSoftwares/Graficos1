/* cSpell:disable */
#include <math.h>
#include <stdio.h>

struct FuncionLineal{
    float m, b;
};
struct FuncionCuadratica{
    float p, h, k;
};

float EvaularFuncionLineal(struct FuncionLineal funcion, float x){
    return funcion.m*(x) + funcion.b;
}

float EvaularFuncionCuadratica(struct FuncionCuadratica funcion, float x){
    return (funcion.p)*pow((x-funcion.h), 2) + funcion.k;
}