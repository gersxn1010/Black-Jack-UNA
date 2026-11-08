#include "Ficha.h"

Ficha::Ficha(int valor, string colorFicha) {
    this->valor = valor;
    this->colorFicha = colorFicha;
}

int Ficha::getValor() {
    return valor;
}

string Ficha::getColorFicha() {
    return colorFicha;
}