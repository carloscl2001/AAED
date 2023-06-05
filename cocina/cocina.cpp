#include <cassert>
#include <iostream>
#include "lista_doble.h"

using namespace std;


struct mueble{
    mueble(size_t p, size_t a):posicion(p), anchura(a){}
    size_t posicion;
    size_t anchura;
};

class Cocina{
    public:
        Cocina(size_t t):longitud(t), lista(Lista<mueble>(t)){}
        bool es_posible_colocar(size_t anchura, size_t posicion);
        void añadir_mueble(size_t longitud, size_t posicion);
        mueble devolver(size_t esimo);
        void eliminar(size_t esimo);
        void mover_mueble(size_t esimo);
        ~Cocina();

    private:
        size_t longitud;
        Lista<mueble> lista;
        Lista<mueble>::posicion buscar_posicion(size_t pos);
};


Lista<mueble>::posicion Cocina::buscar_posicion(size_t pos){
    Lista<mueble>::posicion p;
    Lista<mueble>::posicion maxima;

    maxima = p;
    for(p = lista.primera(); p != lista.fin(); p = lista.siguiente(p)){
        if(lista.elemento(p).posicion<= pos){
            maxima = max(maxima, p);
        }
    }   
    return maxima;
}




bool Cocina::es_posible_colocar(size_t anchura, size_t posicion){
    bool es_colocable = false;
    
    if(posicion + anchura <= longitud){
        Lista<mueble>::posicion p;
        Lista<mueble>::posicion p2;

        for(p = lista.primera(); p != lista.anterior(lista.fin()); p = lista.siguiente(p)){
            p2 = lista.siguiente(p);

            //IZQUIERDA DEL TODO
            if(p == lista.primera()){
                if(posicion + anchura <= lista.elemento(p).posicion)
                    es_colocable = true;
            }

            //DERCHA DEL TODO
            else if(p == lista.anterior(lista.fin())){
                if(lista.elemento(p).posicion + lista.elemento(p).anchura <= anchura + posicion <= longitud)
                    es_colocable = true;
            }

            //ENTREMUEBLES
            else if((lista.elemento(p).posicion + lista.elemento(p).anchura <= posicion) && (posicion + anchura <= lista.elemento(p2).posicion)){
                es_colocable = true;
            }
        }
    }
    return es_colocable;
}


void Cocina::añadir_mueble(size_t longitud, size_t posicion){
    if(es_posible_colocar(longitud, posicion)){
        mueble m(longitud, posicion);
        lista.insertar(m,buscar_posicion(posicion));
    }

}

