#include "Mano.h"
#include "Carta.h"

Mano::Mano() {
}

void Mano::agregarCarta(const Carta& c) { // Método para agregar una carta a la mano
void Mano::agregarCarta(const Carta& c) { // Método para agregar una carta a la
	cartas.push_back(c);
}

int Mano::calcularValor() const {
	int valor = 0;
	int cantidadAses = 0;
	for (const Carta& carta : cartas) {
		valor += carta.getValor();
		if (carta.getValor() == 11) { // As
			cantidadAses++; // Contar la cantidad de Ases
		}
	}
	while (valor > 21 && cantidadAses > 0) {
		valor -= 10; // Contar el As como 1 en lugar de 11
		cantidadAses--;
	}
	return valor;
}

bool Mano::esBlackjack() const {
	return cartas.size() == 2 && calcularValor() == 21;// Verificar si hay exactamente dos cartas y su valor es 21
}

bool Mano::sePasa() const {
	return calcularValor() > 21;// Verificar si el valor de la mano supera 21
}

void Mano::limpiar() {
	cartas.clear();
}

int Mano::cantidadCartas() const {
	return cartas.size();
}

void Mano::mostrar() const {
	for (const Carta& carta : cartas) {
		carta.mostrar();
	}

	cout << "Valor actual: " << calcularValor() << endl;
}