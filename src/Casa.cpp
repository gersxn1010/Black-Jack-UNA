
#include "Casa.h"
#include "Ficha.h"


static void entregarFichas(Jugador& j, int monto) {
 
    const int valores[4] = { 100, 25, 5, 1 };
    const string colores[4] = { "negro", "verde", "rojo", "blanco" };

    for (int i = 0; i < 4; i++) {
        while (monto >= valores[i]) {
            j.agregarFicha(Ficha(valores[i], colores[i]));
            monto -= valores[i];
        }
    }
}

Casa::Casa(int dineroMesa) {
    this->dineroMesa = dineroMesa;
}

int Casa::getDineroMesa() {
    return dineroMesa;
}
void Casa::pagarApuesta(Jugador& j) {
    int apuesta = j.getApuestaActual();
    dineroMesa -= apuesta;                 
    entregarFichas(j, apuesta * 2);        
}


void Casa::cobrarApuesta(Jugador& j) {
    dineroMesa += j.getApuestaActual();
}