#ifndef pila
#define pila
class Pila {
    public:
        typedef char tElemento;
        explicit Pila(unsigned TamaMax);    // constructor
        Pila(const Pila& P);                // ctor. de copia
        Pila& operator =(const Pila& P);    // asignación entre pilas
        bool vacia() const;
        bool llena() const;                 
        const tElemento& tope() const;
        void pop();
        void push(const tElemento& x);
        ~Pila();                            // destructor
    private:
        tElemento *elementos;               // vector de elementos
        int Lmax;                           // tamaño del vector
        int tope_;                          // posición del tope
};
#endif
