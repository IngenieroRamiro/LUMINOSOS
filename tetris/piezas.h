#ifndef PIEZAS_H
#define PIEZAS_H

#include "tablero.h"
#include "tipos.h"

typedef struct
{
    int f;
    int c;
} tBloque;

typedef struct
{
    tBloque bloques[MAX_BLOQUES];
    int cant_bloques;
    int tipo;
    int color;
} tPieza;

void pieza_generar(tPieza* p, int tipo);
int pieza_puede_mover(const tTablero* t, const tPieza* p, int moverF, int moverC);
void pieza_mover(tPieza* p, int moverF, int moverC);
int pieza_puede_rotar(const tTablero* t, const tPieza* p, int sentido);
void pieza_rotar(tPieza* p, int sentido);
void pieza_fijar(tTablero* t, const tPieza* p);
int pieza_color(int figura);
void pieza_rotar_deluxe(const tTablero* t, tPieza* p, int sentido);
void pieza_mover_deluxe_horizontal(const tTablero* t, tPieza* p, int moverC);

#endif
