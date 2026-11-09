#include "Jugador.h"
#include "Ficha.h"
using namespace std;

Jugador::Jugador(string nombre) : Participante(nombre) {
    this->apuestaActual = 0;
}

bool Jugador::quiereCarta() {
    return Participante::quiereCarta();
} // fin de quiereCarta

bool Jugador::apostar(int monto) {
    int totalFichas = 0;

    for (Ficha ficha : fichas) {
        totalFichas += ficha.getValor();
    }

    if (monto > 0 && monto <= totalFichas) {
        apuestaActual = monto;
        return true;
    }

    return false;
} // fin de apostar

void Jugador::recibirFichas(int monto) {
    // Denominaciones de mayor a menor, con su color
    const int valores[] = { 100, 25, 10, 5, 1 };
    const string colores[] = { "negro", "verde", "azul", "rojo", "blanco" };

    for (int i = 0; i < 5; i++) {
        while (monto >= valores[i]) {
            fichas.push_back(Ficha(valores[i], colores[i]));
            monto -= valores[i];
        }
    }
} // fin de recibirFichas

int Jugador::entregarFichasApostadas() {
    int apuesta = apuestaActual;
    int totalFichas = 0;

    for (Ficha ficha : fichas) {
        totalFichas += ficha.getValor();
    }

    fichas.clear();
    recibirFichas(totalFichas - apuesta);

    apuestaActual = 0;
    return apuesta;
} // fin de entregarFichasApostadas

int Jugador::getApuesta() {
    return apuestaActual;
}