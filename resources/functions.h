/* cSpell:disable */
#include <math.h>

struct FuncionLineal{
    float m, b;
};
struct FuncionCuadratica{
    float p, h, k;
};

float EvaularFuncionLineal(struct FuncionLineal funcion, float x);
float EvaularFuncionCuadratica(struct FuncionCuadratica funcion, float x);