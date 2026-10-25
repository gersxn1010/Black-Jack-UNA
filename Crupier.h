#pragma once
#include <iostream>
#include "Participante.h"
#include "Mazo.h"
using namespace std;

class Crupier : public Participante {
private:
    Mazo mazo;
public:
    Crupier(int numeroMazos = 6);
    bool quiereCarta() override;
    void repartirCarta(Participante& destino);
    void repartirManoInicial(Participante& destino);
    void reiniciarSiHaceFalta();
    int cartasRestantes();
};