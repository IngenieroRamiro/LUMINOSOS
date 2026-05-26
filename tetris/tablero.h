#ifndef TABLERO_H
#define TABLERO_H

#include <stdint.h>
#include "tipos.h"
#include "puntuacion.h"

void borrar(uint8_t mat[FILAS][COLS], int mat_coor[]);

void figuras_caen(uint8_t mat[FILAS][COLS], int mat_coor[]);

void fijar_pieza(uint8_t mat[FILAS][COLS], int pieza[8]);

int eliminar_lineas(uint8_t mat[FILAS][COLS]);

void Reiniciar_Tablero (uint8_t mat[FILAS][COLS]);

int Cargar_Partida_Archivo(uint8_t mat[FILAS][COLS], int coords_pieza[8], int *figura_tipo, int *p_caidas, float *vel_actual, tPuntuacion *puntuacion, int *modo_deluxe);

#endif /* TABLERO_H */
