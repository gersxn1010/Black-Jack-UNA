#pragma once
#include <iostream>
#include <vector>
#include "Carta.h"
#include <string>

using namespace std;

class Mano {

private:

	vector<Carta> cartas;
	int valorApuesta = 0;

	friend class Juego;

public:

	void agregarCarta(const Carta& c);

	int calcularValor() const;

	bool esBlackJack() const;

	bool sePasa() const;

	int cantidadCartas() const;

	void limpiar();

	int getValorApuesta() const;

	string aTexto(bool ocultarPrimera) const;

};