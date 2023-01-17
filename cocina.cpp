#include <cassert>
#include <iostream>
#include "lista_doble.h"
// struct Mueble{
//     float l;
// };
using namespace std;

struct Mueble{
    float posicion;
    float ancMuebleura;
    Mueble(){}
    Mueble(float pos, float ancMuebleo) : ancMuebleura(ancMuebleo), posicion(pos) {}
    Mueble(const Mueble& m){
        this->posicion = m.posicion;
        this->ancMuebleura = m.ancMuebleura;
    }
    Mueble& operator=(const Mueble&);
};

// struct Mueble
// {
//     int u;
// };

class Cocina{
    public:
        Cocina(float fLongitud);
        bool puedeColocarse(const Mueble& m) const;
        void NuevoMueble(Mueble& m, float posicion);
        const Mueble& mueble(unsigned int ubicacion);
        void EliminarMueble(unsigned int ubicacion);
        void MoverMueble(unsigned int ubicacion);
    private:
        float _fLongitud;
        unsigned int _uiNumMuebles;
        Lista<Mueble> _aMuebles;
};

Cocina::Cocina(float fLongitud) :_uiNumMuebles(0){
    assert(fLongitud >= 0);
    _fLongitud = fLongitud;
    _aMuebles = Lista<Mueble>();
}

int main(){
    std::cout<<"hola"<<endl;	
    Cocina c(10);
    Mueble m(1,2);

    return 0;
}
