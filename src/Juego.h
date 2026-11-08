#pragma once
#include <iostream>
#include <random>
#include <vector>
#include "Casa.h"
#include "Jugador.h"
#include "Crupier.h"
#include "Mazo.h"
#include "Participante.h"

using namespace std;

enum class EstadoJuego { MENU, APOSTANDO, TURNO_JUGADOR, TURNO_CRUPIER, PAGANDO, FIN_RONDA };
enum class ResultadoRonda { GANA, BLACKJACK, EMPATE, PIERDE };

class Juego {

private:

	Casa casa;

	vector<Jugador> jugadores;
	vector<int> saldosJugadores;
	vector<int> apuestasRonda;

	Crupier crupier;
	vector<Mazo> mazo;
	EstadoJuego estado;
	int numeroRonda;

	void barajar(Mazo& mazo);

	ResultadoRonda resolverApuesta(const Jugador& jugador);

	void pagar(Jugador& jugador, ResultadoRonda resultado);

	void cobrar(Jugador& jugador);

public:

	Juego();

	void iniciar();

	void reglas();

	void iniciarRonda();

	void cederTurno(Participante& p);

	void finalizarRonda();

	bool hayJugadoresConDinero();

};