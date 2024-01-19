#include "pila_enlazada.hpp" //Pila estatica

#include "cola.cpp"//Cola pseudo

#include "lista_doble.h"

using namespace std;

#include <string>


/*Una emisora de radio en línea quiere automatizar la gestión de las listas de reproducción. Por este motivo decide organizar las canciones 
de que dispone en una estructura de datos. Los directivos de la emisora deciden que se necesitan las siguientes operaciones para programar la 
música a emitir:
    •crear:→radio, la emisora tiene el archivo sonoro completamente vacío.
    •añadir: radio cancion→radio, la emisora añade una canción nueva a su archivo sonoro.
    •sugerir: radio entero→cancion, devuelve la canción que tiene la duración dada en segundos y que menos veces se ha emitido en la radio.
    •seleccionar: radio entero→cancion, devuelve la canción que tiene la duración dada en segundos y que se ha emitido más veces.
    •emitir: radio cancion→radio, se toma nota de que la canción se emitirá en laradio. Cada vez que se emite una canción se llama a esta operación.
    •borrar: radio entero→radio, borra las n canciones que se han emitido menos veces. En caso de empate es indiferente la canción que se seleccione.
El número de canciones de que dispone la radio es conocido, pero también sabemos quecada semana la emisora adquiere nuevas canciones y las añade 
al archivo. Para cada canciónse almacena un número que la identifica y su duración en segundos. La empresa os pide quedefináis el TAD radio y que 
lo implementéis de manera que todas las operaciones tengan elmínimo coste temporal posible*/
struct cancion{
    string nombre;
    size_t duracion;
    size_t veces;
    cancion(string n, size_t d, size_t v = 0):nombre(n), duracion(d), veces(v){}
};

class Radio{
    public:
        Radio();
        void anadirCancion(string nombre, size_t duracion);
        string sugerir(size_t duracion);
        string seleccionar(size_t duracion);
        void emitir(string nombre);
        void borrar(size_t n);

    private:
        Lista<cancion> canciones;
        typedef typename Lista<cancion>::posicion pos;
        bool buscar(string nombre);
        pos buscar(size_t veces);
};

bool Radio::buscar(string nombre){
    pos p = canciones.primera();
    while(p != canciones.fin()){
        if(nombre == canciones.elemento(p).nombre){
            return true;
        }
    }
    return false;
}

Radio::pos Radio::buscar(size_t veces){
    pos p = canciones.primera();
    while(p != canciones.fin()){
        if(veces >= canciones.elemento(p).veces){
            return p;
        }else{
            p = canciones.siguiente(p);
        }
    }
    return p;
}

//pre -> si existe la cancion no se añade
void Radio::anadirCancion(string nombre, size_t duracion){
    //no existe 
    if(!buscar(nombre)){
        cancion c(nombre, duracion);
        canciones.insertar(c, canciones.primera());
    }

}

//pre -> existe una cancion con la duracion dada
string Radio::sugerir(size_t duracion){
    pos p = canciones.primera();
    while(p != canciones.fin()){
        if(duracion != canciones.elemento(p).duracion){
            p = canciones.siguiente(p);
        }else{
            p = canciones.fin();
        }
        
    }
    assert(p != canciones.fin());
    return canciones.elemento(p).nombre;
}

string seleccionar(size_t duracion){
    bool encontrado = false;
    pos p = canciones.anterior(canciones.fin());
    while(!encontrado && p != canciones.primera()){
        if(duracion == canciones.elemento(p).duracion){
            encontrado = true;
        }else{
            p = canciones.anterior(p);
        }
    }
    if(!encontrado && duracion != canciones.elemento(p).duracion){
        encontrado = true;
    }
    assert(encontrado);
    return canciones.elemento(p).nombre;
}


void emitir(string nombre){
    //existe la cancion
    cancion c(nombre);
    pos p = canciones.primera();
    while(p != canciones.fin()){
        if(canciones.elemento(p).nombre == nombre){
            c.duracion  = canciones.elemento(p).duracion;
            c.veces = canciones.elemento(p).veces+1;
            canciones.eliminar(p);
            break;
        }
        p = canciones.siguiente(p);
    }
    pos p = buscar(c.veces);
    canciones.insertar(c,p);
}

void Radio::borrar(size_t n){
    assert(n <= canciones.tama());

    for(int i = 0 ; i < n ; i++){
        canciones.eliminar(canciones.primera());
    }
}

