#pragma once
#include <iostream>
#include <string>
#include "Mano.h"
using namespace std;

class Participante {

protected:

    string nombre;
    Mano mano;
public:

    Participante(string nombre);
    virtual ~Participante();
    virtual bool quiereCarta() = 0;
    void recibirCarta(const Carta& c);
    const Mano& getMano() const;
    void limpiarMano();
    string getNombre() const;
};