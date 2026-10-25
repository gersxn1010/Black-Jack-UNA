#pragma once
#include <iostream>
#include <string>
using namespace std;

class Carta {
private:
    string tipo;
    int valor;
    int numeroCarta;
public:
    Carta(string tipo, int numeroCarta);
    string getTipo();
    int getValor();
    int getNumeroCarta();
    bool esAs();
    string mostrarCarta();
};