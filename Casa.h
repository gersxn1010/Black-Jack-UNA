#pragma once
#include <iostream>
#include "Jugador.h"
using namespace std;

class Casa {
private:
    int dineroMesa;
public:
    Casa(int dineroMesa);
    int getDineroMesa();
    void pagarApuesta(Jugador& j);
    void cobrarApuesta(Jugador& j);
};