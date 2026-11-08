#include "Mazo.h"

void Mazo::crearBarajaCompleta() {
    cartas.clear();

    string palos[4] = { "Corazones", "Diamantes", "Treboles", "Picas" };

    for (int p = 0; p < 4; p++) {
        for (int numero = 1; numero <= 13; numero++) {
            cartas.push_back(Carta(palos[p], numero));
        }
    }
}