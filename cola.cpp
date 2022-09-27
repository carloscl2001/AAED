#ifndef COLA_VEC_H
#define COLA_VEC_H
#include <cassert>
template <typename T> class Cola {
public:
explicit Cola(size_t TamaMax); // Constructor, req. ctor. T()
Cola(const Cola<T>& C); // Ctor. de copia, requiere ctor. T()
Cola<T>& operator =(const Cola<T>& C); // Asig., req. ctor. T()
 bool vacia() const;
 bool llena() const; // Requerida por la implementación
 const T& frente() const;
 void pop();
 void push(const T& x);
 ~Cola(); // Destructor
 private:
 T *elementos; // Vector de elementos
 size_t Lmax; // Tamaño del vector
 size_t n_eltos; // Tamaño de la cola
 };
 template <typename T>
 inline Cola<T>::Cola(size_t TamaMax) :
 elementos(new T[TamaMax]),
 Lmax(TamaMax),
 n_eltos(0)
 {}
 template <typename T>
 Cola<T>::Cola(const Cola<T>& C) :
 elementos(new T[C.Lmax]),
 Lmax(C.Lmax),
 n_eltos(C.n_eltos)
 {
 for (size_t i = 0; i < n_eltos; ++i) // Copiar elementos
 elementos[i] = C.elementos[i];
 }
 template <typename T>
 Cola<T>& Cola<T>::operator =(const Cola<T>& C)
 {
 if (this != &C) { // Evitar autoasignación
 // Destruir el vector y crear uno nuevo si es necesario
 if (Lmax != C.Lmax) {
 delete[] elementos;
 Lmax = C.Lmax;
 elementos = new T[Lmax];
 }
 n_eltos = C.n_eltos;
 // Copiar elementos
 for (size_t i = 0; i < n_eltos; ++i)
 elementos[i] = C.elementos[i];
 }
 return *this;
 }
 template <typename T>
 inline bool Cola<T>::vacia() const
 {
 return (n_eltos == 0);
 }
 template <typename T>
 inline bool Cola<T>::llena() const
 {
 return (n_eltos == Lmax);
 }
 template <typename T>
 inline const T& Cola<T>::frente() const
 {
 assert(!vacia());
 return elementos[0];
 }
 template <typename T>
 void Cola<T>::pop()
 {
 assert(!vacia());
 for (size_t i = 1; i < n_eltos; ++i)
 elementos[i-1] = elementos[i];
 --n_eltos;
 }
 template <typename T>
 inline void Cola<T>::push(const T& x)
 {
 assert(!llena());
 elementos[n_eltos] = x;
 ++n_eltos;
 }
 template <typename T>
 inline Cola<T>::~Cola()
 {
 delete[] elementos;
 }
 #endif // COLA_VEC_H