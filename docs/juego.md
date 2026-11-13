# Guía de juego - Black-Jack-UNA

## 1. Introducción
Este proyecto implementa una versión de Blackjack para consola, donde el jugador compite contra el crupier. El objetivo principal es obtener una mano con valor lo más cercano posible a 21, sin pasarse.

El juego se desarrolla en la terminal, con menú de opciones, apuestas, turnos del jugador y del crupier, y resultados de cada ronda.

---

## 2. Objetivo del juego
Cada jugador intenta ganar al crupier logrando una de estas situaciones:

- Obtener 21 con dos cartas iniciales: Blackjack.
- Alcanzar un valor mayor que el del crupier sin superar 21.
- Hacer que el crupier se pase de 21.

Si el jugador supera 21, pierde automáticamente la mano.

---

## 3. Valor de las cartas
En este juego, el valor de las cartas funciona así:

- Numeros del 2 al 9: valor nominal.
- 10, J, Q, K: valen 10.
- As: vale 11, pero si al sumar cartas la mano se pasa, el As puede cambiar a 1 para evitar perder.

Ejemplo:
- As + 8 = 19
- As + 9 + 5 = 15 (el As pasa a valer 1)
- 10 + 6 + 5 = 21

---

## 4. Inicio de la partida
Al iniciar el programa aparece un menú principal con estas opciones:

1. Jugar
2. Reglas
3. Salir

Si eliges jugar, el sistema te pedirá cuántos jugadores participan y luego solicitará el nombre de cada uno.

Cada jugador empieza con 1000 fichas.

---

## 5. Apuestas
Antes de cada ronda, cada jugador debe apostar una cantidad válida.

En este proyecto:
- apuesta mínima: 10
- apuesta máxima: 500

Si un jugador intenta apostar más de lo que tiene, el sistema no acepta la apuesta.

El crupier solo acepta apuestas si la casa puede cubrir la mano.

---

## 6. Desarrollo de una ronda
Una vez realizadas las apuestas, se reparten dos cartas a cada jugador y dos al crupier. Una de las cartas del crupier queda visible y la otra permanece ocultada hasta el final.

### Turno del jugador
Cada jugador decide si:

- pedir otra carta,
- plantarse,
- doblar la apuesta,
- dividir mano (si tiene dos cartas iguales).

### Pedir carta
Cuando el jugador decide pedir carta:
- recibe una nueva carta,
- se recalcula el valor de su mano,
- si supera 21, pierde esa mano.

### Plantarse
Si el jugador se planta, se queda con el valor actual de su mano y se pasa al turno del crupier.

---

## 7. Doble apuesta
Si el jugador tiene exactamente dos cartas y desea aumentar su riesgo, puede doblar.

El sistema pregunta:

```text
¿Quieres doblar la apuesta y recibir solo una carta? (S/N)
