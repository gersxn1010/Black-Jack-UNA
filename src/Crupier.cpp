
#include "Crupier.h"

Crupier::Crupier(Casa& casa) : Participante("Crupier"), casa(casa) {
}

bool Crupier::quiereCarta() {
    return getMano().calcularValor() < 17;
}

void Crupier::repartirA(Participante& p, Mazo& mazo) {
    if (mazo.estaVacio()) {
        return;
    }
    p.recibirCarta(mazo.sacarCarta());
}

bool Crupier::aceptarApuesta(Jugador& j, int monto) {
    if (!casa.EsApuestaValida(monto)) {
        return false;
    }
    return j.apostar(monto);
}

void Crupier::revelarCarta() {
    cout << getNombre() << ": " << getMano().aTexto(false) << endl;
}

void Crupier::recogerCartas(Participante& p) {
    p.limpiarMano();
}