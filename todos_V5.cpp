#include "pila_enlazada.hpp" //Pila estatica

#include "cola.cpp"//Cola pseudo

#include "lista_doble.h"

using namespace std;

#include <string>

//-----------------------------------APUNTES DE TEORIA------------------------------------------------------------------------------------------------------------------
//Pilas con bicolas
/*
Bicola.push(elemento, izquierdo); 
Bicola.pop(izquierdo);

//Colas con bicolas
Bicola.push(elemento, izquierdo); 
Bicola.pop(derecho);

//Lista Circular 
ListaCir<t>::posicion p = Lista.siguiente(Lista.inipos())
while(p != Lista.inipos()){

}
if(p == Lista.inipos()){

}
*/

//FUNCIÓN INVERTIR-----------------------------------------------------------------------------------------------------------------------------------------------------
//Escriba una función que dados dos elementos a y b y una pila, invierta la secuencia delimitada por ambos dentro de ella.
//Dado que la pila puede tener elementos repetidos, se invertirá la secuencia delimitada por
//la primera ocurrencia de a y de b.

Pila<char> invertir(char a, char b, Pila<char> p){
    Pila<char> paux1;
    Pila<char> paux2;
    Pila<char> final;

    while(!p.vacia() && p.tope() != a){
        paux1.push(p.tope());
        p.pop();
    }
    while(!p.vacia() && p.tope() != b){
        paux2.push(p.tope());
        p.pop();
    }
    if(!p.vacia() && p.tope() == b){
        paux2.push(p.tope());
        p.pop();
    }
    while(!paux2.vacia()){
        paux1.push(paux2.tope());
        paux2.pop();
    }
    while(!p.vacia()){
        paux1.push(p.tope());
        p.pop();
    }
    while(!paux1.vacia()){
        final.push(paux1.tope());
        paux1.pop();
    }

    return final;
}

//TAD TREN--------------------------------------------------------------------------------------------------------------------------------------------------------------
//Realizar la especificacion e implementacion de un tad tren que sirva para representar secuencias
// de longitud arbitraria de vagones, se supone que el tipo vagon esta predefinido
//si la secuencia no esta vacia hay un vagon de tren denominado activo sobre el que puede
//actuar un robot manipulador, las operaciones que se piden son:
// - crea un tren
// - desplazar a la izquieda ( mueve un tren una posicion a la izq, de manera que el nuevo vagon activo es el que está
// inmediatamente a la derecha del actual, si no hay vagon a la derecha no se hace nada )
// -desplazar a la derecha ( simetrica a la anterior)
// -eliminar el vagon activo ( se suprime el vagon activo y se convierte en activo el que está indediatamenta a su derecha
// si este no existe se activa el de su izquierda , y si este ultimo no existe el tren queda vacio
// - insertar vagon activo ( añade un nuevo vagon al tren desplazando el actual vagon activo
// y los siguientes una posicion a la derecha )
// - observar el vagon activo ( una camara fija situada sobre el robot, devuelve el vagón activo)
// - tren vacio ( indica si el tren tiene vagones )

// NOTA: se prohibe expresamente utilizar una estructura doblemente enlazada
// y se exige que el coste de todas las operaciones sea constante, es decir, independientemente
// del numero de vagones del tren.//

//definicion:
//Un tren es una secuencia de elementos de tipo vagon de una longitud arbitraria
//Hay un vagon activo por cada tren

//a) Especificacion 
    //El vagon activo se encuntar en el tope de la pila derecha
  


//b) Implementacion
template <typename tVagon>
class Tren{
    public:
        Tren();
        void desplazarIzqda();
        void desplazarDrcha();
        void eliminarVagonActivo();
        void insertarVagonActivo(tVagon v);
        tVagon VagonVacio();
        bool trenVacio();
    private:
        Pila<tVagon> pI;
        Pila<tVagon> pD;
};

template <typename tVagon>
Tren::Tren():pI(Pila<tVagon>()), pD(Pila<tVagon>()){}

template <typename tVagon>
void Tren::desplazarIzqda(){

    tVagon aux = pD.tope();
    pD.pop();
    if(!pD.vacia()){
        pI.push(aux);
    }else{
        pD.push(aux);
    }
}

template <typename tVagon>
void Tren::desplazarDrcha(){
    pD.push(pI.tope());
    pI.pop();
}

void Tren::eliminarVagonActivo(){
    pD.pop();
}

template <typename tVagon>
void Tren::insertarVagonActivo(tVagon v){
    pD.push(v);
}


template <typename tVagon>
tVagon Tren::VagonVacio(){
    return pD.tope();
}

bool TrenVacio(){
    return (pD.vacia() && pI.vacia());
}




//TAD DICCIONARIO------------------------------------------------------------------------------------------------------------------------------------------------------
//Crear un diccionario de traduccion de palabras de ingles a español
//cada palabra inglesa tendra 1 o mas traducciones al español
//forma mas eficiente posible(ordernar alfabeticamente)
//funciones:
//crear diccionario vacio
//insertar una traduccion de español de una palabra en ingles
//consultar si es correcta la traduccion en español de una palabra en ingles
//consultar todas las traducciones del español de una palabra en ingles
//eliminar una traduccion en español de una palabra en ingles
//eliminar el diccionario
//a) Especificacion


//b)Implementacion
struct palabra{
    string  word;
    Lista<string> traducciones;
};

class Diccionario{
    public:
        Diccionario(){};
        void insertar(string pngles, string pEspanol);
        bool consultar(string pIngles, string pEspanol) const;
        Lista<string> traducciones(string pIngles) const;
        void eliminar(string pIngles, string pEspanol);
        ~Diccionario(){};
    private:
        Lista<palabra> palabras;
        typedef typename Lista<palabra>::posicion p_palabra;
        typedef typename Lista<string>::posicion p_trad;
};

Diccionario::Diccionario():palabras(Lista<palabra>()){}

void insertarEsIN(string pEspanol, string pIngles){
    p_palabra = palabras.primera();
    while(p_palabra != palabras.pfin()){
        //existe la palabra
        if(palabras.elemento(p_palabra).word == pIngles){
            p_trad = palabras.elemento(p_palabra).traducciones.primera();
            while(p_trad != palabras.elemento(p_palabra).traducciones.fin()){
                //no existe la traduccion la mtemos ordenada, si existiera no se mete
                if(palabras.elemento(p_palabra).traducciones.elemento(p_trad) != pEspanol){
                    //encontramos la posicion para insertar
                    if(pEspanol < palabras.elemento(p_palabra).traducciones.elemento(p_trad))
                        palabras.elemento(p_palabra).traducciones.insertar(pEspanol, p_trad);
                }
                p_trad = palabras.elemento(p_palabra).traducciones.siguiente(p_trad);
            }
            p_palabra = palabras.fin();
        }
        //no existe la palabra
        else{
            if(pIngles < palabras.elemento(p_palabra).word){
                //metemos palabra inglesa
                palabra p(pIngles, Lista<string> ());
                palabras.insertar(p, p_palabra);
                //metemos traduccion
                palabras.elemento(p_palabra).traducciones.insertar(pEspanol,  palabras.elemento(p_palabra).traducciones.fin());
                p_palabra = palabras.fin();
            }
            p_palabra = palabras.siguiente(p_palabra);
        }  
        p_palabra = palabras.siguiente(p_palabra);  
    }
}

bool Diccionario::consultar(string pIngles, string pEspanol) const{
    p_palabra = palabras.primera();
    while(p_palabra != palabras.fin()){
        if(palabras.elemento(p_palabra).word == pIngles){
            p_trad = palabras.elemento(p_palabra).traducciones.primera();
            while(p_trad != palabras.elemento(p_palabra).traducciones.fin()){
                if(palabras.elemento(p_palabra).traducciones.elemento(p_trad) == pEspanol)
                    return true;
                else
                    p_trad = palabras.elemento(p_palabra).traducciones.siguiente(p_trad);
            }
            p_palabra = palabras.fin();
        }
        p_palabra = palabras.siguiente(p_palabra);
    }
    return false;
}

Lista<string> traducciones(string pIngles) const{
    p_palabra = palabras.primera();
    while(p_palabra != palabras.pfin()){
        if(palabras.elemento(p_palabra).word == pIngles){
            return palabras.elemento(p_palabra).traducciones;
        }          
    }
    p_palabra = palabras.siguiente(p_palabra);
}

void eliminar(string pIngles, string pEspanol){
    p_palabra = palabras.primera();
    while(p_palabra != palabras.fin()){
        if(palabras.elemento(p_palabra).word == pIngles){
            p_trad = palabras.elemento(p_palabra).traducciones.primera();
            while(p_trad != palabras.elemento(p_palabra).traducciones.fin()){
                if(palabras.elemento(p_palabra).traducciones.elemento(p_trad) == pEspanol){
                    palabras.elemento(p_palabra).traducciones.eliminar(p_trad);
                    p_palabra = palabras.fin();
                }
            }
        }
        p_palabra = palabras.siguiente(p_palabra);
    }
    return false;
}


//TAD CONSULTORIO DE UN MEDICO------------------------------------------------------------------------------------------------------------------------------------------
/*La dirección de un hospital quiere informatizar su consultorio médico con un programa que realice las
siguientes operaciones:
- Generar un consultorio vacío.
- Dar de alta a un médico.
- Dar de baja a un médico.
- Poner a un paciente en la lista de espera de un médico.
- Consultar al paciente a quien le toca el turno para ser atendido.
- Atender al paciente que le toque por parte de un médico.
- Comprobar su un médico determinado tiene o no pacientes en espera.
a) Realice la especificación del TAD
b)Diseñe una estructura de datos adecuada para representar el TAD e implemente las operaciones
anteriores.
NOTA: Es absolutamente necesario definir todos los tipos de datos implicados en la resolución del ejercicio,
así como los prototipos de las operaciones utilizadas de los TADs conocidos.:*/
//a) Especificacion
   
//b) Implementacion
struct medico{
    string idMedico;
    Cola<string> cPacientes;
    medico(string s):idMedico(s), cPacientes(Cola<string>()){}
};

class Consultorio{
    public:
        Consultorio();
        void darAlta(string idMedico);
        void darBaja(string idMedico);
        void ponerEspera(string idPaciente, string idMedico);
        string consultarTurno(string idMedico);
        void atender(string idMedico);
        bool espera(string idMedico);
    private:
        Lista<medico> lista;
        Lista<medico>::posicion pos;
        pos buscarMedico(string idMedico) const;
};

//devuelve fin si no lo encuntra
pos Consultorio::buscarMedico(string idMedico) const{
    pos p = lsista.primera();
    while(p != lista.fin()){
        if(lista.elemento(p).idMedico == idMedico)
            return p;
        else
            p = lista.siguiente(p);
    }
    return p;
}

Consultorio::Consultorio():lista(Lista<medico>()){}

void Consultorio::darAlta(string idMedico){
    pos p = buscar(idMedico);
    if(p == lista.fin()){
        medico m(idMedico);
        lista.insertar(m,p);
    }
}

void Consultorio::darBaja(string idMedico){
    pos p = buscar(idMedico);
    if(p != lista.fin()){
        lista.eliminar(p);
    }
}

void Consultorio::ponerEspera(string idPaciente, string idMedico){
    bool encontrado = false;
    pos p = buscar(idMedico);
    if(p != lista.fin()){
        Cola<string> cAux;
        while(!lista.elemento(p).cPacientes.vacia()){
            //se encontraba en la cola
            if(lista.elemento(p).cPacientes.frente() == idPaciente){
                encontrado = true;
            }
            cAux.push(lista.elemento(p).cPacientes.frente());
            lista.elemento(p).cPacientes.pop();
        }
        lista.elegida(p).cPacientes = cAux;
        if(!encontrado){
            lista.elemento(p).push(paciente);
        }
    }
}

idPaciente Consultorio::consultarTurno(string idMedico){
    pos p = buscar(idMedico);
    if(p != lista.fin()){
        return lista.elemento(p).cPacientes.frente();
    }
}

void atender(string idMedico){
    pos p = buscar(idMedico);
    if(p != lista.fin()){
        lista.elemento(p).cPacientes.pop();
    }
}

bool espera(string idMedico){
    pos p = buscar(idMedico);
    if(p != lista.fin()){
        return lista.elemento(p).cPacientes.vacia();
    }
}



//TAD TOKEN BUS-------------------------------------------------------------------------------------------------------------------------------------------------------
/* El estándar IEE 802.4 define las redes TokenBus. TokenBus combina una estructura de bus 
de las redes Ethernet y el sistema de testigo TokenRin.El modo de transmisión es el de 
banda ancha sobre cable coaxial. Los computadores están conectados a un bus, pero el 
trabajo se realiza en un anillo lógico. Cada máquina está identificada con un nombre (de máximo 8 caracteres) dentro de la red.

El testigo o token es una rama de información que otorga la posibilidad de enviar datos a 
la estación en la que se encuentre. El testigo se va desplazando en orden por la red, si una 
maquina recibe el testigo, puede transmitir información o bien pasarlo a la máquina 
siguiente.

El orden viene determinado por el orden de inserción de las máquinas en el bus. Por 
motivo de medio de transmisión el máximo de computadores es de 25.

El objetivo es diseñar un tad con las siguientes operaciones:
-	Inicializar la red, máximo de 25 computadores por red, añade el primer computador e inicializa el token
-	Añadir computador
-	Eliminar computador, sale el primero que entró en la red
-	Pasar el token al siguiente
-	Token: indica que computador tiene el token
-	Enviar una trama concreta del computador A al computador B. Suponemos que trama es un tipo ya definido */
struct ordenador{
    string nombre;
    trama t;
    bool token;
    ordenador(string s, trama t_, bool b = false):nombre(s), t(t_), token(b){} 
};

class TokenBus{
    public:
        TokenBus(string nombre, trama t);
        void anadirComputador(string nombre, trama t);
        void eliminarComputador();
        void pasarSiguienteToken();
        string consultarToken() const;
        void enviarTrama(string n1, string n2);

    private:
        const size_t numMax = 25;
        ListaCir<ordenador> computadores;
        typedef typename ListaCir<ordenador>::posicion pos;
        pos primer_computador;
        bool existeComputador(string nombre);

}
bool TokenBus::existeComputador(string nombre){
    pos p = computadores.inipos();
    p = computadores.siguiente(p);
    while( p != computadores.inipos()){
        if(memcmp(computadores.elemento(p).nombre,nombre))
            return true;
        p = computadores.siguiente(p);
    }
    if(memcmp(computadores.elemento(p).nombre,nombre))
        return true;
    return false;
}


TokenBus::TokenBus(string nombre, trama t){
    ordenador o(nombre, t,true);
    computadores.insertar(o, computadores.inipos());
    primer_computador = computadores.inipos();
}

void TokenBus::anadirComputador(string nombre, trama t){
    assert(computadores.tama() < numMax);
    assert(!existeComputador(nombre));
    computador c(nombre, t);
    computadores.insertar(computadores.anterior(primer_computador),c);
}

void TokenBus::eliminarComputador(){
    assert(computadores.tama() > 0);
    if(computadores.elemento(primer_computador).token){
        pasarSiguienteToken();
    }
    pos p2 = computadores.siguiente(primer_computador);
    computadores.eliminar(primer_computador);
    primer_computador = p2;
}

void TokenBus::pasarSiguienteToken(){
    assert(computadores.tama() > 1);

    //busqueda del compu del token
    pos p = computadores.inipos();
    if(computadores.elemento(p).token){
        pToken = p;
    }else{
        p = computadores.siguiente(p);
        while( p != computadores.inipos()){
            if(computadores.elemento(p).token){
                pToken = p;
                break;
            }
            p = computadores.siguiente(p);
        }
    }

    //pasar el token
    computadores.elemento(pToken).token = false;
    computadores.elemento(computadores.siguiente(pToken)).token = true;
}


string consultarToken() const{
    assert(computadores.tama() >= 1);

    //busqueda del compu del token
    pos p = computadores.inipos();
    if(computadores.elemento(p).token){
        return computadores.elemento(p).nombre;
    }else{
        p = computadores.siguiente(p);
        while( p != computadores.inipos()){
            if(computadores.elemento(p).token){
                return computadores.elemento(p).nombre;
            }
            p = computadores.siguiente(p);
        }
    }
}


void enviarTrama(string n1, string n2){
    assert(existeComputador(n1) && existeComputador(n2));
    assert(computadores.tama() >= 2);

    pos pToken1, pToken2;

    pos p = computadores.inipos();
    size_t cont = 0;
    do{
        if(memcpm(computadores.elemento(p).nombre, n1)){
            pToken1 = p;
            cont++;
        }
        if(memcpm(computadores.elemento(p).nombre, n2)){
            pToken2 = p;
            cont++;
        }
        p = computadores.siguiente(p);

        
    }while(cont < 2 && p!= computadores.inipos() );

    computadores.elemento(pToken2).t = computadores.elemento(pToken1).t;
}

//TAD CUBILETE----------------------------------------------------------------------------------------------------------------------------------------------------------
/*Un conocido juguete está formado por una colección de cubiletes de diferentes tamaños que se
pueden apilar colocando cada uno de ellos boca arriba o boca abajo. Así, dos cubos de distinto
tamaño se pueden apilar de 8 formas diferentes representadas en la siguiente figura.
Partiendo de una pila de cubiletes, todos de diferente tamaño y en cualquier orden, en la que
cada uno de ellos puede estar boca arriba o boca abajo, el juego consiste en construir una
nueva pila con todos los cubos boca abajo y ordenados de mayor a menor tamaño (en sentido
de abajo hacia arriba).
    a) Defina el tipo de datos tCubo para representar los cubiletes del juego.
    b) Implemente una función que dada una pila cualquiera de cubiletes simule el juego y 
    devuelva la nueva pila construida. La solución se basará exclusivamente en el TAD Pila. */

struct tCubo{
    size_t tamano;
    bool bocaBajo;
};

Pila<tCubo> construirPila(Pila<tCubo> pila){
    size_t tam = pila.tama();
    Pila<tCubo> pAux;
    Pila<tCubo> pFinal;
    while(pFinal.tam() != tam){
        tCubo cuboMax = pila.tope();
        // de pila a pila aux
        while(!pila.vacia()){
            pila.tope(); = true;
            pila.pop();
            if(pila.tope().tamano > cuboMax.tamano){
                cuboMax = pila.tope();
            }
            pAux.push(aux);
        }
        //de pila aux a y pila o si es el mayor a pila Final
        while(!pAux.vacia()){
            if(pAux.tope().tamano == cuboMax.tamano){
                pFinal.push(pAux.tope());
                pAux.pop();
            }else{
                pila.push(pAux.tope());
                pAux.pop();
            }
        }

    }
    
}


//TAD HOSPITAL--------------------------------------------------------------------------------------------------------------------------------------------------------
// especifica e implementa el TAD Hospital
// representa los parcientes mediante codigos de pacientes ingresados en el mismo
// la gravedad de los pacientes con un digito decimal
// orden decreciente de gravedad
// gravedad 1-5 --> uci
// gravedad 6-9 --> planta
// gravedad 0 --> morge
// capacidad limitada
// si paciente uci, y esta ocupada, el más grave a planta
// la planta mejor alta
// situacion anomada, sera resuelta lo antes posible,

// OPERACIONES
// crear hospital
// ingreso
// alta
// muerte
// paciente en uci
// pacientes en planta
// pacientes gravedad determinada
// destruir hospital

struct paciente{
    size_t id;
    size_t gravedad;
    paciente(size_t _id, size_t _gravedad):id(_id), gravedad(_gravedad){}
};

class Hospital{
    public:
        Hospital(size_t n_uci, size_t n_planta);
        void ingreso(size_t id, size_t gravedad);
        void alta(size_t id);
        void muerte();
        size_t pacientes_uci() const;
        size_t pacientes_planta() const;
        size_t gravedad_determinada(size_t gravedad) const;
        ~Hospital();
    private:
        size_t capacidad_uci;
        size_t capacidad_planta;
        Lista<paciente> uci;
        Lista<paciente> planta;
        typedef typename Lista<paciente>::posicion pos;
        bool existe_paciente(size_t id);
};

bool Hospital::existe_paciente(size_t id){
    pos pu = uci.primera();
    pos pp = planta.primera();

    while(pu != uci.fin()){
        if(uci.elemento(pu).id == id){
            return true;
        }
        pu = uci.siguiente(pu);
    }

    while(pp != planta.fin()){
        if(planta.elemento(pp).id == id){
            return true;
        }
        pp = planta.siguiente(pp);
    }

    return false;
}

Hospital::Hospital(size_t n_uci, size_t n_planta):capacidad_uci(n_uci), capacidad_planta(n_planta){}

void Hospital::ingreso(size_t id, size_t gravedad){
    //Comprobamos que el paciente no estuviese ya en el hospital
    assert(!existe_paciente(id));

    //Si el paciente tiene gravedad de planta
    if(gravedad >= 6 && gravedad <= 9){
        //Si la planta no está llena
        if(planta.tama() < capacidad_planta){
            //Insertamos al paciente por orden de gravedad (9, 8, 7, 7, 6 ...)
            pos p = planta.primera();
            while(p != planta.fin()){
                if(gravedad >= planta.elemento(p).gravedad){
                    paciente pa(id, gravedad);
                    planta.insertar(pa, p);
                    break;
                }
                p = planta.siguiente(p);
            }
            if(p == planta.fin()){
                paciente pa(id, gravedad);
                planta.insertar(pa, p);
            }
        }
        //Si la planta está llena (Si tu gravedad es peor que el más sano de la planta, este se va)
        else{
            if(gravedad < planta.elemento(planta.primera()).gravedad){ 
                //Damos de alta al paciente mas sano
                alta(planta.elemento(planta.primera()).id);
                //Insertamos al paciente por orden de gravedad (9, 8, 7, 7, 6 ...)
                pos p = planta.primera();
                while(p != planta.fin()){
                    if(gravedad >= planta.elemento(p).gravedad){
                        paciente pa(id, gravedad);
                        planta.insertar(pa, p);
                        break;
                    }
                    p = planta.siguiente(p);
                }
                if(p == planta.fin()){
                    paciente pa(id, gravedad);
                    planta.insertar(pa, p);
                }
            }
        }
    }
    else{
        //Si el paciente tiene gravedad de uci
        if(gravedad >= 1 && gravedad <= 5){
            //Si la uci no está llena
            if(uci.tama() < capacidad_uci){
                //Insertamos al paciente por orden de gravedad (5, 5, 4, 3, 1 ...)
                pos p = uci.primera();
                while(p != uci.fin()){
                    if(gravedad >= uci.elemento(p).gravedad){
                        paciente pa(id, gravedad);
                        uci.insertar(pa, p);
                        break;
                    }
                    p = uci.siguiente(p);
                }
                if(p == uci.fin()){
                    paciente pa(id, gravedad);
                    uci.insertar(pa, p);
                }
            }
            //Si la uci se encuentra llena(Paciente más sano de UCI pasa a planta si se puede)
            else{
                if(gravedad < uci.elemento(uci.primera()).gravedad){
                    //Guardamos la struct del paciente antes de eliminarlo
                    paciente paciente = uci.elemento(uci.primera());
                    //Sacamos de la uci al paciente más sano
                    uci.eliminar(uci.primera());
                    //Metemos al nuevo paciente en la uci
                    pos p = uci.primera();
                    while(p != uci.fin()){
                        if(gravedad >= uci.elemento(p).gravedad){
                            paciente pa(id, gravedad);
                            uci.insertar(pa, p);
                            break;
                        }
                        p = uci.siguiente(p);
                    }
                    if(p == uci.fin()){
                        paciente pa(id, gravedad);
                        uci.insertar(pa, p);
                    }

                    //Una vez metido al nuevo paciente, tenemos que mirar si el paciente más sano que eliminamos anteriormente cabe en planta
                    //Si cabe en la planta
                    if(planta.tama() < capacidad_planta){
                        pos p = planta.primera();
                        while(p != planta.fin()){
                            if(paciente.gravedad >= planta.elemento(p).gravedad){
                                planta.insertar(paciente, p);
                                break;
                            }
                            p = planta.siguiente(p);
                        }
                        if(p == planta.fin()){
                            planta.insertar(paciente, p);
                        }
                    }
                    //Si no cabe, se repite el proceso anterior de dar de alta al más sano de la planta para que quepa este
                    else{
                        if(gravedad < planta.elemento(planta.primera()).gravedad){
                            //Damos de alta al paciente mas sano
                            alta(planta.elemento(planta.primera()).id);
                            //Insertamos al paciente por orden de gravedad (9, 8, 7, 7, 6 ...)
                            pos p = planta.primera();
                            while(p != planta.fin()){
                                if(paciente.gravedad >= planta.elemento(p).gravedad){
                                    planta.insertar(paciente, p);
                                    break;
                                }
                                p = planta.siguiente(p);
                            }
                            if(p == planta.fin()){
                                planta.insertar(paciente, p);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Hospital::alta(size_t id){
    //Primero nos aseguramos que el paciente se encuentre en el hospital
    assert(existe_paciente(id_paciente));

    //Buscamos la posición del paciente
    //Primero en la planta
    pos pp = planta.primera();
    while(pp != planta.fin()){
        if(id == planta.elemento(pp).id){
            planta.eliminar(pp);
            break;
        }
        pp = planta.siguiente(pp);
    }
    if(pp == planta.fin()){ //Si planta es igual a fin quiere decir que no estaba en planta, buscamos en uci
       pos pu = uci.primera();
        while(pu != uci.fin()){
            if(id == uci.elemento(pu).id){
                uci.eliminar(pp);
                break;
            }
            pu = uci.siguiente(pu);
        }

        //Si se ha ido alguien de UCI, quiere decir que hay un hueco, por lo cual miramos si hay alguien de planta con gravedad uci para subirlo
        //Si evidentemento lo hay, lo metemos en la uci de nuevo
        if(planta.elemento(planta.anterior(planta.fin())).gravedad >= 5 && planta.elemento(planta.anterior(planta.fin())).gravedad <= 1){
            paciente paciente = planta.elemento(planta.anterior(planta.fin()));
            planta.eliminar(planta.anterior(planta.fin()));
            //Insertamos al paciente por orden de gravedad (5, 5, 4, 3, 1 ...)
            pos p = uci.primera();
            while(p != uci.fin()){
                if(gravedad >= uci.elemento(p).gravedad){
                    uci.insertar(paciente, p);
                    break;
                }
                p = uci.siguiente(p);
            }
            if(p == uci.fin()){
                uci.insertar(paciente, p);
            }
        }
    }


}

//Para mi, muerte consiste en buscar aquellos pacientes que hayan muerto, es decir, tengan gravedad 0 y eliminarlos del hospital
void Hospital::muerte(){
    pos pp = planta.primera();
    while(pp != planta.fin()){
        if(planta.elemento(pp).gravedad == 0){
            planta.eliminar(pp);
        }
        pp = planta.siguiente(pp);
    }

    pos pu = uci.primera();
    while(pu != uci.fin()){
        if(uci.elemento(pu).gravedad == 0){
            uci.eliminar(pp);
        }
        pu = uci.siguiente(pu);
    }

    //Si al terminar de eliminar a los muertos, quedan huecos en uci, comprobamos si hay pacientes de uci en planta
    if(uci.tama() < capacidad_uci){
        pacientes_pueden_subir = capacidad_uci - uci.tama(); // Si la uci tiene 3 y al cap_maxima es 5, podrian subir 2 en caso de que los hubiera
        while(pacientes_pueden_subir != 0){
            if(planta.elemento(planta.anterior(planta.fin())).gravedad >= 5 && planta.elemento(planta.anterior(planta.fin())).gravedad <= 1){
                paciente paciente = planta.elemento(planta.anterior(planta.fin()));
                planta.eliminar(planta.anterior(planta.fin()));
                //Insertamos al paciente por orden de gravedad (5, 5, 4, 3, 1 ...)
                pos p = uci.primera();
                while(p != uci.fin()){
                    if(gravedad >= uci.elemento(p).gravedad){
                        uci.insertar(paciente, p);
                        break;
                    }
                    p = uci.siguiente(p);
                }
                if(p == uci.fin()){
                    uci.insertar(paciente, p);
                }
                pacientes_pueden_subir--;
            }
            else{
                break;
            }
        }
    }
}

size_t Hospital::pacientes_uci() const{
    return uci.tama();
}

size_t Hospital::pacientes_planta() const{
    return planta.tama();
}

size_t Hospital::gravedad_determinada(size_t gravedad) const{
    size_t contador=0;

    //Si la gravedad que nos dan es gravedad planta, solo buscamos ahí pq no pueden estar en uci
    if(gravedad >= 6 && gravedad <= 9){
        pos pp = planta.primera();
        while(pp != planta.fin()){
            if(gravedad == planta.elemento(pp).gravedad){
                contador++;
            }
            pp = planta.siguiente(pp);
        }
    }
    //Si la gravedad es de UCI, miramos en ambas plantas, ya que se puede dar el caso de que estén en ambas plantas
    else if(gravedad >= 1 && gravedad <= 5){
        pos pp = planta.primera();
        while(pp != planta.fin()){
            if(gravedad == planta.elemento(pp).gravedad){
                contador++;
            }
            pp = planta.siguiente(pp);
        }

        pos pu = uci.primera();
        while(pu != uci.fin()){
            if(gravedad == uci.elemento(pu).gravedad){
                contador++;
            }
            pu = uci.siguiente(pu);
        }
    }

    return contador;
}



//TAD TEXTO 
/*Diseña la estructura de datos para almacenar en memoria un texto del cual desconocemos el número de
líneas y de caracteres por línea. Sabemos que el texto solo consta de caracteres alfanuméricos y signos de
puntuación, es decir, en él no aparecen caracteres de control como fin de línea, retorno de carro...
Sin embargo, hay caracteres especiales que pueden aparecer un número indeterminado de veces.
@ indica el borrado del carácter anterior. En caso de que aparezca varios consecutivos, solo tiene efecto
el primero; el resto, aunque se almacene, se ignora. Este carácter no aparece al principio de ninguna línea.
#indica el borrado de la línea completa. Si aparecen varias igual, solo aparecerá al final de la línea.
Escribe una función MostrarTexto().
Al realizar este volcado de pantalla no te preocupes por el número de caracteres ni de líneas.*/
struct linea{
    Lista<char> caracteres;
    Lista<char>::posicion pos2;
};

class Texto{
    public: 
        MostrarTexto();
    private:
        Lista<linea> lineas;
        Lista<linea>::posicion pos;
};

void Texto::MostrarTexto(){
    pos p = lienas.primera();
    while(p != lineas.fin()){
        pos2 p2 = caracteres.fin()
        while(p2 != lineas.elemento(p).caracteres.primera()){
            if(lineas.elemento(p).caracteres.elemento(p2) == '@'){
                lineas.elemento(p).caracteres.eliminar(lineas.elemento(p).caracteres.anterior(p2));
            }else if(lineas.elemento(p).caracteres.elemento(p2) == '#'){
                Lista<char> l();
                lineas.elemento(p).caracteres = l;
            }
            p2 = lineas.elemento(p).caracteres.siguiente(p2);
        }
        p = lineas.siguiente(p);
    }
}


//TAD HIPERMERCADO------------------------------------------------------------------------------------------------------------------------------------------------------
// Un hipermercado dispone para el pago de las compras de 50 cajas numeradas del 1 al 50. El número de cajas que permanecen abiertas
// a lo largo del dia es variable, de tal forma que en cada momento hay entre 10 y 50 cajas en funcionamiento, dependiendo de la
// afliuencia de clientes (en las horas y fechas puntas hay más cajas abiertas que en momentos de menor clientela), aunque la media
// de cajas abiertas es de 48. El horario de venta se cubre con dos turnos de trabajo al día y en cada turno se supone que hay
// suficientes cajeros para atender la demanda máxima que se pueda producir y además algunos suplentes para sustituir a los que
// necesiten descansar. Para cada caja hay que almacenar el número de caja, el identificador del cajero(3 digitos) y la facturacion
// realizada desde el comiezo del turno de trabajo.
/* a) Escribe la especificación del TAD LíneaCajas con las siguientes operaciones:

	- Crear una linea de cajas cerradas
	- Abrir una caja determianda
	- Cerrar una caja determianda y devolver la facturación realizada en ella desde la última vez que se abrió
	- Cobrar a un cliente el importe de su compra en una caja
	- Sustituir al cajero de una caja determianda. La caja continua funcionandio
	- Cambiar el turno de trabajo y devolver la recaudación total que hay en las cajas en el momento del cambio.
	  En esta operación puede que el total de cajas, así como las cajas concretas de uno y otro turno no coincidan
	- Cerrar todas las cajas y devolver la recaudacion toral que hay en ellas en el momento del cierre

b) Realiza el TAD teniendo en cuenta lo siguiente:
	
	- El tiempo de ejecución de cerrar una caja, cobrar una compra y susituir a un cajero debe de ser constante
	- Justifica razonadamente la estructura de datos elegida en términos de eficiencia en tiempo y espacio*/

struct caja{
    int idCajero;
    double facturacionDesdeAbrir;
    double facturacionCambioTurno;
    double facturacionTotal;
    bool abierta;
    caja(int i = 0, double f1 = 0.0, double f2 = 0.0, double f3 = 0.0, bool b = false):idCajero(i),facturacionDesdeAbrir(f1), facturacionCambioTurno(f2), facturacionTotal(f3), abierta(b){}
};

class Hipermercado{
    public:
        Hipermercado();
        void abirCaja(size_t i, int idCajero);
        double cerrarCaja(size_t i);
        void cobrarCliente(size_t i, double importe);
        void sustituirCajero(size_t i, int idCajero);
        double cambiarTurno();
        double cerrarTodasCajas();
    private:
        caja vector[50];
};

Hipermercado::Hipermercado(){
    for(size_t i = 0; i < 50 ; i++){
        vector[i] = caja();
    }
}

void Hipermercado::abrirCaja(size_t i, int idCajero){
    assert(i < 50 && i >= 0 && !vector[i].abierta);
    assert(idCajero > 0 && idCajero < 1000);
    vector[i].abierta = true;
    vector[i].idCajero = idCajero;
}

double Hipermercado::cerrarCaja(size_t i){
   assert(i < 50 && i >= 0 && vector[i].abierta);
   double dinero = vector[i].facturacionDesdeAbrir;

   vector[i].abierta = false;
   vector[i].idCajero = 0;
   vector[i].facturacionCambioTurno += vector[i].facturacionDesdeAbrir;
   vector[i].facturacionDesdeAbrir = 0;

   return dinero;
}


void Hipermercado::cobrarCliente(size_t i, double importe){
    assert(i < 50 && i >= 0 && !vector[i].abierta);
    assert(importe > 0);

    vector[i].facturacionDesdeAbrir += importe;
}


void Hipermercado::sustituirCajero(size_t i, int idCajero){
    assert(i < 50 && i >= 0 && vector[i].abierta);
    assert(idCajero > 0 && idCajero < 1000);

    vector[i].idCajero = idCajero;
}

double Hipermercado::cambiarTurno(){
    double dineroCajas = 0;

    for(size_t i = 0; i < 50 ; i++){
        if(vector[i].abierta()){
            double dinero = cerrarCaja[i];
            dineroCajas += vector[i].facturacionCambioTurno;
            vector[i].facturacionTotal += vector[i].facturacionCambioTurno;
            vector[i].facturacionCambioTurno = 0;
        }
    }
    return dineroCajas;
}

double cerrarTodasCajas(){
    double dineroCajas = 0;

    for(size_t i = 0; i < 50 ; i++){
        if(vector[i].abierta()){
            double dinero = cerrarCaja[i];
            vector[i].facturacionTotal += vector[i].facturacionCambioTurno;
            dineroCajas += vector[i].facturacionTotal;
            vector[i].facturacionCambioTurno = 0;
            vector[i].facturacionTotal = 0;
        }
    }
    return dineroCajas;
}




//TAD SIMBOLO------------------------------------------------------------------------------------------------------------------------------------------------------------
/*El TAD símbolo se usa para representar símbolos trazados con líneas rectas. Un símbolo es una sucesión de
Trazos, un trazo es una línea recta con sentido arriba, abajo, izquierda y derecha. El TAD símbolo se tiene
que permitir realizar las siguientes operaciones:
- Crear un símbolo vacío.
- Añadir un trazo al final de un símbolo.
- Deshacer los últimos n trazos.
- Devolver símbolo con simetría X (Volteado Vertical)
- Devolver símbolo con simetría Y (Volteado Horizontal)
- Devolver símbolo con simetría XY
a) Realice la especificación del TAD
b) Diseñe una estructura de datos adecuada para representar el TAD e implemente las operaciones
anteriores.
NOTA: Es absolutamente necesario definir todos los tipos de datos implicados en la resolución del ejercicio,
así como los prototipos de las operaciones utilizadas de los TADs conocidos.*/
//a)Especificaion
class Simbolo{
    public:
        Simbolo();
        void anadirTrazo(char t);
        void deshacerTrazos(size_t N);
        void simetriaX();
        void simetriaXY();
        void simetriaY();

    private:
        Lista<char> lista;
        Lista<char>::posicion pos;
};

Simbolo::Simbolo():lista(Lista<char>()){}

void Simbolo::anadirTrazo(char t){
    lista.insertar(t, lista.fin());
}

void Simbolo::deshacerTrazos(size_t N){
    for(int i = 0; i < N; i++){
        lista.eliminar(lista.anterior(lista.fin()));
    }
}

void Simbolo::simetriaX(){
    for(pos p = lista.primera(); p != lista.fin(); p = lista.siguiente(p)){
        char aux = lista.elemento(p);
        if(aux == 'A'){
            lista.elemento(p) = 'B';
        }else if(aux == 'B'){
            lista.elemento(p) = 'A';
        }
    }
}

void Simbolo::simetriaY(){
    for(pos p = lista.primera(); p != lista.fin(); p = lista.siguiente(p)){
        char aux = lista.elemento(p);
        if(aux == 'I'){
            lista.elemento(p) = 'D';
        }else if(aux == 'D'){
            lista.elemento(p) = 'I';
        }
    }
}


void Simbolo::simetriaXY(){
    for(pos p = lista.primera(); p != lista.fin(); p = lista.siguiente(p)){
        char aux = lista.elemento(p);
        if(aux == 'A'){
            lista.elemento(p) = 'B';
        }else if(aux == 'B'){
            lista.elemento(p) = 'A';
        }else if(aux == 'I'){
            lista.elemento(p) = 'D';
        }else if(aux == 'D'){
            lista.elemento(p) = 'I';
        }
    }
}

//TAD CARTELERAS--------------------------------------------------------------------------------------------------------------------------------------------------------
/*Se desea un TAD para carteleras de espectáculos, que representen un sistema informático con información relativa a los
    espectáculos ofrecidos al público por una serie de salas. Cada sala puede ofrecer varios espectáculos. El TAD debe
    contener las siguientes operaciones:
        - Crear una cartelera vacía.
        - Añadir una sala a la cartelera (esta no se modifica si la sala ya existía).
        - Añadir un espectáculo a la oferta de una sala ya existente (el sistema no se modifica si la sala ya ofrecía ese espectáculo).
        - Eliminar una sala, junto con sus espectáculos (el sistema no se modifica si la sala no existía).
        - Eliminar un espectáculo de una sala (el sistema no se modifica si la sala no existía o sí existía pero no ofrecía ese espectáculo).
        - Consultar las salas.
        - Consultar los espectáculos de una sala.*/
//b) y a)
struct sala{
    string id;
    Lista<string> espectaculos;
    sala(string idSala):id(idSala), espectaculos(Lista<string>()){}
};

class Cartelera{
    public:
        Cartelera():salas(Lista<sala>()){}
        void anadirSala(string idSala);
        void anadirEspectaculo(string idSala, string idEspectaculo);
        void eliminarSala(string idSala);
        void eliminarEspectaculo(string idSala, string idEspectaculo);
        Lista<sala> consultarSalas() const;
        Lista<string> consultarEspectaculos(string idSala) const;
    private:
        Lista<sala> salas;
        typedef typename Lista<sala>::posicion posSala;
        typedef typename Lista<string>::posicion posEspectaculo;
        posSala busquedaSala(string idSala);
        posEspectaculo busquedaEspectaculo(posSala p, string idEspectaculo);
};

Cartelera::posSala Cartelera::busquedaSala(string idSala){
    posSala p = salas.primera();
    while(p != salas.fin()){
        if(salas.elemento(p).id >= idSala)
            return p;
        else
            p = salas.siguiente(p);
    }
    return p;
}

Cartelera::posEspectaculo Cartelera::busquedaEspectaculo(posSala p, string idEspectaculo){
    if(p != salas.fin()){
        posEspectaculo p2 = salas.elemento(p).espectaculos.primera();
        while(p2 != salas.elemento(p).espectaculos.fin()){
            if(salas.elemento(p).espectaculos.elemento(p2) >= idEspectaculo)
                return p2;
            else
                p2 = salas.elemento(p).espectaculos.siguiente(p2);
        }
        return p2;
    }
}



//pre: sala no se encuentre en la cartelera
void Cartelera::anadirSala(string idSala){
    sala s(idSala);
    posSala p = busquedaSala(idSala);
    //no existe
    if(p == salas.fin())
        salas.insertar(s,p);
    else if(salas.elemento(p).id != idSala)
        salas.insertar(s,p);
    
}

void Cartelera::anadirEspectaculo(string idSala, string idEspectaculo){
    posSala p = busquedaSala(idSala);
    if(p != salas.fin() && salas.elemento(p).id == idSala){
        posEspectaculo p2 = busquedaEspectaculo(p, idEspectaculo);
        //existe sala y no especatculo
        if(p2 != salas.elemento(p).espectaculos.fin() && salas.elemento(p).espectaculos.elemento(p2) != idEspectaculo){
            salas.elemento(p).espectaculos.insertar(idEspectaculo, p2);
        }else{
            salas.elemento(p).espectaculos.insertar(idEspectaculo, p2);
        }
    }
}


void Cartelera::eliminarSala(string idSala){
    posSala p = busquedaSala(idSala);
    if(p != salas.fin() && salas.elemento(p).id == idSala){
        salas.eliminar(p);
    }
}

void Cartelera::eliminarEspectaculo(string idSala, string idEspectaculo){
    posSala p = busquedaSala(idSala);
    if(p != salas.fin() && salas.elemento(p).id == idSala){
        posEspectaculo p2 = busquedaEspectaculo(p,idEspectaculo);
        if(p2 != salas.elemento(p).espectaculos.fin() && salas.elemento(p).espectaculos.elemento(p2) == idEspectaculo)
            salas.elemento(p).espectaculos.eliminar(p2);
    }
}

Lista<sala> Cartelera::consultarSalas() const{
    return salas;
}


Lista<string> Cartelera::consultarEspectaculos(string idSala) const{
    posSala p = busquedaSala(idSala);
    if(p != salas.fin() && salas.elemento(p).id == idSala){
        return salas.elemento(p).espectaculos;
    }
}





//TAD COCINA------------------------------------------------------------------------------------------------------------------------------------------------------------
// Una empresa de muebles de cocina necesita un TAD para representar el conjunto de muebles
//colocados en la pared de una cocina. Una cocina se crea con una longitud positiva
// y un mueble colocado en la pared se identifica por el par formado por su posicion
// y su anchura. La posicion es la distancia desde su lateral izquierdo al extremo derecho 
//de la pared
// El tad debe soportar las siguiente operaciones
// -crear una cocina vacia con una longitud dada
//- determinar si un mueble de una cierta anchura puede colocarse en una posicion dada
// - añadir un mueble de una determinada longitud a una posicion dada
// - devolver el mueble inésimo de la cocina empezando a contar por la izquierda
// - eliminar el mueble enesimo de la cocina si existe
// - mover el mueble inesimo de la cocina si existe hacia la izquierda hasta que se junte 
//      con el mueble i-1 esimo o el extremo izquierdo de la pared
//- destruir la cocina

struct mueble{
    double anchura;
    double posicion;
};

class Cocina{
    public:
        Cocina(double l);
        bool determinarColocacion(double anchura, double posicion);
        void anadirMueble(double anchura, double posicion);
        mueble muebleInesimo(size_t i);
        void eliminarInesimo(size_t i);
        void moverMueble(size_t i);
        ~Cocina();

    private:
        double longitud;
        Lista<mueble> muebles;
        typedef typename  Lista<mueble>::posicion pos;
};

Cocina::Cocina(double l):longitud(l){}

bool Cocina::determinarColocacion(double anchura, double posicion){
    assert(posicion - anchura >= 0 && posicion <= longitud);
    pos p = muebles.primera();
    //antes del primer mueble
    if(posicion-anchura>=mueble.elemento(p).posicion){
        return true;
    }else{
        while(p!=mueble.fin()){
            if(mueble.elemento(p).posicion - mueble.elemento(p).anchura >= posicion - anchura >= mueble.elemento(p.siguiente()).posicion){
                return true;
            }
        }
        if(mueble.elemento(p).posicion - mueble.elemento(p).anchura >= posicion - anchura >= 0){
            return true;
        }else{
            return false;
        }
    }
}

void anadirMueble(double anchura, double posicion){
    assert(determinarColocacion(anchura,posicion));
    mueble m(anchura, posicion);
    pos p = muebles.primera();
    while(p!=mueble.fin()){
        if(mueble.elemento(p).posicion < posicion){
            muebles.insertar(m,p);
            break;
        }
        p = muebles.siguiente(p);
    }
}

mueble muebleInesimo(size_t i){
    size_t cont = 0;
    pos p = muebles.primera();
    while(p!=mueble.fin()){
        if(cont == i){
            return muebles.elemento();
        }
        p = muebles.siguiente(p);
        cont++;
    }
}

void eliminarInesimo(size_t i){
    size_t cont = 0;
    pos p = muebles.primera();
    while(p!=mueble.fin()){
        if(cont == i){
            muebles.eliminar(p);
        }
        p = muebles.siguiente(p);
        cont++;
    }
}

void moverMueble(size_t i){
    size_t cont = 0;
    pos p = muebles.primera();
    while(p!=mueble.fin()){
        if(cont == i){
            break;
        }
        p = muebles.siguiente(p);
        cont++;
    }
    if(cont == 1){
        muebles.elemento(p).posicion = longitud;
    }else{
        muebles.elemento(p).posicion = muebles.elemento(muebles.anterior(p)).posicion - muebles.elemento(muebles.anterior(p)).anchura;
    }
}


//TAD ESCALONADA---------------------------------------------------------------------------------------------------------------------------------------------------------
/*Una función f:R->R es escalonada cuando consiste en una sucesión de funciones constantes definidas en
subintervalos disjuntos y contiguos, es decir, f puede definirse mediante condiciones de la forma f(x)=yi, si
x¡<=z<xi+1, donde los valores yi; son distintos para subintervalos adyacentes. Cada uno de los puntos (xi, yi)
en los que la función cambia de valor se llama salto o escalón.
(40%) Especificar un TAD para las funciones escalonadas con un numero finito de saltos, que incluya las
siguientes operaciones:
- Crear una función constante f(x)=yi, definida a partir de xi
- Añadir un nuevo saltos en el punto (x,y) a una función. Si ya existe un salto en las coordenadas x, se
sustituye por el nuevo.
- Eliminar el escalón definido en el subintervalo al que pertenece la coordenada x. El escalón anterior al
eliminado se prolonga hasta el siguiente.
- Calcular el valor de una función en un punto dado.
- Calcular el valor mínimo de una función escalonada
- Calcular el valor máximo de una función escalonada
- Hacer una translación de una función w unidades horizontales y z unidades verticales, siendo w y z
números reales.
- Destruir una función */

struct salto{
    double x,y;
};

class Escalonada{
    public:
        Escalonada(double c1, double c2);
        void anadirSalto(double c1, double c2);
        void eleminarSalto(double c1);
        double valor(double c1);
        double valorMin();
        double valorMax();
        void translacion(double w, double z);
        ~Escalonada();

    private:
        Lista<salto> funcion;
        typedef typename Lista<salto>::posicion pos;
}

pos buscar(double c1){
    pos p = funcion.primera();
    while(p != funcion.fin()){
        if(c1 == funcion.elemento(p).x){
            return p;
        }
        p = funcion.siguiente(p);
    }
    return p;
}


Escalonada::Escalonada(double c1, double c2){
    salto s(c1,c2);
    funcion.insertar(s, funcion.fin());
}

void Escalonada::anadirSalto(double c1, double c2){
    salta s(c1,c2);
    pos p = funcion.primera();
    while(p != funcion.fin()){
        if(c1 == funcion.elemento(p).x){
            funcion.elemento(p).y = c2;
        }else{
            if(s.c1 < funcion.elemento(p).x)
                funcion.insertar(s,p);
                break;
        }
        p = funcion.siguiente(p);
    }
    if(p == funcion.fin()){
        funcion.insertar(s,fin);
    }
}

void Escalonada::eleminarSalto(double c1){
    pos p = funcion.primera();
    while(p != funcion.fin()){
        if(c1 == funcion.elemento(p).x){
            funcion.eleminar(p);
        }
        p = funcion.siguiente(p);
    }
}

double Escalonada::valor(double c1){
    assert(buscar(c1) != funcion.fin());
    return funcion.elemento(p);
}

double Escalonada::valorMin(){
    pos p = funcion.primera();
    double min = funcion.elemento(p).y;
    while(p != funcion.fin()){
        if(funcion.elemento(p).y < min){
            min = funcion.elemento(p).y;
        }
        p = funcion.siguiente(p);
    }
    return min;
}

double Escalonada::valorMax(){
    pos p = funcion.primera();
    double max = funcion.elemento(p).y;
    while(p != funcion.fin()){
        if(funcion.elemento(p).y > max){
            max = funcion.elemento(p).y;
        }
        p = funcion.siguiente(p);
    }
    return max;
}

void Escalonada::translacion(double w, double z){
    pos p = funcion.primera();
    while(p != funcion.fin()){
        funcion.elemento(p).x *= w;
        funcion.elemento(p).y *= z;
        p = funcion.siguiente(p);
    }
}

//TAD RADIO
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



//TAD GESTOR IMPRESION-----------------------------------------------------------------------------------------------------------------------------------------------
//En una oficina tienen una impresora que sirve a distintos usuarios, cada uno de los cuales puede 
//enviar a la misma dos clases de trabajos, urgentes y no urgentes. Los trabajos de la misma clase
//de un usuario concreto serán procesados por orden de llegada y siempre los urgentes antes que 
//los que no lo sean. Asumiremos que los trabajos se identifican mediante un código único de tipo string.
//La impresora atiende a los usuarios por turnos, de forma que al que le llega el turno imprime tan 
//sólo uno de sus trabajos, a continuación, pasa el turno al siguiente usuario en espera y, si tiene 
//trabajos pendientes, esperará a que le vuelva a llegar el turno después de que lo reciban todos 
//los usuarios que ya estén esperando. Cuando un usuario envía su primer trabajo de impresión se 
//le asigna el turno que sigue al del último en espera con trabajos pendientes. Un usuario pierde su 
//turno al terminar de imprimir todos sus trabajos y se le asignará otro turno la próxima vez que solicite imprimir un nuevo trabajo.

// a)	Especifica las siguientes operaciones del TAD Gestor de Impresión:
//      •	Crear un gestor de impresión para n usuarios.
//      •	Añadir un trabajo de un usuario y de una urgencia determinada.
//      •	Eliminar el trabajo a imprimir
//      •	Cancelar todos los trabajos de un usuario
// b)	Implementa el TAD Gestor de Impresión según la especificación del apartado anterior, justificando razonadamente la estructura de datos empleada
using namespace std;

struct usuario{
    Cola<string> cUrgente;
    Cola<string> cNoUrgente;
};

class Gestor{
    public:
        Gestor(size_t n);
        void anadirTrabajo(size_t i, bool urgencia);
        void imprimirTrabajo();
        void cancelarTrabajos(size_t i);
    private:
        vector<usuario> vector;
        Cola<size_t> cola;
};

GestorImpresion::GestorImpresion(size_t n):vector(n), cola(n) { }

//Usamos el TAD Cola con implementacion pseudoestatica en la principal, dinamica para las de trbajo y un vector de la stl al tener que saber el tam en tipo de ejecucion

void anadirTrabajo(size_t i, bool urgencia, string trabajo){
    assert(i >= 0 && i < vector.size());
    //tenia trabajo antes -> no se mete a cola prinicipal
    if(vector[i].cUrgente.tama() > 0 || vector[i].cNoUrgente.tam() > 0){
        if(urgencia)
            vector[i].cUrgente.push(trabajo);
        else
            vector[i].cNoUrgente.push(trabajo);
    }
    //no tenia ningun trbajo-> se mete a cola principal
    else{
        if(urgencia)
            vector[i].cUrgente.push(trabajo);
        else
            vector[i].cnoUrgente.push(trabajo);
        cola.push(i);
    }
}

void Gestor::imprimirTrabajo(){
    if(cola.frente().cUrgente.tama() > 0)
        cola.frente().cUrgente.pop();
    else
        cola.frente().cNoUrgente.pop();
        
    if(cola.frente().cUrgente.tama() == 0 && cola.frente().cNoUrgente.tama() == 0)
        cola.pop();
    else
        cola.push(cola.frente());
        cola.pop();
}

void cancelarTrabajos(size_t i){
    assert(i >= 0 && i < vector.size());
    //en caso de que tuviese algun trabajo, es decir, estas en la cola princiapal
    if(cola.frente().cUrgente.tama() > 0 && cola.frente().cNoUrgente.tama() > 0){
        vector[i].cUrgente = cola<string> cUrgente();
        vector[i].cNoUrgente = cola<string> cNoUrgente();
        
        Cola<size_t> cAux;
        while(!cola.vacia()){
            if(cola.frente() == i){
                cola.pop();
            }
            cAux.push(cola.frente());
        }
        cola = cAux;
    }
}


//TAD AVERIA--------------------------------------------------------------------------------------------------------------------------------------------------------
/*
La compañia aerea Averias SA necesita un sistema de reservas con las siguientes operaciones:
- crear un sistema de reservas vacio, sin informacion
- añadir un nuevo vuelo al sistema de reservas
- comprobar si un vuelo existe o no en el sistema
- registrar una reserva para un pasajero en un vuelo existente con la condicion,
    de que un mismo pasajero no mas de una reserva en el mismo vuelo.
- comprobar si un vuelo ya no admite mas reservas
- determinar el numero del asiento, que le asigna a un pasajero en un vuelo, suponiendo que tal asignacion se realiza por orden de reserva,
    empezabndo por el uno, y devolviendo 0 para los pasajero sin reserva
- calcular el numero de reservas que hay en un vuelo
- anular un vuelo en un sistema de reserva, eliminando todas las posibles reservas que haya para ese vuelo
- obtener una lista de todos los vuelos en orden de salida
*/

struct reserva{
    string nombrePasajero;
    string numAsiento;
};

struct vuelo{
    string id;
    string horaSalida;
    string numMaxReservas;
    Lista<reserva> reservas;
    typedef typename::posicion pos2;
    vuelo(string i, string h, string n):id(i),horaSalida(h),numMaxReservas(n){}
};

class Averia{
    public: 
        Averia();
        void anadirVuelo(string idVuelo, string horaSalida, size_t numReservas);
        bool comprobarVuelo(string idVuelo);
        void registrarReserva(string idVuelo, string idPasajero);
        bool comprobarMasReservas(string idVuelo);
        string numAsientoPasajero(string idVuelo, string idPasajero);
        size_t calculaNumReservas(string idVuelo);
        void anularVuelo(string idVuelo);
        Lista<vuelo> MostrarVuelos();

    private:
        Lista<vuelo> vuelos;
        typedef typename Lista<vuelo>::posicion pos;
}

Averia::Averia(){}

bool Averia::comprobarVuelo(string idVuelo){
    if(busquedaPosId(idVuelo) == vuelos.fin())
        return false;
    else
        return true;
}

pos Averia::busqueda(string horaSalida){
    os p = vuelos.primera();
    while(p != vuelos.fin()){
        if(horaSalida <= vuelos.elemento(p).horaSalida)
            return p;
        else
            p = vuelos.siguiente(p);
    }
    return p;
}

pos Averia::busquedaPosId(string id){
    pos p = vuelos.primera();
    while(p != vuelos.fin()){
        if(id == vuelos.elemento(p).id)
            return p;
        else
            p = vuelos.siguiente(p);
    }
    return p;
}


void Averia::anadirVuelo(string idVuelo, string horaSalida, size_t numReservasMax){
 
    assert(!comprobarVuelo(idVuelo));
    aasert(numReservasMax > 0 );
    pos p = busquedaPos(horaSalida);
    vuelo v(idVuelo, horaSalida, numReservasMax);
    vuelos.insertar(v,p);
    
}

void Averia::registrarReserva(string idVuelo, string idPasajero){
    assert(comprobarVuelo(idVuelo));
    //el vuelo existe y obtenemso su posicion
    pos p = busquedaPosId(idVuelo);
    pos2 p2 = vuelos.elemento(p).reservas.primera();
    bool reservaEncontrada = false;
    while(p2 != vuelos.elemento(p).reservas.fin()){
        if(vuelos.elemento(p).reservas.elemento(p2).nombrePasajero == idPasajero){
            reservaEncontrada = true;
        }
        p2 = vuelos.elemento(p).reservas.siguiente(p2);
    }

    assert(!reservaEncontrada);
    assert(comprobarMasReservas(idVuelo));
    reserva r(nombrePasajero, vuelos.elemento(p).reservas.tam()+1);
    vuelos.elemento(p).reservas.insertar(r,p2);
}

bool comprobarMasReservas(string idVuelo){
    assert(comprobarVuelo(idVuelo));
    pos p = busquedaPosId(idVuelo);
    if(vuelos.elemento(p).reservas.tama() < vuelos.elemento(p).numMaxReservas)
        return true;
    else
        return false;
}

string numAsientoPasajero(string idVuelo, string idPasajero){
    assert(comprobarVuelo(idVuelo));
    pos p = busquedaPosId(idVuelo);
    pos2 p2 = vuelos.elemento(p).reservas.primera();
    while(p2 != vuelos.elemento(p).reservas.fin()){
        if(vuelos.elemento(p).reservas.elemento(p2).nombrePasajero == idPasajero){
            return vuelos.elemento(p).reservas.elemento(p2).numAsiento;
        }
        p2 = vuelos.elemento(p).reservas.elemento(p2).siguiente(p2);
    }
    return 0;
}

size_t calculaNumReservas(string idVuelo){
    assert(comprobarVuelo(idVuelo));
    pos p = busquedaPosId(idVuelo);
    return vuelos.elemento(p).reservas.tama();
}

void anularVuelo(string idVuelo){
    assert(comprobarVuelo(idVuelo));
    pos p = busquedaPosId(idVuelo);
    vuelos.eliminar(p);
}


Lista<vuelo> MostrarVuelos(){
    return vuelos;
}




//TAD ALMACEN
/*Una empresa ha robotizado su almacén. Para ello lo ha dividido en 60 estantes de tres tamaños diferentes (pequeño, mediano y grande) 
a partes iguales. A cada estante se le asigna un elemento según su tamaño (en cada estante solo hay elementos de un tipo, pero puede 
haber hasta 50 elementos del mismo tipo).
Se pide diseñar un TAD para el funcionamiento del robot que incluya las siguientes operaciones:
    1. Crear un almacén vacío.
    2. Insertar un elemento en un estante. Si ya hay un estante asignado, y el elemento cabe, se coloca en ese. Si no es así, 
    se busca otro estante del mismo tamaño. Si no hay, se devuelve False. Si se puede colocar se devuelve True.
    3. Comprobar si hay elementos de un tipo determinado.
    4. Sacar un elemento de un tipo dado.
    5. Vaciar el almacén (destructor del TAD).
*/

//0 -> small
//1 -> medium
//2 -> big

//0-19 => small
//20-39 => medium
//40-59 => big 

struct estante{
    size_t tipoTamanoEstanteria;
    size_t numMaximo = 50;
    size_t numActual;
};
class Almacen{
    public:
        Almacen();
        bool insertarElementoEstante(size_t tamanoElemento);
        bool comprobarElementoTamano(size_t tamanoElemento);
        void sacarElemento(size_t tamanoElemento);
        ~Almacen();
    private:
        estante estanterias[60];
};
//pila -> pseudoestática
Almacen::Alamacen(){
    for(size_t i = 0 ; i < 60 ; i++){
        if(i <= 19){
            estanterias[i].tipoTamanoEstanteria = 0;
        }else if(i <= 39 &&  i>= 20){
            estanterias[i].tipoTamanoEstanteria = 1;
            
        }else{
            estanterias[i].tipoTamanoEstanteria = 2;
        }
        estanterias[i].numActual = 0;
    }
}


bool Almacen::insertarElementoEstante(size_t tamanoElemento){
    bool sePuede = false;
    size_t rango1 = 0;
    size_t rango2 = 0;

    if(tamanoElemento == 0){
        rango2 = 19;
    }else if(tamanoElemento == 1){
        rango1 = 20;
        rango2 = 39;

    }else if(tamanoElemento == 2){
        rango1 = 40;
        rango2 = 59;
    }
    while(rango1 <= rango2 && !sePuede){
        if(estanterias[rango1].numActual < estanterias[rango1].numMax){
            estanterias[rango1].numActual++;
            sePuede = true;
            return sePuede;
        }
        else
            rango1++;    
    }
    return sePuede;
}


bool comprobarElementoTamano(size_t tamanoElemento){
    bool existeElemento = false;
    size_t rango1 = 0;
    size_t rango2 = 0;

    if(tamanoElemento == 0){
        rango2 = 19;
    }else if(tamanoElemento == 1){
        rango1 = 20;
        rango2 = 39;

    }else if(tamanoElemento == 2){
        rango1 = 40;
        rango2 = 59;
    }
    while(rango1 <= rango2 && !sePuede){
        if(estanterias[rango1].numActual > 0){
            sePuede = true;
            return sePuede;
        }
        else
            rango1++;    
    }
    return sePuede;
}


void sacarElemento(size_t tamanoElemento){
    size_t rango1 = 0;
    size_t rango2 = 0;

    if(tamanoElemento == 0){
        rango2 = 19;
    }else if(tamanoElemento == 1){
        rango1 = 20;
        rango2 = 39;

    }else if(tamanoElemento == 2){
        rango1 = 40;
        rango2 = 59;
    }
    while(rango1 <= rango2 && !sePuede){
        if(estanterias[rango1].numActual > 0){
            estanterias[rango1].numActual--;
        }
        else
            rango1++;    
    }
}