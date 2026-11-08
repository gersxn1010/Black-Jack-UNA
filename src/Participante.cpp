#include "Participante.h"
#include <stdexcept>

Participante::Participante(string nombre)
    :nombre(nombre) {
}

Participante :: ~Participante() {}

bool Participante::quiereCarta() {
    string opcion;
    while (true) {
        cout << nombre << ", ¿deseas pedir otra carta? (s/n): ";
        if (!(cin >> opcion)) {
            throw runtime_error("No se pudo leer la respuesta del participante.");
        }

        if (opcion == "s" || opcion == "S") {
            return true;
        }
        if (opcion == "n" || opcion == "N") {
            return false;
        }

        cout << "Respuesta no valida. Ingresa s o n.\n";
    }
}

void Participante::recibirCarta(const Carta& c) {
    if (manos.empty()) {
        manos.push_back(Mano());
    }

    manos.back().agregarCarta(c);
}

const Mano& Participante::getMano() const {
    return manos.front();
}

void Participante::limpiarMano() {
    manos.clear();
}

string Participante::getNombre() const {
    return nombre;
}