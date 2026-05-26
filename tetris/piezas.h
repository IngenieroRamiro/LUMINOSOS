#ifndef PIEZAS_H
#define PIEZAS_H

#include <stdint.h>
#include "tipos.h"

void reiniciar_pieza(int mat_coor[PIEZAS][8], int pieza_a_resetear);

void reiniciar_pieza_10(int mat_coordenads[11][10], int figura);

void rotar_universal(int pieza[8], uint8_t tablero[FILAS][COLS]);

void mover_derecha(int pieza[8], uint8_t tablero[FILAS][COLS]);

void mover_izquierda(int pieza[8], uint8_t tablero[FILAS][COLS]);

void rotar_deluxe(int coords_pieza[10], uint8_t tablero[FILAS][COLS]);

#endif
