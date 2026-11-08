#pragma once
#include <iostream>
#include <random>
#include "Casa.h"
#include "Mazo.h"
#include "Jugador.h"
#include "Participante.h"

using namespace std;

class Crupier : public Participante {

private:
    Casa& casa;

public:
    Crupier(Casa& casa);

    bool quiereCarta() override;
    void repartirA(Participante& p, Mazo& mazo);
    bool aceptarApuesta(Jugador& j, int monto);
    void revelarCarta();
    void recogerCartas(Participante& p);
};