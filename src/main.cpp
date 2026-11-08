#include "Juego.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main() {

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    Juego main;
    main.iniciar();

    return 0;
}