#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "fuentes.h"
#include "tipos.h"


void Pantalla_Inicio(tFuente *fuente, int *juego, uint8_t mat[FILAS][COLS], int coords_pieza[8], int *figura_tipo, int *p_caidas, float *vel_actual, int *modo_deluxe, tPuntuacion *puntuacion);
void Guardar_Partida_Archivo(uint8_t mat[FILAS][COLS], int coords_pieza[8], int figura_tipo, int p_caidas, float vel_actual, tPuntuacion *puntuacion, int modo_deluxe);
void Pausar_Juego (tFuente *fuente, int *juego, uint8_t mat[FILAS][COLS], int coords_pieza[8], int figura_tipo, int p_caidas, float vel_actual, tPuntuacion *puntuacion, int modo_deluxe);

#endif // MENU_H_INCLUDED
