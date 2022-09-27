//
#include <stdlib.h>
#include <iostream>

struct mueble
{
    size_t pos;
    size_t anch;
};

class Cocina{
    public:
        Cocina(size_t l);
    private:
        size_t longi;
        lista<mueble> mueble_;
};

Cocina::Cocina(size_t l):longi(l), mueble(lista<mueble>()){};





