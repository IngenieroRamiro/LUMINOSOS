#ifndef COLISION_H
#define COLISION_H

#include "tipos.h"

int verificar_colision(uint8_t mat[FILAS][COLS], int pieza[8]);
void rotar_universal(int pieza[8], uint8_t tablero[FILAS][COLS]);
void mover_derecha(int pieza[8], uint8_t tablero[FILAS][COLS]);
void mover_izquierda(int pieza[8], uint8_t tablero[FILAS][COLS]);

#endif /* COLISION_H */
