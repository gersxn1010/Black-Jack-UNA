#pragma once
#include <iostream>

using namespace std;

class Jugador {

protect:
mano:Mano;

private:
	int dinero;
	int apuestaActual;

public:

	void apostarFicha();

	void pedirCarta(c:Carta);

	void plantarse();

	void doblarApuesta();

	Mano getMano();

};