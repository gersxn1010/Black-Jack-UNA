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

	// Crea un generador de números aleatorios con una semilla basada en la hora actual y un dispositivo de hardware.
    mt19937& generadorAleatorio() {
        static mt19937 generador([] {
            random_device fuente;
			// Mezcla la semilla con la hora actual para obtener un generador más impredecible.
            seed_seq semilla{
                fuente(),
                fuente(),
                static_cast<unsigned int>(
					// Obtiene la hora actual en nanosegundos desde una referencia historica y la convierte a un entero sin signo.
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





	// Función para leer un número entero dentro de un rango específico.
	// Esto lo podria hacer un switch case, pero es más sencillo y flexible con un bucle while.
	// nos da la facilidad para validar la entrada del usuario y asegurarnos de que esté dentro de los límites deseados.
    int leerNumero(const string& mensaje, int minimo, int maximo) {
        int numero;

        while (true) {
            cout << mensaje;

            if (cin >> numero && numero >= minimo && numero <= maximo) {
                return numero;
            }

            cout << "Ingresa un numero entre " << minimo << " y " << maximo << ".\n";
            cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada para evitar bucles infinitos en caso de entrada inválida.
        }
    }





	// esto lo podria hacer un system("pause") pero no es portable, por lo que se hace de esta manera.
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




	// Función para seleccionar un mazo de cartas de manera aleatoria, regida por la cantidad de cartas restantes en cada mazo.

    Mazo& seleccionarMazo(vector<Mazo>& mazos) {
        int totalCartas = 0;
        for (Mazo& mazo : mazos) {
            totalCartas += mazo.cartasRestantes();
        }

		//logic_error es una excepción que se lanza cuando se detecta
        // un error lógico en el programa, 
        // como intentar repartir cartas cuando no hay disponibles.

        if (totalCartas == 0) {
            throw logic_error("No hay cartas disponibles para repartir.");
        }



		// Se utiliza una distribución uniforme para seleccionar un número aleatorio entre 1 y el total de cartas restantes.

        uniform_int_distribution<int> distribucion(1, totalCartas);
        int cartaSeleccionada = distribucion(generadorAleatorio());


		// Se recorre cada mazo y se va restando la cantidad de cartas restantes
        // hasta que el numero aleatorio seleccionado sea 0 o menos
        // indicando que ese mazo es el elegido para repartir la carta.
        for (Mazo& mazo : mazos) {
            cartaSeleccionada -= mazo.cartasRestantes();
            if (cartaSeleccionada <= 0) {
                return mazo;
            }
        }
		// Si por alguna razón no se selecciona un mazo (lo cual no debería ocurrir), se devuelve el último mazo como medida de seguridad.
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











// Implementación de la clase Juego

Juego::Juego()
    : casa(), crupier(casa),
    mazo(6),
    estado(EstadoJuego::MENU), numeroRonda(0) {
    for (Mazo& mazoActual : mazo) {
        barajar(mazoActual);
    }
}




void Juego::barajar(Mazo& mazo) {
    if (mazo.estaVacio()) {
        mazo = Mazo();
    }

    shuffle(mazo.cartas.begin(), mazo.cartas.end(), generadorAleatorio());
}





void Juego::iniciar() {

    while (true) {
        limpiarPantalla();
        mostrarTitulo();
        cout << "  1. Jugar\n";
        cout << "  2. Reglas\n";
        cout << "  3. Salir\n";

        int opcion = leerNumero("\nElige una opcion: ", 1, 3);

        if (opcion == 1) {
            if (jugadores.empty()) {
                int cantidad = leerNumero("\nCuantos jugadores (1-4): ", 1, 4);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                for (int i = 0; i < cantidad; i++) {
                    string nombre;
                    cout << "Nombre del jugador " << i + 1 << ": ";
                    getline(cin, nombre);

                    if (nombre.empty()) {
                        nombre = "Jugador " + to_string(i + 1);
                    }

                    jugadores.push_back(Jugador(nombre));
                    jugadores.back().recibirFichas(1000);
                    saldosJugadores.push_back(1000);
                }
            }

            if (!hayJugadoresConDinero()) {
                cout << "\nNo hay jugadores con fichas suficientes para apostar.\n";
                pausar();
                continue;
            }

            while (hayJugadoresConDinero()) {
                iniciarRonda();

                if (estado == EstadoJuego::MENU) {
                    break;
                }

                finalizarRonda();
                pausar();
            }

            cout << "\nLa partida termino: ningun jugador puede cubrir la apuesta minima.\n";
            pausar();
        }
        else if (opcion == 2) {
            reglas();
            pausar();
        }
        else {
            cout << "\nGracias por jugar. Hasta la proxima.\n";
            return;
        }
    }
}



void Juego::reglas() {
    limpiarPantalla();
    mostrarTitulo();
    cout << "  REGLAS RAPIDAS\n\n";
    cout << "  - Cada jugador comienza con 1000 en fichas.\n";
    cout << "  - La apuesta minima es 10 y la maxima es 500.\n";
    cout << "  - El objetivo es acercarse a 21 sin pasarse.\n";
    cout << "  - Las cartas numericas valen su numero; J, Q y K valen 10.\n";
    cout << "  - El As vale 11 o 1 para evitar pasarse.\n";
    cout << "  - Al tener cartas iguales, puedes dividir tu mano en dos.\n";
    cout << "  - El crupier pide cartas hasta llegar al menos a 17.\n";
    cout << "  - Una victoria paga 1 a 1; un blackjack paga 3 a 2.\n";
    cout << "  - Un empate devuelve la apuesta.\n";
}




void Juego::iniciarRonda() {
    limpiarPantalla();
    estado = EstadoJuego::APOSTANDO;
    numeroRonda++;

    cout << "\n---------------- RONDA " << numeroRonda << " ----------------\n";
    apuestasRonda.assign(jugadores.size(), 0);

    auto repartirCarta = [this](Mano& mano) {
        bool todosVacios = true;
        for (size_t i = 0; i < mazo.size(); i++) {
            if (!mazo[i].estaVacio()) {
                todosVacios = false;
                break;
            }
        }

        if (todosVacios) {
            for (size_t i = 0; i < mazo.size(); i++) {
                barajar(mazo[i]);
            }
        }

        mano.agregarCarta(seleccionarMazo(mazo).sacarCarta());
        };

    for (size_t i = 0; i < jugadores.size(); i++) {
        jugadores[i].limpiarMano();
    }
    crupier.limpiarMano();

    for (size_t i = 0; i < jugadores.size(); i++) {
        if (saldosJugadores[i] < 10) {
            cout << jugadores[i].getNombre()
                << " no tiene fichas suficientes para apostar.\n";
            continue;
        }

        cout << "\n" << jugadores[i].getNombre()
            << " - fichas disponibles: " << saldosJugadores[i] << "\n";

        bool apuestaAceptada = false;
        while (!apuestaAceptada) {
            int monto = leerNumero("Cuanto deseas apostar: ", 10, 500);

            if (monto > saldosJugadores[i]) {
                cout << "No tienes suficientes fichas para esa apuesta.\n";
            }
            else if (!crupier.aceptarApuesta(jugadores[i], monto)) {
                cout << "La casa no puede aceptar esa apuesta. Intenta otro monto.\n";
            }
            else {


              //Si pasa ambas comprobaciones, el else procesa la apuesta:
              // entrega las fichas apostadas, 
              // descuenta esa cantidad del saldo, 
              // crea una mano y registra allí el valor apostado

                apuestasRonda[i] = jugadores[i].entregarFichasApostadas();
                saldosJugadores[i] -= apuestasRonda[i];
                jugadores[i].manos.push_back(Mano());
                jugadores[i].manos[0].valorApuesta = apuestasRonda[i];
                apuestaAceptada = true;
                cout << "Apuesta aceptada: " << apuestasRonda[i] << ".\n";
            }
        }
    }

    bool hayApuestas = false;
    for (size_t i = 0; i < apuestasRonda.size(); i++) {
        if (apuestasRonda[i] > 0) {
            hayApuestas = true;
            break;
        }
    }

    if (!hayApuestas) {
        estado = EstadoJuego::MENU;
        return;
    }
    
    estado = EstadoJuego::TURNO_JUGADOR;
    crupier.manos.push_back(Mano());

    for (int reparto = 0; reparto < 2; reparto++) {
        for (size_t i = 0; i < jugadores.size(); i++) {
            if (apuestasRonda[i] > 0) {
                repartirCarta(jugadores[i].manos[0]);
            }
        }
        repartirCarta(crupier.manos[0]);
    }

    for (size_t i = 0; i < jugadores.size(); i++) {

        if (apuestasRonda[i] == 0) {
            continue;
        }

        Mano& mano = jugadores[i].manos[0];
        bool cartasIguales = mano.cartas.size() == 2 &&
            mano.cartas[0].getNumeroCarta() == mano.cartas[1].getNumeroCarta();

        if (!cartasIguales) {
            continue;
        }

        int apuesta = mano.getValorApuesta();
        if (saldosJugadores[i] < apuesta) {
            cout << jugadores[i].getNombre()
                << " no tiene fichas suficientes para dividir la mano.\n";
            continue;
        }

        cout << jugadores[i].getNombre()
            << ", tienes dos cartas iguales. ¿Quieres dividir y duplicar la apuesta? (S/N): ";
        char respuesta;
        cin >> respuesta;

        if (respuesta != 's' && respuesta != 'S') {
            continue;
        }

        if (!crupier.aceptarApuesta(jugadores[i], apuesta)) {
            cout << "No se puede cubrir la apuesta adicional; no se divide.\n";
            continue;
        }
        
        int apuestaExtra = jugadores[i].entregarFichasApostadas();
        saldosJugadores[i] -= apuestaExtra;

        Carta cartaMovida = mano.cartas[1];
        mano.cartas.erase(mano.cartas.begin() + 1);

        Mano segundaMano;
        segundaMano.valorApuesta = apuestaExtra;
        segundaMano.agregarCarta(cartaMovida);
        jugadores[i].manos.push_back(segundaMano);

        repartirCarta(jugadores[i].manos[0]);
        repartirCarta(jugadores[i].manos[1]);
        cout << "La apuesta se duplico; ahora juegas dos manos.\n";
    }

    cout << "\nCarta visible del crupier: "
        << crupier.getMano().aTexto(true) << "\n";

    for (size_t i = 0; i < jugadores.size(); i++) {
        if (apuestasRonda[i] == 0) {
            continue;
        }

        cederTurno(jugadores[i]);
    }

    estado = EstadoJuego::TURNO_CRUPIER;
    bool crupierNecesitaCarta = false;
    for (size_t i = 0; i < apuestasRonda.size(); i++) {
        for (size_t j = 0; j < jugadores[i].manos.size(); j++) {
            if (jugadores[i].manos[j].getValorApuesta() > 0 &&
                !jugadores[i].manos[j].sePasa()) {
                crupierNecesitaCarta = true;
                break;
            }
        }
        if (crupierNecesitaCarta) {
            break;
        }
    }

    if (crupierNecesitaCarta) {
        while (crupier.quiereCarta()) {
            repartirCarta(crupier.manos[0]);
        }
    }
}



void Juego::cederTurno(Participante& p) {
    auto repartirCarta = [this](Mano& mano) {
        bool todosVacios = true;
        for (size_t i = 0; i < mazo.size(); i++) {
            if (!mazo[i].estaVacio()) {
                todosVacios = false;
                break;
            }
        }

        if (todosVacios) {
            for (size_t i = 0; i < mazo.size(); i++) {
                barajar(mazo[i]);
            }
        }

        mano.agregarCarta(seleccionarMazo(mazo).sacarCarta());
        };

    Jugador* jugador = dynamic_cast<Jugador*>(&p);
    size_t indiceJugador = jugadores.size();
    if (jugador != nullptr) {
        for (size_t i = 0; i < jugadores.size(); i++) {
            if (&jugadores[i] == jugador) {
                indiceJugador = i;
                break;
            }
        }
    }

    for (size_t i = 0; i < p.manos.size(); i++) {
        Mano& mano = p.manos[i];

        if (mano.esBlackJack()) {
            continue;
        }

        cout << "\n" << p.getNombre();
        if (p.manos.size() > 1) {
            cout << " - mano " << i + 1;
        }
        cout << ": " << mano.aTexto(false)
            << " (valor " << mano.calcularValor() << ")\n";

        if (jugador != nullptr && indiceJugador < jugadores.size() &&
            mano.cartas.size() == 2) {
            string respuestaDoblar;
            while (true) {
                cout << "¿Quieres doblar la apuesta y recibir solo una carta? (S/N): ";
                if (!(cin >> respuestaDoblar)) {
                    throw runtime_error("No se pudo leer la respuesta del jugador.");
                }

                if (respuestaDoblar == "s" || respuestaDoblar == "S" ||
                    respuestaDoblar == "n" || respuestaDoblar == "N") {
                    break;
                }

                cout << "Respuesta no valida. Ingresa s o n.\n";
            }

            if (respuestaDoblar == "s" || respuestaDoblar == "S") {
                int apuestaAdicional = mano.getValorApuesta();
                if (saldosJugadores[indiceJugador] < apuestaAdicional) {
                    cout << "No tienes fichas suficientes para doblar.\n";
                }
                else if (!crupier.aceptarApuesta(*jugador, apuestaAdicional)) {
                    cout << "La casa no puede aceptar la apuesta adicional.\n";
                }
                else {
                    int fichasDoblar = jugador->entregarFichasApostadas();
                    saldosJugadores[indiceJugador] -= fichasDoblar;
                    mano.valorApuesta += fichasDoblar;

                    repartirCarta(mano);
                    cout << "Doblaste la apuesta y recibiste "
                        << mano.cartas.back().mostrarCarta()
                        << ". Tu mano ahora vale " << mano.calcularValor() << ".\n";
                    if (mano.sePasa()) {
                        cout << "Te pasaste de 21.\n";
                    }
                    continue;
                }
            }
        }

        while (!mano.sePasa()) {
            if (!p.quiereCarta()) {
                break;
            }

            repartirCarta(mano);
            cout << "Sacaste " << mano.cartas.back().mostrarCarta();
            if (p.manos.size() > 1) {
                cout << " en la mano " << i + 1;
            }
            cout << ". Tu mano ahora vale " << mano.calcularValor() << ".\n";

            if (mano.sePasa()) {
                cout << "Te pasaste de 21.\n";
            }
        }
    }
}




void Juego::finalizarRonda() {
    estado = EstadoJuego::PAGANDO;
    crupier.revelarCarta();
    cout << "Valor del crupier: "
        << crupier.getMano().calcularValor() << "\n";

    for (size_t i = 0; i < jugadores.size(); i++) {
        if (jugadores[i].manos.empty()) {
            continue;
        }

        cout << "\n" << jugadores[i].getNombre() << ":\n";
        if (jugadores[i].manos.size() == 1) {
            cout << "  Cartas: " << jugadores[i].manos[0].aTexto(false)
                << " (valor " << jugadores[i].manos[0].calcularValor()
                << ")\n";
            ResultadoRonda resultado = resolverApuesta(jugadores[i]);
            if (resultado == ResultadoRonda::PIERDE) {
                cobrar(jugadores[i]);
            }
            else if (resultado == ResultadoRonda::GANA ||
                resultado == ResultadoRonda::BLACKJACK) {
                pagar(jugadores[i], resultado);
            }
            else {
                liquidarMano(jugadores[i], jugadores[i].manos[0],
                    resultado, casa, saldosJugadores[i]);
            }
        }
        else {
            for (size_t j = 0; j < jugadores[i].manos.size(); j++) {
                Mano& mano = jugadores[i].manos[j];
                cout << "  Mano " << j + 1 << ": " << mano.aTexto(false)
                    << " (valor " << mano.calcularValor() << ")\n";
                ResultadoRonda resultado = resolverMano(mano, crupier.getMano());
                cout << "  Resultado mano " << j + 1 << ": ";
                liquidarMano(jugadores[i], mano, resultado, casa,
                    saldosJugadores[i]);
            }
        }
    }

    estado = EstadoJuego::FIN_RONDA;
}



ResultadoRonda Juego::resolverApuesta(const Jugador& jugador) {
    return resolverMano(jugador.manos[0], crupier.getMano());
}



void Juego::pagar(Jugador& jugador, ResultadoRonda resultado) {
    for (size_t i = 0; i < jugadores.size(); i++) {
        if (&jugadores[i] == &jugador && !jugador.manos.empty()) {
            liquidarMano(jugador, jugador.manos[0], resultado, casa,
                saldosJugadores[i]);
            return;
        }
    }
}



void Juego::cobrar(Jugador& jugador) {
    for (size_t i = 0; i < jugadores.size(); i++) {
        if (&jugadores[i] == &jugador && !jugador.manos.empty()) {
            liquidarMano(jugador, jugador.manos[0], ResultadoRonda::PIERDE,
                casa, saldosJugadores[i]);
            return;
        }
    }
}



bool Juego::hayJugadoresConDinero() {
    if (casa.getDineroBanca() < 10) {
        return false;
    }

    for (size_t i = 0; i < saldosJugadores.size(); i++) {
        if (saldosJugadores[i] >= 10) {
            return true;
        }
    }

    return false;
}