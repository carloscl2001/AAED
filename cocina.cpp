/*
El TAD COCINA es una sucesión de muebles(elemeneto que poseen un ancho y una profundidad)

*/
#include <stdlib.h>
#include <iostream>

struct Mueble{
    float posicion;
    float anchura;
};

class Cocina{
    public:
        Cocina(size_t t);
        ~Cocina();
    private:
        float longitud;
        lista<Mueble> lista;
};

Cocina::Cocina(float l)
{
    if (l > 0)
        longitud = l;
}





