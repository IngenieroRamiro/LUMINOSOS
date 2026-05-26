#ifndef TABLERO_H
#define TABLERO_H

#include <stdint.h>
#include "tipos.h"

typedef uint8_t tCelda;

typedef struct
{
    tCelda** celdas;
    int filas;
    int columnas;
} tTablero;

int tablero_crear(tTablero* t, int filas, int columnas);
void tablero_destruir(tTablero* t);
void tablero_limpiar(tTablero* t);

int tablero_dentro(const tTablero* t, int f, int c);
int tablero_ocupado(const tTablero* t, int f, int c);

void tablero_fijar_celda(tTablero* t, int f, int c, uint8_t valor);

int eliminar_lineas(tTablero* t);

#endif



/// ////////////////////// ///
/// ARQUITECTURA ANTERIOR ///

/*

#ifndef TABLERO_H
#define TABLERO_H

#include <stdint.h>
#include "tipos.h"

void borrar(uint8_t mat[FILAS][COLS], int mat_coor[]);

void figuras_caen(uint8_t mat[FILAS][COLS], int mat_coor[]);

void fijar_pieza(uint8_t mat[FILAS][COLS], int pieza[8]);

int eliminar_lineas(uint8_t mat[FILAS][COLS]);

void Reiniciar_Tablero (uint8_t mat[FILAS][COLS]);

#endif*/
