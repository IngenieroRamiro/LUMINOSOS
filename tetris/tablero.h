#ifndef TABLERO_H
#define TABLERO_H

#include <stdint.h>
#include "tipos.h"

void borrar(uint8_t mat[FILAS][COLS], int mat_coor[PIEZAS][8], int *j, int *nivel);

void figuras_caen(uint8_t mat[FILAS][COLS], int mat_coor[PIEZAS][8], int *j, int *nivel);

void figueras_tetris(uint8_t mat[FILAS][COLS], int mat_coor[PIEZAS][8], int *j, int *nivel);

void fijar_pieza(uint8_t mat[FILAS][COLS], int pieza[8]);

int eliminar_lineas(uint8_t mat[FILAS][COLS]);

#endif /* TABLERO_H */
