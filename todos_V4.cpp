#include "pilavec0.h" //Pila estatica
#include "pilavec1.h" //Pila psudoestatica
#include "pilaenla.h" //Pila dinámica

#include "colavec.h"//Cola pseudo
#include "colacir.h"//Cola vectorial circular
#include "colaenla.h"//Cola enla o dinamica
#include "colaenlacir.h"//Cola enla circular

#include "listavec.h"//Lista pseudo
#include "listaenla.h" //Lista enla
#include "listadobleenla.h" //Lista doblemente enlazada
#include "listacir.h"//Lista circular

//-----------------------------------APUNTES DE TEORIA------------------------------------------------------------------------------------------------------------------
//Pilas con bicolas
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
/*Realizar la especificación e implementación de un TAD Tren que sirva para representar secuencias (de
longitud arbitraria) de vagones (se supone que el tipo vagón está predefinido). Si la secuencia no está
vacía, hay un vagón del tren denominado “activo” sobre el que puede actuar un robot manipulador. Las
operaciones que se piden son:
- Crear un tren.
- Desplazar a la izquierda: Mueve un tren una posición a la izquierda de manera que el nuevo vagón activo
es el que está inmediatamente a la derecha del actual. Si no hay vagón a la derecha no se hace nada.
- Desplazar a la derecha: Simétrica a la anterior.
- Eliminar el vagón activo: Se suprime el vagón activo y se convierte en activo el que está inmediatamente
a su derecha. Si éste no existe, se activa el de su izquierda. Y si éste último tampoco existe, el tren queda
vacío.
- Insertar vagón activo: Añade un nuevo vagón al tren desplazando el actual Vagón activo y los siguientes
una posición hacia la derecha
- Observar el vagón activo: Una cámara fija situada sobre el robot devuelve el vagón activo.
- Tren vacío: indica si el tren tiene vagones.
Nota: Se prohíbe expresamente utilizar una estructura doblemente enlazada. Y se exige que el coste de
todas las operaciones sea constante, es decir, independiente del número de vagones del tren. Se valorará
la claridad de la especificación y la eficiencia de las operaciones
*/

//El vagon activo el de la derecha
class Tren{
    public:
        Tren(){};
        void izquierda();
        void derecha();
        void eliminar_activo();
        void insertar_activo(const vagon &v);
        vagon observar() const;
        bool vacio() const;
        ~Tren(){};
    private:
        Pila<vagon> TI, TD;
};

//Ojo con esta
void Tren::izquierda(){
    vagon aux = TD.tope();
    TD.pop();
    if(!TD.vacia()){
        TI.push(aux);
    }else{
        TD.push(aux);
    }
}

void Tren::derecha(){
    if(!TI.vacia()){
        TD.push(TI.tope());
        TI.pop();
    }
}

void Tren::eliminar_activo(){
    if(!TD.vacia()){
        TD.pop();
        if(TD.vacia() && !TI.vacia()){
            TD.push(TI.tope());
            TI.pop();
        }
    }
}

void Tren::insertar_activo(const vagon &v){
    TD.push(v);
}

vagon Tren::observar() const{
    if(!TD.vacia()){
        return TD.tope();
    }
}

bool Tren::vacio() const{
    if(!TD.vacia() || !TI.vacia()){
        return true;
    }
    else{
        return false;
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
struct usuario{
    Cola<string> CU;
    Cola<string> CNU;
};

class Impresora{
    public:
        Impresora(size_t n);
        void anadir(size_t codigo, bool urgencia, string trabajo);
        void eliminar();
        void cancelar(size_t codigo);
        ~Impresora();
    private:
        Cola<size_t> cola_impresion;
        size_t tam;
        usuario* vector_usuarios;
};

Impresora::Impresora(size_t n):tam(n), vector_usuarios(new usuario[n]){}

void Impresora::anadir(size_t codigo, bool urgencia, string trabajo){
    if(codigo < n){
        if(urgencia){
            vector_usuarios[codigo].CU.push(trabajo);
        }else{
            vector_usuarios[codigo].CNU.push(trabajo);
        }
        Cola<size_t> aux = cola_impresion;
        Cola<size_t> aux2;
        while(!aux.vacia() && aux.frente() != codigo){
            aux2.push(aux.frente());
            aux.pop();
        }
        if(aux.vacia()){
            cola_impresion.push(codigo);
        }
    }
}

void Impresora::eliminar(){
    if(!cola_impresion.vacia()){
        size_t cod = cola_impresion.frente();
        cola_impresion.pop();

        if(!vector_usuarios[cod].CU.vacia()){
            vector_usuarios[cod].CU.pop();
        }
        else{
            vector_usuarios[cod].CNU.pop();
        }
        if(!vector_usuarios[cod].CU.vacia() || !vector_usuarios[cod].CNU.vacia()){
            cola_impresion.push(cod);
        }
    }
}

void Impresora::cancelar(size_t codigo){
    Cola<size_t> aux;
    while(!cola_impresion.vacia() && cola_impresion.frente() != codigo){
        aux.push(cola_impresion.frente());
        cola_impresion.pop();
    }
    if(cola_impresion.frente() == codigo){
        cola_impresion.pop();
    }
    while(!cola_impresion.vacia()){
        aux.push(cola_impresion.frente());
        cola_impresion.pop();
    }
    cola_impresion = aux;

    vector_usuarios[codigo].CU = Cola<string>{};
    vector_usuarios[codigo].CNU = Cola<string>{};
}

Impresora::~Impresora(){
    delete[] vector_usuarios;
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

struct palabra{
    string  word;
    Lista<string> traducciones;
};

class Diccionario{
    public:
        Diccionario(){};
        void insertar(string pingles, string pespanol);
        bool consultar(string pingles, string pespanol) const;
        Lista<string> traducciones(string pingles) const;
        void eliminar(string pingles, string pespanol);
        ~Diccionario(){};
    private:
        Lista<palabra> palabras;
        typedef typename Lista<palabra>::posicion p_palabra;
        typedef typename Lista<string>::posicion p_trad;
};

void Diccionario::insertar(string pingles, string pespanol){
    p_palabra p = palabras.primera();

    while(p != palabras.fin()){
        if(palabras.elemento(p).word == pingles){
            p_trad pe = palabras.elemento(p).traducciones.primera();
            while(pe != palabras.elemento(p).traducciones.fin()){
                if(pespanol < palabras.elemento(p).traducciones.elemento(pe)){
                    palabras.elemento(p).traducciones.insertar(pespanol, pe);
                }
                pe = palabras.elemento(p).traducciones.siguiente(pe);
            }
        }
        p = palabras.siguiente(p);
    }

    p = palabras.primera();
    while(p != palabras.fin()){
        if(pingles < palabras.elemento(p).word){
            palabra p_;
            p_.word = pingles;
            p_trad pe = palabras.elemento(p).traducciones.primera();
            p_.traducciones.insertar(pespanol, pe);

            palabras.insertar(p_, p);
        }
        p = palabras.siguiente();
    }
}

bool Diccionario::consultar(string pingles, string pespanol) const{
    p_palabra pi =  palabras.primera();

    while(pi != palabras.fin()){
        if(palabras.elemento(pi) == pingles){
            p_trad pe = palabras.elemento(pi).traducciones.primera();

            while(pe != palabras.elemento(pi).traducciones.fin()){
                if(palabras.elemento(pi).traducciones.elemento(pe) == pespanol){
                    return true;
                }
                pe = palabras.elemento(pi).traducciones.siguiente(pe);
            }
        }
        pi = palabras.siguiente(pi);
    }

    return false;
}

Lista<string> Diccionario::traducciones(string pingles) const{
    p_palabra pi =  palabras.primera();

    while(pi != palabras.fin()){
        if(palabras.elemento(pi) == pingles){
           return palabras.elemento(pi).traducciones;
        }
        pi = palabras.siguiente(pi);
    }
}

void Diccionario::eliminar(string pingles, string pespanol){
    p_palabra pi =  palabras.primera();

    while(pi != palabras.fin()){
        if(palabras.elemento(pi) == pingles){
            p_trad pe = palabras.elemento(pi).traducciones.primera();

            while(pe != palabras.elemento(pi).traducciones.fin()){
                if(palabras.elemento(pi).traducciones.elemento(pe) == pespanol){
                    palabras.elemento(pi).traducciones.eliminar(pe);
                }
                pe = palabras.elemento(pi).traducciones.siguiente(pe);
            }
        }
        pi = palabras.siguiente(pi);
    }
}

//TAD CONSULTORIO DE UN MEDICO------------------------------------------------------------------------------------------------------------------------------------------
/*Especificacion:*/
/*Consultorio():
	·Precondicion:-------.
	·Postcondicion:Crea un Consultorio vacio.
*/
/*void altaMedico(const Medico& M):
	·Precondicion:Medico no debe estar dado de alta.
	·Postcondicion:Da de alta al medico.
*/
/*void bajaMedico(const Medico& M):
	·Precondicion:Medico debe estar dado de alta.
	·Postcondicion:Dar de baja al medico.
*/
/*void ponerPaciente(const Medico& M,const Paciente& P):
	·Precondicion:Medico debe estar dado de alta.
	·Postcondicion:Pone al paciente en lista de espera del medico M.
*/
/*Paciente verPaciente(const Medico& M):
	·Precondicion:Medico debe estar dado de alta y tiene al menos un paciente en lista de espera.
	·Poscondicion:Devuelve la persona que le toca.
*/
/*void atenderPaciente(const Medico& M):
	·Precondicion:Medico debe estar dado de alta y debe tener un paciente minimo.
	·Postcondicion:Se atiende al paciente que le toca, por lo que desaparece de la lista de espera.
*/
/*bool medicoVacio(const Medico& M)const:
	·Precondicion:Medico debe estar dado de alta.
	·Postcondicion:Devuelve true si medico no tiene pacientes, false en otro caso.
*/

struct medico{
    int codigo;
    Cola<int> pacientes;
};

class Consultorio{
    public:
        Consultorio(){};
        void altamedico(int medico_);
        void bajamedico(int medico_);
        void ponerpaciente(int medico_, int paciente);
        int verpaciente(int medico_) const;
        void atenderpaciente(int medico_);
        bool medicovacio(int medico_) const;
        ~Consultorio(){};
    private:
        Lista<medico> medicos;
        typedef typename Lista<medicos>::posicion p;
        p buscar(int medico_);
};

Consultorio::p Consultorio::buscar(int medico_){
    p p = medicos.primera();

    while(p != medicos.fin()){
        if(medicos.elemento(p).codigo == medico_){
            return p;
        }
        p = medicos.siguiente(p);
    }

    return p;
}

void Consultorio::altamedico(int medico_){
    medico m;
    m.codigo = medico_;
    p aux = buscar(medico_);

    assert(aux == medicos.fin());
    
    medicos.insertar(m, medicos.fin());
}

void Consultorio::bajamedico(int medico_){
    p aux = buscar(medico_);

    assert(aux != medicos.fin());

    medicos.eliminar(aux);
}

void Consultorio::ponerpaciente(int medico_, int paciente){
    p aux = buscar(medico_);

    assert(aux != medicos.fin());

    medicos.elemento(aux).pacientes.push(paciente);
}

int Consultorio::verpaciente(int medico_) const{
    p aux = buscar(medico_);

    assert(aux != medicos.fin());

    assert(!medicos.elemento(aux).pacientes.vacia());

    return medicos.elemento(aux).pacientes.frente();
}

void Consultorio::atenderpaciente(int medico_){
    p aux = buscar(medico_);
    
    assert(aux != medicos.fin());

    assert(!medicos.elemento(aux).pacientes.vacia());

    medicos.elemento(aux).pacientes.pop();
}

bool Consultorio::medicovacio(int medico_) const{
    p aux = buscar(medico_);

    assert(aux != medicos.fin());

    if(medicos.elemento(aux).pacientes.vacia()){
        return true;
    }
    else{
        return false;
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


struct computador{
    char nombre[8];
    bool token;
    trama mensaje;
};

class Token_Bus{
    public:
        Token_Bus(char nom_comp, trama msj);
        void anadir_computador(char nom_comp, trama msj);
        void eliminar_computador();
        void pasar_token();
        char token() const;
        void enviar(char comp1, char comp2);
        ~Token_Bus(){};
    private:
        static const int max;
        Cola<computador> Bus;
};

Token_Bus::Token_Bus(char nom_comp, trama msj){
    max = 25;
    computador c;
    c.nombre = nom_comp;
    c.token = true;
    c.mensaje = msj;
    
    Bus = Cola<computador>(25);
    Bus.insertar(c);
}

void Token_Bus::anadir_computador(char nom_comp, trama msj){
    assert(!Bus.llena());
    
    Cola<computador> aux = Bus;

    bool encontrado = false;

    while(!aux.vacia() && !encontrado){
        if(aux.frente == nom_comp){
            encontrado = true;
        }
        aux.pop();
    }

    if(!encontrado){
        computador c;
        c.nombre = nom_comp;
        c.token = false;
        c.mensaje = msj;

        Bus.push(c);
    }

}

void Token_Bus::eliminar_computador(){
    assert(!Bus.vacia());

    if(Bus.frente().token == true){
        Bus.pop();
        if(!Bus.vacia()){
            Bus.frente().token = true;
        }
    }else{
        Bus.pop();
    }
}

void Token_Bus::pasar_token(){
    assert(!Bus.vacia());

    Cola<computador> aux(25);

    while(!Bus.vacia() && !Bus.frente().token){
        aux.push(Bus.frente());
        Bus.pop();
    }
    if(Bus.frente().token == true){
        Bus.frente().token = false;
        aux.push(Bus.frente());
        Bus.pop();
        if(!Bus.vacia()){
            Bus.frente().token = true;
            while(!Bus.vacia()){
                aux.push(Bus.frente());
                Bus.pop();
            }
            while(!aux.vacia()){
                Bus.push(aux.frente());
                aux.pop();
            }
        }else{
            aux.frente().token = true;
            while(!aux.vacia()){
                Bus.push(aux.frente());
                aux.pop();
            }
        }
    }
    while(!aux.vacia()){
        Bus.push(aux.frente());
        aux.pop();
    }
}

char Token_Bus::token(){
    assert(!Bus.vacia());

    Cola<computador> aux(25);

    while(!Bus.vacia() && !Bus.frente().token){
        aux.push(Bus.frente());
        Bus.pop();
    }
    if(Bus.frente().token){
        return Bus.frente().nombre;
    }
}

void Token_Bus::enviar(char comp1, char comp2){
    assert(!Bus.vacia());

    assert(comp1 == token());

    Cola<computador> aux(25);

    while(!Bus.vacia()){
        if(Bus.frente().nombre == comp1){
            trama msj1 = Bus.frente().mensaje;
        }
        aux.push(Bus.frente());
        Bus.pop();
    }

    while(!aux.vacia()){
        if(aux.frente().nombre == comp2){
            aux.frente().mensaje = msj1;
        }
        Bus.push(aux.frente());
        aux.pop();
    }
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

struct cubilete{
    int tam;
    bool abajo;
};


Pila<cubilete> apilar(Pila<cubilete> pilaOriginal){
    Pila<cubilete> fin;

    while(!pilaOriginal.vacia()){
        cubilete cub = pilaOriginal.tope();
        pilaOriginal.pop();
        cub.abajo = true;

        while(!fin.vacia() && fin.tope().tam < cub.tam){
            pilaOriginal.push(fin.tope());
            fin.pop();
        }

        fin.push(cub);
    }

    return fin;
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

//Lista ordenada
struct paciente{
    int codigo;
    int gravedad;
};

class Hospital{
    public:
        Hospital(int tu, int tp);
        void ingreso(int cod_pac, int grav);
        void alta(int cod_pac);
        void muerte(int cod_pac);
        size_t pacientes_uci() const;
        size_t pacientes_planta() const;
        size_t pacientes_grav(int grav);
        ~Hospital(){};
    private:
        size_t tam_uci, tam_planta;
        Lista<paciente> UCI;
        Lista<paciente> PLANTA;
        typedef typename Lista<paciente>::posicion p;
};

Hospital::Hospital(int tu, int tp):tam_uci(tu), tam_planta(tp), UCI(Lista<paciente>(tu)), PLANTA(Lista<paciente>(tp)){}

void Hospital::ingreso(int cod_pac, int grav){
    paciente pa;
    pa.codigo = cod_pac;
    pa.gravedad = grav;

    //Esto es para la UCI
    if(grav > 0 && grav < 6){
        //Si la Uci no esta llena
        if(!UCI.llena()){
            p pu = UCI.primera();
            while(pu != UCI.fin() && UCI.elemento(pu).gravedad < grav){
                pu = UCI.siguiente(pu);
            }
            if(UCI.elemento(pu).gravedad < grav){
                UCI.insertar(pa, pu);
            }
        }//Si la Uci esta llena
        else{
            //Esto es si yo estoy mas sano que el mas sano de la UCI
            if(UCI.elemento(UCI.fin()).gravedad < grav){
                //Si la planta no esta llena
                if(!PLANTA.llena()){
                    p pp = PLANTA.primera();
                    while(pp != PLANTA.fin() && PLANTA.elemento(pp).gravedad < grav){
                        pp = PLANTA.siguiente(pp);
                    }
                    if(PLANTA.elemento(pp).gravedad < grav){
                        PLANTA.insertar(pa, pp);
                    }
                }//Si la planta esta llena
                else{   
                    if(grav < PLANTA.elemento(PLANTA.fin()).gravedad){
                        PLANTA.eliminar(PLANTA.fin());
                        p pp = PLANTA.primera();
                        while(pp != PLANTA.fin() && PLANTA.elemento(pp).gravedad < grav){
                            pp = PLANTA.siguiente(pp);
                        }
                        if(PLANTA.elemento(pp).gravedad < grav){
                            PLANTA.insertar(pa, pp);
                        }
                    }
                }
            }//Si yo no estoy mas sano que el mas sano de la uci
            else{
                //Si la planta no esta llena
                if(!PLANTA.llena()){
                    paciente mas_sano_uci;
                    mas_sano_uci.gravedad = UCI.elemento(UCI.fin()).gravedad;
                    mas_sano_uci.codigo = UCI.elemento(UCI.fin()).codigo;
                    UCI.eliminar(UCI.fin());
                    p pu = UCI.primera();
                    while(pu != UCI.fin() && UCI.elemento(pu).gravedad < grav){
                        pu = UCI.siguiente(pu);
                    }
                    if(UCI.elemento(pu).gravedad < grav){
                        UCI.insertar(pa, pu);
                    }

                    p pp = PLANTA.primera();
                    while(pp != PLANTA.fin() && PLANTA.elemento(pp).gravedad < mas_sano_uci.gravedad){
                        pp = PLANTA.siguiente(pp);
                    }
                    if(PLANTA.elemento(pp).gravedad < mas_sano_uci.gravedad){
                        PLANTA.insertar(mas_sano_uci, pp);
                    }
                }//Si la planta esta llena
                else{   
                    if(mas_sano_uci.gravedad < PLANTA.elemento(PLANTA.fin()).gravedad){
                        PLANTA.eliminar(PLANTA.fin());
                        p pp = PLANTA.primera();
                        while(pp != PLANTA.fin() && PLANTA.elemento(pp).gravedad < mas_sano_uci.gravedad){
                            pp = PLANTA.siguiente(pp);
                        }
                        if(PLANTA.elemento(pp).gravedad < mas_sano_uci.gravedad){
                            PLANTA.insertar(mas_sano_uci, pp);
                        }
                    }
                }
            }
        }
    }//ESto es para la planta
    else if(grav > 5 && grav < 10){
        //Si la planta no esta llena
        if(!PLANTA.llena()){
            p pp = PLANTA.primera();
            while(pp != PLANTA.fin() && PLANTA.elemento(pp).gravedad < grav){
                pp = PLANTA.siguiente(pp);
            }
            if(PLANTA.elemento(pp).gravedad < grav){
                PLANTA.insertar(pa, pp);
            }
        }//Si la planta esta llena
        else{   
            if(grav < PLANTA.elemento(PLANTA.fin()).gravedad){
                PLANTA.eliminar(PLANTA.fin());
                p pp = PLANTA.primera();
                while(pp != PLANTA.fin() && PLANTA.elemento(pp).gravedad < grav){
                    pp = PLANTA.siguiente(pa, pp);
                }
                if(PLANTA.elemento(pp).gravedad < grav){
                    PLANTA.insertar(pa, pp);
                }
            }
        }
    }
}

void Hospital::alta(int cod_pac){
    p pu = UCI.primera();
    p pp = PLANTA.primera();

    while(pu != UCI.fin() && UCI.elemento(pu).codigo != cod_pac){
        pu = UCI.siguiente(pu);
    }
    if(UCI.elemento(pu).codigo == cod_pac){
        UCI.eliminar(pu);
    }else{
        while(pp != PLANTA.fin() && PLANTA.elemento(pp).codigo != cod_pac){
            pp = PLANTA.siguiente(pp);
        }
        if(PLANTA.elemento(pp).codigo == cod_pac){
            PLANTA.eliminar(pp);
        }
    }
}

void Hospital::muerte(int cod_pac){
    alta(cod_pac);
}

size_t Hospital::pacientes_uci() const{
    p pu = UCI.primera();
    size_t cont = 0;

    while(pu != UCI.fin()){
        pu = UCI.siguiente(pu);
        cont++;
    }
    return cont;
}

size_t Hospital::pacientes_planta() const{
    p pp = PLANTA.primera();
    size_t cont = 0;

    while(pp != PLANTA.fin()){
        pp = PLANTA.siguiente(pp);
        cont++;
    }
    return cont;
}

size_t Hospital::pacientes_grav(int grav){
    size_t cont = 0;
    if(grav > 0 && grav < 6){
        if(UCI.elemento(UCI.fin()).grav < grav){
            p pp = PLANTA.primera();
            while(pp != PLANTA.fin()){
                if(PLANTA.elemento(pp).gravedad == grav){
                    cont++;
                }
                pp = PLANTA.siguiente(pp);
            }
        }else{
            p pu = UCI.primera();
            while(pu != UCI.fin()){
                pu = UCI.siguiente(pu);
                if(UCI.elemento(pu).gravedad == grav){
                    cont++;
                }
            }
        }
    }else{
        p pu = UCI.primera();
        while(pu != UCI.fin()){
            pu = UCI.siguiente(pu);
            if(UCI.elemento(pu).gravedad == grav){
                cont++;
            }
        }
    }

    return cont;
}

//TAD TEXTO haz una estructura y una función que se llama MostrarTexto() que ponga por pantalla el texto bien. Si hay una @ se elimina---------------------------------
// lo de su izq y si hay un # se elimina todo a la izqda de el.
//Ejemplo: El municipl@io -> El municipio

struct linea{
    Lista<char> caracteres;
};

class Texto{
    public:
        Texto(Lista<linea> texto);
        void mostrar_texto();
    private:
        Lista<linea> lineas;
};

Texto::Texto(Lista<linea> texto):lineas(texto){}

void Texto::mostrar_texto(){
    Lista<linea>::posicion p1 = lineas.primera();

    while(p1 != lineas.ultima()){
        Lista<char>::posicion p2 = lineas.elemento(p1).caracteres.fin();
        while(p2 != lineas.elemento(p1).caracteres.primera()){
            if(lineas.elemento(p1).caracteres.elemento(p2) == '@'){
                lineas.elemento(p1).caracteres.eliminar(lineas.elemento(p1).caracteres.anterior(p2));
                lineas.elemento(p1).caracteres.eliminar(p2);
            }
            else if(lineas.elemento(p1).caracteres.elemento(p2) == '#'){
                while(p2 != lineas.elemento(p1).caracteres.primera()){
                    lineas.elemento(p1).caracteres.eliminar(p2);
                    p2 = lineas.elemento(p1).caracteres.anterior();
                }
            }
            p2 = lineas.elemento(p1).caracteres.anterior(p2 );
        }
    }

    //Insercion de flujo la hice en poo si quieres la buscas dlh
    cout<<lineas;
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
    int cajero;
    double dia;
    double turno;
    double periodo;
    bool activa;
};

class Hipermercado{
    public:
        Hipermercado();
        void abrir(size_t num_caja, int num_cajero);
        double cerrar(size_t num_caja);
        void cobrar(size_t num_caja, double importe);
        void sustituir(size_t num_caja, int num_cajero);
        double turno();
        double cierre();
        ~Hipermercado(){};
    private:
        caja cajas[50];
};

Hipermercado::Hipermercado(){
    caja c;
    c.cajero = 0;
    c.dia = 0.0;
    c.turno = 0.0;
    c.periodo = 0.0;
    c.activa = false;
    for(size_t i = 0; i < 50; i++){
        cajas[i] = c;
    }
}

void Hipermercado::abrir(size_t num_caja, int num_cajero){
    assert(num_caja < 50);
    assert(!cajas[num_caja].activa);

    cajas[num_caja].activa = true;
    cajas[num_caja].cajero = num_cajero;
}

double Hipermercado::cerrar(size_t num_caja){
    assert(num_caja < 50);
    assert(cajas[num_caja].activa);

    cajas[num_caja].activa = false;
    cajas[num_caja].turno += cajas[num_caja].periodo;
    double aux = cajas[num_caja].periodo;
    cajas[num_caja].periodo = 0.0;

    return aux;
}

void Hipermercado::cobrar(size_t num_caja, double importe){
    assert(num_caja < 50);
    assert(cajas[num_caja].activa);

    cajas[num_caja].periodo+= importe;
}

void Hipermercado::sustituir(size_t num_caja, int num_cajero){
    assert(num_caja < 50);
    assert(cajas[num_caja].activa);

    cajas[num_caja].cajero = num_cajero;
}

double Hipermercado::turno(){
    double dinero_turno = 0.0;
    for(size_t i = 0; i < 50; i++){
        //Cierro las cajas
        cajas[i].activa = false;
        cajas[i].turno += cajas[num_caja].periodo;
        cajas[i].periodo = 0.0;

        //Guardo la suma de los turnos de cada caja
        dinero_turno += cajas[i].turno;  

        //Reinicio el turno de las cajas
        cajas[i].dia += cajas[i].turno;
        cajas[i].turno = 0.0;
    }
    return dinero_turno;
}

double Hipermercado::cierre(){
    double dinero_dia = 0.0;

    for(size_t i = 0; i < 50; i++){
        //Cierro las cajas
        cajas[i].activa = false;
        cajas[i].turno += cajas[num_caja].periodo;
        cajas[i].periodo = 0.0; 

        //Reinicio el turno de las cajas
        cajas[i].dia += cajas[i].turno;
        cajas[i].turno = 0.0;

        //Guardo la suma del dinero del dia de todas las cajas
        dinero_dia += cajas[i].dia;

        //Reinicio el dia
        cajas[i].dia = 0.0;
    }
    return dinero_dia;
}

//TAD SIMBOLO------------------------------------------------------------------------------------------------------------------------------------------------------------
/*Especificacion:*/
/*Simbolo():
	·Precondicion:-------.
	·Postcondicion:Crea un Simbolo vacio.
*/
/*void anadirTrazo(const Trazos& T):
	·Precondicion:-------.
	·Postcondicion:Anade el trazo al simbolo.
*/
/*void eliminarTrazos(size_t n):
	·Precondicion:EL numero de trazos es <=n.
	·Postcondicion:Elimina los ultimos n trazos del simbolo.
*/
/*void simetricoX():
	·Precondicion:-------.
	·Postcondicion:Devuelve el Simbolo simetrico por X.
*/
/*void simetricoY():
	·Precondicion:-------.
	·Postcondicion:Devuelve el Simbolo simetrico por Y.
*/
/*void simetricoXY():
	·Precondicion:-------.
	·Postcondicion:Devuelve el Simbolo simetrico por XY.
*/

class Simbolo{
    public:
        Simbolo(){};
        void anadirTrazo(char letra);
        void eliminarTrazos(size_t n);
        Lista<char> simetricoX();
        Lista<char> simetricoY();
        Lista<char> simetricoXY();
        ~Simetrico(){};
    private:
        Lista<char> simbolos;
        typedef typename Lista<char>::posicion p
};

void Simbolo::anadirTrazo(char letra){
    simbolos.insertar(letra, simbolos.fin());
}

void Simbolo::eliminarTrazos(size_t n){
    for(size_t i = 0; i < n; i++){
        simbolos.eliminar(simbolos.anterior(simbolos.fin()));
    }
}

Lista<char> Simbolo::simetricoX(){
    Lista<char> simetrica;
    p px = simbolos.primera();
    while(px != simbolos.fin()){
        if(simbolos.elemento(px) == 'S'){
            simetrica.insertar('B', simetrica.fin());
        }
        else if(simbolos.elemento(px) == 'B'){
            simetrica.insertar('S', simetrica.fin());
        }
        else{
            simetrica.insertar(simbolos.elemento(px), simetrica.fin());
        }
        px = simbolos.siguiente(px);
    }
    return simetrica;
}

Lista<char> Simbolo::simetricoY(){
    Lista<char> simetrica;
    p px = simbolos.primera();
    while(px != simbolos.fin()){
        if(simbolos.elemento(px) == 'I'){
            simetrica.insertar('D', simetrica.fin());
        }
        else if(simbolos.elemento(px) == 'D'){
            simetrica.insertar('I', simetrica.fin());
        }
        else{
            simetrica.insertar(simbolos.elemento(px), simetrica.fin());
        }
        px = simbolos.siguiente(px);
    }
    return simetrica;
}

Lista<char> Simbolo::simetricoXY(){
    Lista<char> simetrica;
    p px = simbolos.primera();
    
    while(px != simbolos.fin()){
        if(simbolos.elemento(px) == 'I'){
            simetrica.insertar('D', simetrica.fin());
        }
        else if(simbolos.elemento(px) == 'D'){
            simetrica.insertar('I', simetrica.fin());
        }
        else if(simbolos.elemento(px) == 'S'){
            simetrica.insertar('B', simetrica.fin());
        }
        else if(simbolos.elemento(px) == 'B'){
            simetrica.insertar('S', simetrica.fin());
        }
        px = simbolos.siguiente(px);
    }

    return simetrica;
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

struct sala{
    int id;
    Lista<int> Espectaculos;
};

class Cartelera{
    public:
        Cartelera(){};
        void anadir_sala(int sal);
        void anadir_espectaculo(int sal, int espectaculo);
        void eliminar_sala(int sal);
        void eliminar_espectaculo(int sal, int espectaculo);
        const Lista<Sala>& mostrar_salas() const noexcept;
        const Lista<Espectaculo>& mostrar_espectaculos(size_t sal) const noexcept;
        ~Cartelera(){};
    private:
        Lista<sala> salas;
        Lista<sala>::posicion p;
        p buscar(int sal);
        p buscar_espectaculo(int sal, int espec);
};

Cartelera::p Cartelera::buscar(int sal){
    p pos = salas.primera();
    while(pos != salas.fin()){
        if(salas.elemento(pos).id == sal){
            return pos;
        }
    }
    return pos;
}

Cartelera::p Cartelera::buscar_espectaculo(int sal, int espec){
    p pos = buscar(sal);
    p pos_espec = salas.elemento(pos).Espectaculos.primera();
    while(pos_espec != salas.elemento(pos).Espectaculos.fin()){
        if(salas.elemento(pos).Espectaculos.elemento(pos_espec) == espec){
            return pos_espec;
        }
    }
    return pos_espec;
}

void Cartelera::anadir_sala(int sal){
    assert(buscar(sal) == salas.fin());

    sala s;
    s.id = sal;

    salas.insertar(s, salas.fin());
}

void Cartelera::anadir_espectaculo(int sal, int espectaculo){
    p posicion_sala = buscar(sal);
    assert(posicion_sala != salas.fin());
    assert(buscar_espectaculo(sal, espectaculo) == salas.elemento(posicion_sala).Espectaculos.fin());

    salas.elemento(posicion_sala).Espectaculos.insertar(espectaculo, salas.elemento(posicion_sala).Espectaculos.fin())
}

void Cartelera::eliminar_sala(int sal){
    p posicion_sala = buscar(sal);
    assert(posicion_sala != salas.fin());

    salas.eliminar(posicion_sala);
}

void Cartelera::eliminar_espectaculo(int sal, int espectaculo){
    p posicion_sala = buscar(sal);
    assert(posicion_sala != salas.fin());

    p posicion_espectaculo = buscar(sal, espectaculo);
    assert(posicion_espectaculo != salas.elemento(posicion_sala).Espectaculos.fin());

    salas.elemento(posicion_sala).Espectaculos.eliminar(posicion_espectaculo);
}

const Lista<Sala>& mostrar_salas() const noexcept{
    return salas;
}

const Lista<Espectaculo>& mostrar_espectaculos(size_t sal) const noexcept{
    p posicion_sala = buscar(sal);
    assert(posicion_sala != salas.fin());

    return salas.elemento(posicion_sala).Espectaculos;
}

//TAD COCINA------------------------------------------------------------------------------------------------------------------------------------------------------------
// Una empresa de muebles de cocina necesita un TAD para representar el conjunto de muebles
//colocados en la pared de una cocina. Una cocina se crea con una longitud positiva
// y un mueble colocado en la pared se identifica por el par formado por su posicion
// y su anchura. La posicion es la distancia desde su lateral izquierdo al extremo derecho de la pared
// El tad debe soportar las siguiente operaciones
// -crear una cocina vacia con una longitud dada
//- determinar si un mueble de una cierta anchura puede colocarse en una posicion dada
// - añadir un mueble de una determinada longitud a una posicion dada
// - devolver el mueble inésimo de la cocina empezando a contar por la izquierda
// - eliminar el mueble enesimo de la cocina si existe
// - mover el mueble inesimo de la cocina si existe hacia la izquierda hasta que se junte con el mueble i-1 esimo o el extremo izquierdo
//de la pared
//- destruir la cocina
struct mueble{
    int posicion;
    int anchura;
};

class Cocina{
    public:
        Cocina(int longitud);
        bool colocar(int pos, int anch) const;
        void anadir(int pos, int anch);
        mueble inesimo_mue(int n) const;
        void eliminar(int n);
        void mover(int n);
        ~Cocina(){};
    private:
        int longi;
        Lista<mueble> muebles;
        typedef typename Lista<mueble>::posicion p;
};

Cocina::Cocina(int longitud):longi(longitud), muebles(Lista<mueble>(longitud)){}

bool Cocina::colocar(int pos, int anch) const{
    if(pos > longi || pos < 0 || pos - anch < 0){
        return false;
    }
    else{
        p pp = muebles.primera();

        while(pp != muebles.fin()){
            if(muebles.elemento(pp).posicion > pos > muebles.elemento(muebles.siguiente(pp)).posicion){
                if(muebles.elemento(pp).posicion - muebles.elemento(pp).anchura >= pos){
                    if(pos - anch >= muebles.elemento(muebles.siguiente(pp)).posicon){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }

            pp = muebles.siguiente(pp);
        }

        return true;
    }
}

void Cocina::anadir(int pos, int anch){
    assert(colocar(pos, anch));

    p pp = muebles.primera();

    while(pp != muebles.fin()){
        if(pos > muebles.elemento(pp).posicion){
            mueble m;
            m.posicion = pos;
            m.anchura = anch;
            muebles.insertar(m, pp);
        }
        pp = muebles.siguiente(pp);
    }
}

mueble Cocina::inesimo_mue(int n) const{
    p pp = muebles.primera();
    int cont = 0;

    while(pp != muebles.fin() && cont != n){
        pp = muebles.siguiente(pp);
        cont++;
    }
    if(cont == n){
        return muebles.elemento(pp);
    }
}

void Cocina::eliminar(int n){
    p pp = muebles.primera();
    int cont = 0;
    while(pp != muebles.fin() && cont != n){
        pp = muebles.siguiente(pp);
        cont++;
    }
    if(cont == n){
        muebles.elemento(pp);
    }
}

void Cocina::mover(int n){
    p pp = muebles.primera();
    int cont = 1;
    while(pp != muebles.fin() && cont != n){
        pp = muebles.siguiente(pp);
        cont++;
    }
    if(cont == n){
        if(pp = muebles.primera()){
            muebles.elemento(pp).posicion = longi;
        }else{
            muebles.elemento(pp).posicion = muebles.elemento(muebles.anterior(pp)).posicion - muebles.elemento(muebles.anterior(pp)).anchura;
        }
    }
}


//TAD ESCALONADA---------------------------------------------------------------------------------------------------------------------------------------------------------
// Una funcion f: R-r Es escalonada cuando consiste en una sucesion de funciones constantes definidas
//en subintervalos disjuntos y contiguos es decir f puede definirse mediante condiciones de la forma
// f(x) = yi si xi es menor o igual que z y es menor que xi+1 donde los valores yi son distintos para subinervalos
// adyacentes. Cada uno de los puntos (xi,yi) en lo que la funcion cambia de valor se llama salto o escalon
// IMAGEN
// Especificar un tad para las funciones escalonadas con un numero finito de saltos que incluya las sig operaciones
// - crear una funcion constante f(x) = yi definida a partir de xi
// - añadir un nuevo salto en el punto xi a una funcion, si ya existe un salto en las coordenadas x, se subsituye por el nuevo
// - eliminar el escalon definido en el subintervalo al que pertenece la coordenada x, el escalor anterior al
// eliminado se prolonga hasta el siguiente
// - calcular el valor de una funcion en un punto dado
// - calcular el valor minimo de una funcion escalonada
// - calculo el valor máximo de una funcion escalonada
// - hacer una traslacion de una funcion w unidades horizontales y z unidades verticales , siendo w y z ->R
// - destruir una funcion

struct salto{
    double xi, yi;
    punto(double x, double y):xi(x), yi(y){}
};

class Escalonada{
    public:
        Escalonada(double coordx, double coordy);
        void anadir_salto(double coordx, double coordy);
        void eliminar_salto(double coordx);
        double valorpunto(double coordx) const;
        double valorminimo() const;
        double valormax() const;
        void traslacion(double fx, double fy);
        ~Escalonada(){};
    private:
        Lista<salto> funcion;
        typedef typename Lista<salto>::posicion pos;
};

Escalonada::Escalonada(double coordx, double coordy){
    salto p(coordx, coordy);
    funcion.insertar(p, funcion.fin());
}

void Escalonada::anadir_salto(double coordx, double coordy){
    pos pf = funcion.primera();
    salto p(coordx, coordy);
    bool insertado = false;

    while(pf != funcion.fin() && !insertado){
        if(coordx == funcion.elemento(pf).xi){
            funcion.elemento(pf).yi = coordy;
            insertado = true;
        }
        else if(coordx < funcion.elemento(pf).xi){
            funcion.insertar(p, pf);
            insertado = true;
        }

        pf = funcion.siguiente(pf);
    }
    if(pf == funcion.fin()){
        funcion.insertar(p, pf);
    }
}

void Escalonada::eliminar_salto(double coordx){
    pos pf = funcion.primera();
    bool eliminado = false;

    while(pf != funcion.fin() && !eliminado){
        if(funcion.elemento(pf).xi == coordx){
            funcion.eliminar(pf);
            eliminado = true;
        }
        pf = funcion.siguiente(pf);
    }
}

double Escalonada::valorpunto(double coordx) const{
    pos pf = funcion.primera();

    while(pf != funcion.fin() && !eliminado){
        if(funcion.elemento(pf).xi == coordx){
            return funcion.elemento(pf).yi;
        }
        pf = funcion.siguiente(pf);
    }
}

double Escalonada::valorminimo() const{
    pos pf = funcion.primera();
    double minimo = funcion.elemento(pf).yi;

    while(pf != funcion.fin()){
        if(funcion.elemento(pf).yi < minimo){
            minimo = funcion.elemento(pf).yi;
        }
        pf = funcion.siguiente(pf);
    }

    return minimo;
}

double Escalonada::valormax() const{
    pos pf = funcion.primera();
    double maximo = funcion.elemento(pf).yi;

    while(pf != funcion.fin()){
        if(funcion.elemento(pf).yi > maximo){
            maximo = funcion.elemento(pf).yi;
        }
        pf = funcion.siguiente(pf);
    }

    return maximo;
}

void Escalonada::traslacion(double fx, double fy){
     pos pf = funcion.primera();

     while(pf != funcion.fin()){
        funcion.elemento(pf).xi += fx;
        funcion.elemento(pf).yi += fy;
        pf = funcion.siguiente(pf);
    }
}

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
    int duracion, n;
    string nombre;
    cancion(int nombre_, int duracion_, int n_= 0):nombre(nombre_), duracion(duracion_){}
};

class Radio{
    public:
        Radio();
        void anadir_cancion(string nom, int dur);
        cancion devuelve_cancion_menos_emitida(int tiempo) const;
        cancion devuelve_cancion_mas_emitida(int tiempo) const;
        void emitir_canción(string nom);
        void borrar_n_canciones(int n);
        ~Radio(){};

    private:
        Lista<cancion> canciones;
        typedef typename Lista<cancion>::posicion p;
};

Radio::Radio(){}

void Radio::anadir_cancion(string nom, int dur){
    cancion c(nom, dur);
    canciones.insertar(c, canciones.fin());
}

cancion Radio::devuelve_cancion_menos_emitida(int tiempo) const{
    p paux = canciones.primera();
    p pc = canciones.primera();
    int repetida = canciones.elemento(pc).n;
    int rep = 0;

    while(pc != canciones.fin()){
        if(canciones.elemento(pc).duracion == tiempo){
            rep = canciones.elemento(pc).n;
            if(canciones.elemento(pc).n < repetida){
                repetida = canciones.elemento(pc).n;
                paux=pc;
            }
        }
        pc = canciones.siguiente(pc);
    }
}

cancion Radio::devuelve_cancion_mas_emitida(int tiempo) const{
    p pc = canciones.primera();
    p paux = canciones.primera();
    int repe = 0;

    while(pc != canciones.fin()){
        if(canciones.elemento(pc).duracion == tiempo && canciones.elemento(pc).n > repe){
            repe = canciones.elemento(pc).n;
            paux = pc;
        }
        pc = canciones.siguiente(pc);
    }

    return canciones.elemento(paux);
}

void Radio::emitir_canción(string nom){
    p pc = canciones.primera();
    bool aux = false;

    while(pc != canciones.fin() && !aux){
        if(canciones.elemento(pc).nombre == nom){
            canciones.elemento(pc).n++;
            aux = true;
        }
        pc = canciones.siguiente(pc);
    }
}

void Radio::borrar_n_canciones(int n){ 
    int cont = 0;

    while(cont < n){

        p pc = canciones.primera();
        p paux =canciones.primera();
        int repeticiones = canciones.elemento(pc).n;


        while(pc != canciones.fin()){
            if(canciones.elemento(pc).n < repeticiones){
                repeticiones = canciones.elemento(pc).n;
                paux = pc;
            }
            pc = canciones.siguiente(pc);
        }
        canciones.eliminar(paux);

        cont++;
        
    }

}
