#ifndef TABLERO_H
#define TABLERO_H

#include "tipos.h"

void fijar_pieza(uint8_t mat[FILAS][COLS], int pieza[8]);
int eliminar_lineas(uint8_t mat[FILAS][COLS]);

#endif /* TABLERO_H */
