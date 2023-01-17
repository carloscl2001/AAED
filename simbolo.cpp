#include <pila.h>
#include <cassert>
#include <iostream>
#include <size_t>
using namespace std;

/*a)El TAD simbolo es un tipo abstracto de datos, para representar símbolos trazados con lineas. Es decir, es una sucesión de simbolo, donde se insertan y eliminan los ultimos simobolos y existe  el simbolo vacio. Trazo es una linea recta, qu e puede arriba abajo, izq y drch    
    
    Simbolo()
//precondicion -> no hay
//postcondicion -> crea un simbolo vacio

    void añadirTrazo(Trazo trazo)
//precondicion -> el trazo no esté vacio
//postcondicion -> añade el trazo al final simbolo

    void deshacerTrazos(size_t n)
//precondcion -> el simbolo tiene n o mas trazas
//postcondicon -> saca del simbolo los ultimos n trazas

    Simbolo simetriaX()
//precondicon -> el simbolo no está vacio
//postcondicion -> devuelve el simbolo simétrico respecto a x

    Simbolo simetriaY()
//precondicon -> el simbolo no está vacio
//postcondicion -> devuelve el simbolo simétrico respecto a x

    Simbolo simetriaXY()
//precondicon -> existe el simbolo y no está vacio
//postcondicion -> devuelve el simbolo simétrico respecto a xy
*/

/*

TAD PILA
template <typename tElemento> class Pila{
    public:
        explicit Pila(unsigned TamaMax); // Ctor., requiere ctor. tElemento()
        Pila(const Pila& P); // Ctor. de copia
        Pila& operator =(const Pila& P); // Asignación entre pilas
        bool vacia() const;
        bool llena() const; // Requerida por la implementación
        const tElemento& tope() const;
        void pop();
        void push(const tElemento& x);
        ~Pila(); // Destructor
    private:
        struct nodo {
            T elto;
            nodo* sig;
            nodo(const T& e, nodo* p = nullptr): elto(e), sig(p) {}
        };

        nodo* tope_;

        void copiar(const Pila<T>& P);
};
*/


//TAD SIMBOLO
#define ARRIBA 1
#define ABAJO 2
#define IZQ 3
#define DRCHA 4
struct Trazo{
    size_t direccion;
    trazo(size_t t):direccion(t){}
};

class Simbolo{
    public:
        Simbolo();
        void anadirTrazo(Trazo t);
        void deshacerTrazo(size_t n);
        Simbolo simetriaX();
        Simbolo simetriaY();
        Simbolo simetriaXY();
    private:
        pila<trazo> sucesion;
        size_t n_trazos;
};

Simbolo::Simbolo(){
    sucesion();
    n_trazos = 0;
}

void Simbolo::anadirTrazo(Trazo t){
    if (t.direccion < 4 && t.direcion > 1)
        sucesion.push(t);
    n_trazos++;

}

void Simbolo::deshacerTrazo(size_t n){
    assert(n > 0);
    for (size_t i = 0; i < n; i++){
        sucesion.pop();
        n_trazos++
    }
}
Simbolo Simbolo::simetriaX(){
    assert(n_trazos > 0);
    pila<trazo> aux();
    Simbolo nuevo();
    for (size_t i = 0; i < n_trazos; i++){
        Trazo t = sucesion.tope();
        if (t.direccion == DRCHA)
        {
            t.direccion = IZQ;
        }else if(t.direccion == IZQ){
            t.direccion == DRCHA;
        }
        aux.push(t);
        suesion.pop();
    }
    for (size_t i = 0; i < aux.n_trazos; i++){
        sucesion.push(sucesion.tope());
        aux.pop();
    }
    return nuevo;
}

Simbolo Simbolo::simetriaY(){
    pila<trazo> sucesion2 = this.sucesion;
    assert(n_trazos > 0);
    pila<trazo> aux();
    Simbolo nuevo();
    for (size_t i = 0; i < n_trazos; i++){
        Trazo t = sucesion2.tope();
        if (t.direccion == ARRIBA)
        {
            t.direccion = ABAJO;
        }else if(t.direccion == ABAJO){
            t.direccion == ARRIBA;
        }
        aux.push(t);
        suesion2.pop();
    }
    for (size_t i = 0; i < aux.n_trazos; i++){
        nuevo.sucesion.push(aux.tope());
        aux.pop();
    }
    return nuevo;
}

Simbolo Simbolo::simetriaXY(){
    assert(n_trazos > 0);
    pila<trazo> aux();
    Simbolo nuevo();
    for (size_t i = 0; i < n_trazos; i++){
        Trazo t = sucesion.tope();
        if (t.direccion == ARRIBA)
        {
            t.direccion = ABAJO;
        }else if(t.direccion == ABAJO){
            t.direccion == ARRIBA;
        }
        if(t.direccion == IZQ){
            t.direccion == DRCHA
        }else if(t.direccion == IZQ){
            t.direccion == DRCHA
        }
        aux.push(t);
        suesion.pop();
    }
    for (size_t i = 0; i < aux.n_trazos; i++){
        nuevo.sucesion.push(aux.tope());
        aux.pop();
    }
    return nuevo;
}
