#include "Mazo.h"

void Mazo::crearBarajaCompleta() //Método encargado de crear una baraja completa de cartas.


{
    cartas.clear();// Limpia las cartas que se encuentran actualmente en el mazo.

    string palos[4] = { "Corazones", "Diamantes", "Treboles", "Picas" };

    //Se recorre los cuatro palos de la baraja, luego las cartas numeradas del 1 al 13 para cada palo
    for (int p = 0; p < 4; p++) {
        for (int numero = 1; numero <= 13; numero++) {
            cartas.push_back(Carta(palos[p], numero));// Agrega una nueva carta al mazo con su respectivo palo y numero
        }
    }
}
Mazo::Mazo() {
    crearBarajaCompleta();
}

Carta Mazo::sacarCarta() {

    if (cartas.empty()) // Comprueba que el mazo este vacío
    {
        crearBarajaCompleta(); // En caso que no queden cartas, crea una baraja 
    }

    Carta carta = cartas.back();
    cartas.pop_back();
    return carta;
}

bool Mazo::estaVacio() {
    return cartas.empty();
}

int Mazo::cartasRestantes() {
    return (int)cartas.size();
}

bool Mazo::necesitaBarajar() {
    return cartas.empty();
}