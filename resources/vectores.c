#include <stdio.h>
#include <string.h>

struct Vector{
    char * nombre;
    float x, y, z;
};

struct Vector Suma(struct Vector v1, struct Vector v2);
struct Vector MultiplicarCte(struct Vector v1, float cte);
float ProductoPunto(struct Vector v1, struct Vector v2);
struct Vector ProductoCruz(struct Vector v1, struct Vector v2);

// int main (void){
//     struct Vector v1 = {"Vector 1", 1, 2, 3};
//     struct Vector v2 = {"Vector 2", 7, 4, 9};
//     float cte = 5;

//     struct Vector resultadoV;
//     float resultadoE;
//     resultadoV.nombre = "Vector Resultante";

//     // resultadoV = Suma(v1, v2);
//     // resultadoV = MultiplicarCte(v1, cte);
//     // resultadoE = ProductoPunto(v1, v2);
//     // resultadoV = ProductoCruz(v1, v2);

//     printf("Constante: %0.2f\n", cte);
//     printf("Vector 1, nombre: %s, x: %0.2f, y: %0.2f, z: %0.2f\n", v1.nombre, v1.x, v1.y, v1.z);
//     printf("Vector 2, nombre: %s, x: %0.2f, y: %0.2f, z: %0.2f\n", v2.nombre, v2.x, v2.y, v2.z);
//     // printf("Vector Resultante, nombre: %s, x: %0.2f, y: %0.2f, z: %0.2f\n", resultadoV.nombre, resultadoV.x, resultadoV.y, resultadoV.z);
//     // printf("Resultado Escalar: %0.2f\n", resultadoE);

//     return 0;
// }

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