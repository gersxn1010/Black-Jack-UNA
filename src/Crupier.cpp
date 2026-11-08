#include "Crupier.h"
#include "Mano.h"
#include "Participante.h"
#include "Mazo.h"
#include "Carta.h"

Crupier::Crupier(int numeroMazos)
    : Participante("Crupier"), mazo(numeroMazos) {
    // se rebaraja cuando queda menos del 25% de las cartas
    limiteRebarajar = (52 * numeroMazos) / 4;
}

bool Crupier::quiereCarta() {
    return mano.calcularValor() < 17;   // el crupier pide hasta llegar a 17
}

void Crupier::repartirCarta(Participante& destino) {
    if (mazo.estaVacio()) {             // seguridad por si se acaba a mitad de ronda
        mazo.reiniciar();
    }
    destino.recibirCarta(mazo.sacarCarta());
}

void Crupier::repartirManoInicial(Participante& destino) {
    repartirCarta(destino);
    repartirCarta(destino);
}

void Crupier::reiniciarSiHaceFalta() {
    if (mazo.cartasRestantes() < limiteRebarajar) {
        mazo.reiniciar();
    }
}

int Crupier::cartasRestantes() {
    return mazo.cartasRestantes();
}