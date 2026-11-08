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

string Carta::getTipo() const {
    return tipo;
}

int Carta::getValor() const {
    return valor;
}

int Carta::getNumeroCarta() const {
    return numeroCarta;
}

bool Carta::esAs() const {
    return numeroCarta == 1;
}