#include <string.h>

struct Color{
    int r, g, b, a;
};

struct Vector{
    char * nombre;
    float x, y, z;
    struct Color color;
};

struct Vector Suma(struct Vector v1, struct Vector v2);
struct Vector MultiplicarCte(struct Vector v1, float cte);
float ProductoPunto(struct Vector v1, struct Vector v2);
struct Vector ProductoCruz(struct Vector v1, struct Vector v2);