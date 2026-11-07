#pragma once
#include <iostream>
#include <vector>
#include "Jugador.h"
#include "Crupier.h"
#include "Casa.h"
#include "EstadoJuego.h"
using namespace std;

enum class EstadoJuego {
    MENU,
    APOSTANDO,
    TURNO_JUGADOR,
    TURNO_CRUPIER,
    FIN_RONDA
};

class Juego {
private:
    vector<Jugador> jugadores;
    Crupier crupier;
    Casa casa;
    EstadoJuego estado;
    int numeroRonda;

    void iniciarRonda();
    void recibirApuestas();
    void turnoJugador(Jugador& j);
    void turnoCrupier();
    void determinarGanador();
    bool validarApuesta(int apuesta, int saldo);
    void finalizarRonda();
    bool hayJugadoresConDinero();
public:
    Juego();
    void iniciar();
};



