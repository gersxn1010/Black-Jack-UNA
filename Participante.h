#pragma once
#include <iostream>
#include <vector>
#include "Mano.h"
#include "Carta.h"

using namespace std;

class Participante{

protected:

string nombre;

vector<Mano>manos;

friend class Juego;

public:

Participante(string nombre);

virtual ~Participante();

virtual bool quiereCarta();

void recibirCarta(const Carta& c);

const Mano& getMano() const;

void limpiarMano();

string getNombre() const;

};