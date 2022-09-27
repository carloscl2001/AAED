#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H
#include <cassert>


template <typename T> 
class Lista
{
struct nodo; // Declaraci�n adelantada privada
	public:
		typedef nodo* posicion; // Posici�n de un elemento
		Lista(); // Constructor, requiere ctor. T()
        Lista(int) : Lista() {}
		Lista(const Lista<T>& Lis); // Ctor. de copia, req. ctor. T()
		Lista<T>& operator =(const Lista<T>& Lis); // Asig. de listas
		void insertar(const T& x, posicion p);
		void eliminar(posicion p);
		const T& elemento(posicion p) const;// Lec. elto. en Lista const
		
		//-------------------------------------
		//inline de elemento porque falla si no
		inline T& elemento(posicion p)
		{
			assert(p->sig != L); // p no es fin
		return p->sig->elto;
		}
		//-------------------------------------
		
		posicion buscar(const T& x) const;// Req. operador == para T
		posicion siguiente(posicion p) const;
		posicion anterior(posicion p) const;
		posicion primera() const;
		posicion fin() const; // Posici�n despu�s del �ltimo
		~Lista(); // Destructor
	private:
		struct nodo
		{
			T elto;
			nodo *ant, *sig;
			nodo(const T& e, nodo* a = nullptr, nodo* s = nullptr): elto(e), ant(a), sig(s) {}
		};
		nodo* L; // lista doblemente enlazada de nodos
		void copiar(const Lista<T>& Lis);
};

// M�todo privado
template <typename T>
void Lista<T>::copiar(const Lista<T> &Lis)
{
	L = new nodo(T()); // Crear el nodo cabecera
	L->ant = L->sig = L; // Estructura circular
	// Copiar elementos de Lis
	for (nodo* q = Lis.L->sig; q != Lis.L; q = q->sig)
	L->ant = L->ant->sig = new nodo(q->elto, L->ant, L);
}

template <typename T>
inline Lista<T>::Lista() : L(new nodo(T())) // Crear cabecera
{	
	L->ant = L->sig = L; // Estructura circular
}
template <typename T>
inline Lista<T>::Lista(const Lista<T>& Lis)
{
copiar(Lis); 
}

template <typename T>
Lista<T>& Lista<T>::operator =(const Lista<T>& Lis)
{
	if (this != &Lis)
	{ // Evitar autoasignaci�n
		this->~Lista(); // Vaciar la lista actual
		copiar(Lis);
	}
return *this;
}

template <typename T> inline
void Lista<T>::insertar(const T& x, Lista<T>::posicion p)
{
	
	p->sig = p->sig->ant = new nodo(x, p, p->sig);
	// El nuevo nodo con x queda en la posici�n p
}

template <typename T>
inline void Lista<T>::eliminar(Lista<T>::posicion p)
{
	assert(p->sig != L); // p no es fin
	nodo* q = p->sig;
	p->sig = q->sig;
	p->sig->ant = p;
	delete q;
// El nodo siguiente queda en la posici�n p
}

//deberia de ir aqui como no funciona hacemos un inline
/*
template <typename T> 
const T& Lista<T>::elemento(Lista<T>::posicion p) const
{
	assert(p->sig != L); // p no es fin
return p->sig->elto;
}
*/

template <typename T>
typename Lista<T>::posicion Lista<T>::buscar(const T& x) const
{
	nodo* q = L;
	bool encontrado = false;
	while (q->sig != L && !encontrado)
	if (q->sig->elto == x)
	encontrado = true;
	else q = q->sig;
	
return q;
}

template <typename T> inline
typename Lista<T>::posicion
Lista<T>::siguiente(Lista<T>::posicion p) const
{
	assert(p->sig != L); // p no es fin
return p->sig;
}

template <typename T> inline
typename Lista<T>::posicion
Lista<T>::anterior(Lista<T>::posicion p) const
{
	assert(p != L); // p no es la primera posici�n
return p->ant;
}

template <typename T>
inline typename Lista<T>::posicion Lista<T>::primera() const
{
return L;
}

template <typename T>
inline typename Lista<T>::posicion Lista<T>::fin() const
{
return L->ant;
}

// Destructor: vac�a la lista y destruye el nodo cabecera
template <typename T>
Lista<T>::~Lista()
{
	nodo* q;
	while (L->sig != L) {
	q = L->sig;
	L->sig = q->sig;
	delete q;
	}
delete L;
}

#endif // LISTA_DOBLE_H
