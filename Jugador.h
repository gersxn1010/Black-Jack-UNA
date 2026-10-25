#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Participante.h"
#include "Ficha.h"
using namespace std;

class Jugador : public Participante {
private:
    vector<Ficha> fichas;
    int apuestaActual;
    bool plantado;
public:
    Jugador(string nombre, vector<Ficha> fichas);
    bool quiereCarta() override;
    bool puedeApostar(int monto);
    bool apostarFicha(int indice);
    bool doblarApuesta();
    void plantarse();
    int getDinero();
    int getApuestaActual();
    void nuevaRonda();
    void agregarFicha(Ficha f);
    void mostrarFichas();   // extra: para elegir ficha al apostar
};