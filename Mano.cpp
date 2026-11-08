#include "Mano.h"
                                                                                                                
void Mano::agregarCarta(const Carta& c) {
    cartas.push_back(c);
}

int Mano::calcularValor() const {
    int valor = 0;
    int ases = 0;
    for (const Carta& c : cartas) {
        valor += c.getValor();

        if (c.esAs()) {
            ases++;
        }
        //El As puede valer 1 o 11 en blackjack.s
        //Se reduce su valor en 10 si nos pasamos de 21.
        while (valor > 21 && ases > 0) {
            valor -= 10;
            ases--;
        }
    }
    return valor;
}

bool Mano::esBlackJack() const {
    return cartas.size() == 2 && calcularValor() == 21;

}

bool Mano::sePasa() const {
    return calcularValor() > 21;
}

int Mano::cantidadCartas() const {
    return static_cast<int>(cartas.size());
}

void Mano::limpiar() {
    cartas.clear();
    valorApuesta = 0;
}

int Mano::getValorApuesta() const {
    return valorApuesta;
}

string Mano::aTexto(bool ocultarPrimera) const {
    string resultado;

    for (int i = 0; i < cantidadCartas(); i++) {
        if (i == 0 && ocultarPrimera) {
            resultado += "[Carta oculta]";
        }
        else {
            //Ajustar segun el metodo que tenga la clase carta
            resultado += cartas[i].mostrarCarta();
        }


        if (i < cantidadCartas() - 1) {
            resultado += ",  ";
        }

    }
    return resultado;
}


