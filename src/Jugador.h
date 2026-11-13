#pragma once
#include <iostream>
#include <vector>
#include "Ficha.h"
#include "Participante.h"

using namespace std;

class Jugador : public Participante {

private:

	vector<Ficha> fichas;

	int apuestaActual;

public:

	Jugador(string nombre);

	bool quiereCarta() override;

	bool apostar(int monto);

	void recibirFichas(int monto);

	int entregarFichasApostadas();

	int getApuesta();

};