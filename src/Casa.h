#pragma once
#include <iostream>
#include <string>

using namespace std;

class Casa {

private:

	string nombre = "Casa";
	int dineroBanca = 2000;
	int apuestaMinima = 10;
	int apuestaMaxima = 500;

public:

	Casa();

	bool EsApuestaValida(int monto);

	bool intentarPagarPremio(int monto);

	void recibirApuestaPerdida(int monto);

	int getDineroBanca();


};