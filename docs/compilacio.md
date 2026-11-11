# Compilación del proyecto Black-Jack

## 1. Descripción
Este proyecto es una implementación en C++ del juego Blackjack para consola. La lógica del juego se encuentra principalmente en `src/Juego.cpp` y el punto de entrada es `src/main.cpp`.

El programa permite:
- iniciar partidas con jugadores,
- realizar apuestas,
- repartir cartas,
- pedir carta o plantarse,
- manejar el turno del crupier,
- pagar y cobrar según el resultado de la ronda.

## 2. Requisitos
Para compilar el proyecto necesitas:
- Visual Studio 2022 o un compilador de C++ compatible con C++17.
- Si vas a usar la línea de comandos, debes abrir una terminal de Microsoft Developer Command Prompt o una terminal con `cl.exe` disponible en el PATH.
- El proyecto no usa librerías externas ni dependencias adicionales.

## 3. Compilación con el comando `cl`
Desde la raíz del proyecto, abre una terminal de desarrollador de Visual Studio y ejecuta:

```bat
cd /d "d:\Descargas\Black\Black-Jack-UNA"
cl /EHsc /I src src\Carta.cpp src\Casa.cpp src\Crupier.cpp src\Ficha.cpp src\Juego.cpp src\Jugador.cpp src\main.cpp src\Mazo.cpp src\Mano.cpp src\Participante.cpp /Fe:BlackJack-UNA.exe








Contenido para `guia-visual-studio.md`:

```md
# Guía de compilación en Visual Studio

## 1. Descripción
Esta guía explica cómo compilar el proyecto Black-Jack usando Visual Studio 2022.

El proyecto está organizado dentro de la carpeta `src`, donde se encuentran todos los archivos `.cpp` y `.h` necesarios para la aplicación.

## 2. Requisitos
Necesitas:
- Visual Studio 2022
- Carga de trabajo de "Desarrollo de escritorio con C++"
- El proyecto descargado en tu computadora

## 3. Método 1: Crear un proyecto nuevo en Visual Studio
1. Abre Visual Studio 2022.
2. Selecciona "Crear un proyecto".
3. Elige "Aplicación de consola" o "Proyecto vacío" en C++.
4. Asigna un nombre al proyecto, por ejemplo: `BlackJack-UNA`.
5. Guarda el proyecto en la carpeta raíz del repositorio.
6. En el explorador del proyecto, agrega todos los archivos `.cpp` que están en `src`.

### Archivos que debes agregar
- `main.cpp`
- `Carta.cpp`
- `Casa.cpp`
- `Crupier.cpp`
- `Ficha.cpp`
- `Juego.cpp`
- `Jugador.cpp`
- `Mazo.cpp`
- `Mano.cpp`
- `Participante.cpp`

También puedes agregar los archivos `.h` para mantener la estructura ordenada.

## 4. Método 2: Abrir la carpeta del proyecto
1. Abre Visual Studio.
2. Selecciona "Abrir una carpeta".
3. Elige la carpeta raíz del proyecto `Black-Jack-UNA`.
4. Visual Studio detectará la estructura del proyecto.
5. Compila presionando `Ctrl + Shift + B` o usando la opción "Compilar".
6. Si todo está bien, ejecuta el programa con `F5`.

## 5. Configuración importante
Asegúrate de que:
- `main.cpp` esté como archivo principal.
- Todos los archivos de `src` estén dentro del proyecto.
- El proyecto esté configurado en modo `Debug` o `Release`.
- La carpeta `src` esté incluida correctamente en la solución.

## 6. Compilar con el compilador de Visual Studio
Si prefieres compilar desde la línea de comandos, puedes usar el compilador `cl` de Visual Studio. Para ello, abre "Developer Command Prompt for VS 2022" y ejecuta:

```bat
cd /d "d:\Descargas\Black\Black-Jack-UNA"
cl /EHsc /I src src\Carta.cpp src\Casa.cpp src\Crupier.cpp src\Ficha.cpp src\Juego.cpp src\Jugador.cpp src\main.cpp src\Mazo.cpp src\Mano.cpp src\Participante.cpp /Fe:BlackJack-UNA.exe
