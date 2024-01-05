#include "pila_enlazada.hpp"
#include "iostream"
using namespace std;

int main(){

    Pila<int> pilita;
    int cambio = 90;

    pilita.push(10);
    pilita.push(20);
    pilita.push(40);

    cambio =  pilita.tope() - 30;

    pilita.pop();
    pilita.push(cambio);
    cout<<pilita.tope();

}
