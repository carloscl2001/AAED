#include "../lista_doble.h"

struct trama{}; //estructura dada


struct computador{
    public:
        computador(char nom[8]):nombre(new char[8]), datos(Lista<trama>()){

        }
        char* nombre_(){return nombre;}

    private:
        char nombre[8];
        Lista<trama> datos;
};


class TokenBus{
    public:
        TokenBus(computador c);
        void añadir_computador(char* nombre);
        void eliminar_computador();
        void pasar_token();
        char* c_token();
        void enviar_trama(trama t, char* nombre1, char* nombre2);
    private:
        size_t n_computadores;
        Lista<computador> listaOrdenadores;
        Lista<computador>::posicion token;
};


TokenBus::TokenBus(computador c):n_computadores(1),listaOrdenadores(Lista<computador>()), token(listaOrdenadores.primera()){
    listaOrdenadores.insertar(c,listaOrdenadores.primera());
}

void TokenBus::añadir_computador(char* nombre){
    if(n_computadores < 25){
        computador c(nombre);
        listaOrdenadores.insertar(c,listaOrdenadores.fin());
        n_computadores++;
    }
}

void TokenBus::eliminar_computador(){
    listaOrdenadores.eliminar(listaOrdenadores.primera());
}

void TokenBus::pasar_token(){
    token = listaOrdenadores.siguiente(token);
}

char* TokenBus::c_token(){
    return (listaOrdenadores.elemento(token).nombre_());
}

void TokenBus::enviar_trama(trama t, char* nombre1, char* nombre2){

}