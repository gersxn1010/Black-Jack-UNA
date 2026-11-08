#pragma once
#include <iostream>

using namespace std;

class Ficha {

private:

	int valor;

	string colorFicha;

public:

	Ficha(int valor, string colorFicha);

	int getValor();

	string getColorFicha();

};