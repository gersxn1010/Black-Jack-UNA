#pragma once
#include <iostream>
#include <vector>
#include "Carta.h"
#include <vector>
#include "Carta.h"

using namespace std;

class Mano {
private:
    vector<Carta> cartas;
public:
    void agregarCarta(const Carta& c);
    int calcularValor() const;
    bool esBlackjack() const;
    bool sePasa() const;
    void limpiar();
    int cantidadCartas() const;
    void mostrar() const;

	Mano();<

	void agregarCarta(const Carta& c);

	int calcularValor() const;

	bool esBlackjack() const;

	bool sePasa() const;

	void limpiar();

	int cantidadCartas() const;

	void mostrar() const;


};