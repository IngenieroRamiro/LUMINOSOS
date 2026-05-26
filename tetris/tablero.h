#ifndef TABLERO_H
#define TABLERO_H

#include <stdint.h>
#include "tipos.h"

void Reiniciar_Tablero(uint8_t mat[FILAS][COLS]);
void borrar(uint8_t mat[FILAS][COLS], int mat_coor[], int tam);
void figuras_caen(uint8_t mat[FILAS][COLS], int mat_coor[], int tam);
void fijar_pieza(uint8_t mat[FILAS][COLS], int pieza[], int tam);
int eliminar_lineas(uint8_t mat[FILAS][COLS]);

#endif // TABLERO_H
