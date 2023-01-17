#include <cstring>
#include <iostream>
#include <cassert>
#include "lista_doble.h"
using namespace std;
/*
a)------------------------------------------------------------------------------------------------------
EL TAD Dicccionartio es una sucesión de elementos terminoIngles, en donde cada traduccion esta formada por otra sucesion de terminos de tipo traduccionEspanol.

    Diccionario()
Precondicion -> ninguna
Postcondicion -> crea un diccionario vacio

    void insertarTradEsp(string terminoIngles, string traduccionEspanol)
Precondicion -> El terminoIngles se encuentra en el dicccionario y no contiene la traduccionEspanol
Postcondicion -> Introduce la traduccionEspanol en el terminoIngles

    void eliminarTradEsp(string terminoIngles, string traduccionEspanol)
Precondicion -> El terminoIngles se encuentra en el dicccionario y que contiene traduccionEspanol
Postcondicion -> Eliminar la traduccion terminoEspanol del termnoIngles

    void consultarTradEsp(string terminoIngles)
Precondicion -> El terminoIngles se encuentra en el diccionario
Postcondicion -> Imprime todas las traduciones espanolas de la palabras inglesa

    -Diccionario()
Precondicion -> existe el dicccionario
Postcondicoin -> Destruye el dicccionario

b)------------------------------------------------------------------------------------------------------
El TAD diccionario, esta representado por una lista de terminosIngles, donde as su vez, cada terminoIngles esta formado por una lista de traduccionEspanol.

traduccionEspanol es un string
*/
struct terminoIngles{
    terminoIngles(string s):sIng(s){
        nTrad = 0;
        lTradEsp = Lista<string>();
    }
    string sIng;
    Lista<string> lTradEsp;
    size_t nTrad;
};

class Diccionario{
    public:
        Diccionario():nTer(0){
            lTerIng = Lista<terminoIngles>();
        }
        void insertarTradEsp(string, string);
        void eliminarTradEsp(string, string);
        void consultarTradEsp(string);
        ~Diccionario();

    private:
        Lista<terminoIngles> lTerIng;
        size_t nTer;
};

//Precondicion -> El terminoIngles se encuentra en el dicccionario y no contiene la traduccionEspanol
//Postcondicion -> Introduce la traduccionEspanol en el terminoIngles
void Diccionario::insertarTradEsp(string termIng, string tradEsp){
    Lista<terminoIngles>::posicion p;
    while(p != lTerIng.fin() && lTerIng.elemento(p).sIng != termIng){
        p = lTerIng.siguiente(p);
    }

    bool existe = false;

    Lista<string> lIngEsp = lTerIng.elemento(p).lTradEsp;
    Lista<string>::posicion p2 = lIngEsp.primera();
    while(p2 != lIngEsp.fin() && existe == false){
        if(lIngEsp.elemento(p2) == tradEsp)
            existe = true;
        else
        p2 = lIngEsp.siguiente(p2);
    }
    lIngEsp.insertar(tradEsp,p2);
}

//Precondicion -> El terminoIngles se encuentra en el dicccionario y que contiene traduccionEspanol
//Postcondicion -> Eliminar la traduccion terminoEspanol del termnoIngles
void Diccionario::eliminarTradEsp(string termIng, string tradEsp){
    bool existe = false;

    //Miramos primera lista
    Lista<terminoIngles>::posicion p = lTerIng.primera();
    while(p != lTerIng.fin() && lTerIng.elemento(p).sIng != termIng){
        p = lTerIng.siguiente(p);
    }

    //Miramos segunda lista
    Lista<string> lEspIng = lTerIng.elemento(p).lTradEsp;
    Lista<string>::posicion p2 = lEspIng.primera();
    while(p2 != lTerIng.elemento(p).lTradEsp.fin() && false){
        if(lEspIng.elemento(p2) == tradEsp)
            existe = true;
        else
            p2 = lEspIng.siguiente(p2);
    }

    //si existe la eliminamos
    if(existe)
        lEspIng.eliminar(p2);
}

//Precondicion -> El terminoIngles se encuentra en el diccionario
//Postcondicion -> Imprime todas las traduciones espanolas de la palabras inglesa
void Diccionario::consultarTradEsp(string termIng){

    Lista<terminoIngles>::posicion p = lTerIng.primera();
    while(p != lTerIng.fin() && p->elto.sIng != termIng){
        p = lTerIng.siguiente(p);
    }
    Lista<string> lEspIng = lTerIng.elemento(p).lTradEsp;
    Lista<string>::posicion p2 = lEspIng.primera();
    while (p2 != lEspIng.fin()){
        cout<<lEspIng.elemento(p2);
        p2 = lEspIng.siguiente(p2);
    }    
}
