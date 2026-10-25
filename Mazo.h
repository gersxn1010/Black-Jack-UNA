#pragma once
#include <iostream>
#include <vector>
#include <random>
#include "Carta.h"
using namespace std;

class Mazo {
private:
    vector<Carta> cartas;
    int numeroMazos;
    mt19937 generador;
    void llenar();
public:
    Mazo(int numeroMazos = 6);
    int cartasRestantes();
    bool estaVacio();
    void barajar();
    Carta sacarCarta();
    void reiniciar();
};