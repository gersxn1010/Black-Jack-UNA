#include "Juego.h"
#include "Jugador.h"
#include "Crupier.h"
#include "Mazo.h"
#include "Participante.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>


namespace {

    mt19937& generadorAleatorio() {
        static mt19937 generador([] {
            random_device fuente;
            seed_seq semilla{
                fuente(),
                fuente(),
                static_cast<unsigned int>(
                    chrono::high_resolution_clock::now().time_since_epoch().count())
            };
            return mt19937(semilla);
            }());
        return generador;
    }



    void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    }






    int leerNumero(const string& mensaje, int minimo, int maximo) {
        int numero;

        while (true) {
            cout << mensaje;

            if (cin >> numero && numero >= minimo && numero <= maximo) {
                return numero;
            }

            cout << "Ingresa un numero entre " << minimo << " y " << maximo << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }






    void pausar() {
        cout << "\nPresiona Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }






    void mostrarTitulo() {
        cout << "\n";
        cout << "  +======================================================+\n";
        cout << "  |                 BLACKJACK - LA CASA                 |\n";
        cout << "  +======================================================+\n";
    }


    Mazo& seleccionarMazo(vector<Mazo>& mazos) {
        int totalCartas = 0;
        for (Mazo& mazo : mazos) {
            totalCartas += mazo.cartasRestantes();
        }

        if (totalCartas == 0) {
            throw logic_error("No hay cartas disponibles para repartir.");
        }

        uniform_int_distribution<int> distribucion(1, totalCartas);
        int cartaSeleccionada = distribucion(generadorAleatorio());

        for (Mazo& mazo : mazos) {
            cartaSeleccionada -= mazo.cartasRestantes();
            if (cartaSeleccionada <= 0) {
                return mazo;
            }
        }

        return mazos.back();
    }


    ResultadoRonda resolverMano(const Mano& manoJugador, const Mano& manoCrupier) {
        if (manoJugador.sePasa()) {
            return ResultadoRonda::PIERDE;
        }

        if (manoJugador.esBlackJack() && manoCrupier.esBlackJack()) {
            return ResultadoRonda::EMPATE;
        }

        if (manoCrupier.esBlackJack()) {
            return ResultadoRonda::PIERDE;
        }

        if (manoJugador.esBlackJack()) {
            return ResultadoRonda::BLACKJACK;
        }

        if (manoCrupier.sePasa() ||
            manoJugador.calcularValor() > manoCrupier.calcularValor()) {
            return ResultadoRonda::GANA;
        }

        if (manoJugador.calcularValor() == manoCrupier.calcularValor()) {
            return ResultadoRonda::EMPATE;
        }

        return ResultadoRonda::PIERDE;
    }





    void liquidarMano(Jugador& jugador, Mano& mano, ResultadoRonda resultado,
        Casa& casa, int& saldo) {
        int apuesta = mano.getValorApuesta();

        if (resultado == ResultadoRonda::PIERDE) {
            cout << jugador.getNombre() << ": pierde " << apuesta << ".\n";
            casa.recibirApuestaPerdida(apuesta);
            return;
        }

        if (resultado == ResultadoRonda::EMPATE) {
            cout << jugador.getNombre() << ": empate; se devuelve "
                << apuesta << ".\n";
            jugador.recibirFichas(apuesta);
            saldo += apuesta;
            return;
        }

        int ganancia = apuesta;
        if (resultado == ResultadoRonda::BLACKJACK) {
            ganancia = apuesta * 3 / 2;
        }

        if (casa.intentarPagarPremio(ganancia)) {
            jugador.recibirFichas(apuesta + ganancia);
            saldo += apuesta + ganancia;
            if (resultado == ResultadoRonda::BLACKJACK) {
                cout << jugador.getNombre()
                    << ": BLACKJACK! Hiciste 21 con tus dos cartas. "
                    << "Recibes " << apuesta + ganancia
                    << " en total (premio de 3:2).\n";
            }
            else {
                cout << jugador.getNombre() << ": gana; recibe "
                    << apuesta + ganancia << ".\n";
            }
        }
        else {
            jugador.recibirFichas(apuesta);
            saldo += apuesta;
            cout << jugador.getNombre()
                << ": la casa no puede cubrir el premio; se devuelve la apuesta.\n";
        }
    }

}//Final del namespace anónimo