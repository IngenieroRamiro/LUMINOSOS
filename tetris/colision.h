#ifndef COLISION_H
#define COLISION_H

#include <stdint.h>
#include "tipos.h"

int verificar_colision(uint8_t mat[FILAS][COLS], int pieza[8]);
int fin_juego(uint8_t mat[FILAS][COLS], int pieza[]);

#endif/* COLISION_H */
