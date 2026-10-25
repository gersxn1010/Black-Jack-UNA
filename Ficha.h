#pragma once
#include <iostream>
#include <string>
using namespace std;

class Ficha {
private:
    int valor;
    string colorFicha;
public:
    Ficha(int valor, string colorFicha);
    int getValor() const;
    string getColorFicha() const;
};