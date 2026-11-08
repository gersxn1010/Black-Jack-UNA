#pragma once
#include <iostream>
#include <vector>
#include "Carta.h"

using namespace std;

class Mazo {

private:

    void crearBarajaCompleta();



public:

    Mazo();

    vector<Carta> cartas;

    Carta sacarCarta();

    bool estaVacio();

    int cartasRestantes();

    bool necesitaBarajar();

};