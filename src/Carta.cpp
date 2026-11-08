#include "Carta.h"


Carta::Carta(string tipo, int numeroCarta) {
    this->tipo = tipo;
    this->numeroCarta = numeroCarta;
    if (numeroCarta == 1) {
        valor = 11; //As
    }
    else if (numeroCarta >= 10) {
        valor = 10; //J, Q, K
    }
    else {
        valor = numeroCarta; //2-9
    }
}

