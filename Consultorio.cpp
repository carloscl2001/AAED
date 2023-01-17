#include <iostream>
#include <pila.h>
#include <cola.cpp>
#include <lista_doble.h>
using namespace std;

struct medico
{
    string id_m;
    Cola<paciente> paciente_;
};

struct paciente
{
    string id_p;
};


class Consultorio
{
    public:
        Consultorio();
        void dar_alta(medico m);
        void dar_baja(medico m);
        void poner(medico m, paciente p);
        paciente& consultar(medico m);
        void atender(medico m);
        bool comprobar(medico m);        
    private:
        Lista<medico> medico_;
};
// NADA
// CREA UN CONSULTORIO VACIO
Consultorio::Consultorio(){};

void Consultorio::dar_alta(medico m){
    medico_.insertar(m,medico_.primera());
}

void Consultorio::dar_baja(medico m){
    assert(medico_.primera() != medico_.fin());
    if(medico_.buscar(m) != medico_.fin())
    {
        medico_.eliminar(medico_.buscar(m));
    }
}

void Consultorio::po