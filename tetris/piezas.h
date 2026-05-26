#ifndef PIEZAS_H
#define PIEZAS_H

#include "tablero.h"

#define BLOQUES 4

typedef struct
{
    int f;
    int c;
} tBloque;

typedef struct
{
    tBloque bloques[BLOQUES];
    int tipo;
    int color;
} tPieza;

void pieza_generar(tPieza* p, int tipo);

int pieza_puede_mover(const tTablero* t, const tPieza* p, int moverF, int moverC);
void pieza_mover(tPieza* p, int moverF, int moverC);

int pieza_puede_rotar(const tTablero* t, const tPieza* p);
void pieza_rotar(tPieza* p);

void pieza_fijar(tTablero* t, const tPieza* p);

int pieza_color(int figura);

#endif


/// ////////////////////// ///
/// ARQUITECTURA ANTERIOR ///

/*


#ifndef PIEZAS_H
#define PIEZAS_H

#include <stdint.h>
#include "tipos.h"

void reiniciar_pieza(int mat_coor[PIEZAS][8], int pieza_a_resetear);

void rotar_universal(int pieza[8], uint8_t tablero[FILAS][COLS]);

void mover_derecha(int pieza[8], uint8_t tablero[FILAS][COLS]);

void mover_izquierda(int pieza[8], uint8_t tablero[FILAS][COLS]);

#endif*/
