#include "piezas.h"

static const int FORMAS[7][8] =
{
    {1,3,1,4,1,5,1,6},
    {2,4,2,5,2,6,1,6},
    {2,4,2,5,2,6,1,4},
    {2,4,2,5,1,5,1,6},
    {2,5,2,6,1,4,1,5},
    {1,4,1,5,2,4,2,5},
    {2,3,2,4,2,5,1,4}
};

void pieza_generar(tPieza* p, int tipo)
{
    p->tipo = tipo;
    p->color = pieza_color(tipo);

    for (int i = 0; i < BLOQUES; i++)
    {
        p->bloques[i].f = FORMAS[tipo][i * 2];
        p->bloques[i].c = FORMAS[tipo][i * 2 + 1];
    }
}

int pieza_puede_mover(const tTablero* t, const tPieza* p, int moverF, int moverC)
{
    for (int i = 0; i < BLOQUES; i++)
    {
        int nuevaF = p->bloques[i].f + moverF;
        int nuevaC = p->bloques[i].c + moverC;

        if (tablero_ocupado(t, nuevaF, nuevaC))
            return 0;
    }

    return 1;
}

void pieza_mover(tPieza* p, int moverF, int moverC)
{
    for (int i = 0; i < BLOQUES; i++)
    {
        p->bloques[i].f += moverF;
        p->bloques[i].c += moverC;
    }
}

int pieza_puede_rotar(const tTablero* t, const tPieza* p)
{
    tBloque pivot = p->bloques[1];

    if (p->tipo == 5)
        return 0;

    for (int i = 0; i < BLOQUES; i++)
    {
        int moverF = p->bloques[i].f - pivot.f;
        int moverC = p->bloques[i].c - pivot.c;

        int nf = pivot.f + moverC;
        int nc = pivot.c - moverF;

        if (tablero_ocupado(t, nf, nc))
            return 0;
    }

    return 1;
}

void pieza_rotar(tPieza* p)
{
    tBloque pivot = p->bloques[1];

    for (int i = 0; i < BLOQUES; i++)
    {
        int moverF = p->bloques[i].f - pivot.f;
        int moverC = p->bloques[i].c - pivot.c;

        p->bloques[i].f = pivot.f + moverC;
        p->bloques[i].c = pivot.c - moverF;
    }
}

void pieza_fijar(tTablero* t, const tPieza* p)
{
    for (int i = 0; i < BLOQUES; i++)
    {
        tablero_fijar_celda(t, p->bloques[i].f, p->bloques[i].c, 11);
    }
}

int pieza_color(int figura)
{
    const int colores[] = {1, 176, 126};

    return colores[figura % 3];
}

/// ////////////////////// ///
/// ARQUITECTURA ANTERIOR ///

/*


#include "piezas.h"
#include <stdlib.h>


void reiniciar_pieza(int mat_coor[PIEZAS][8], int pieza_a_resetear)
{
    const int plantillas[7][8] =
    {
        {0,3,0,4,0,5,0,6}, // I
        {1,4,1,5,1,6,0,6}, // L
        {1,4,1,5,1,6,0,4}, // J
        {1,4,1,5,0,5,0,6}, // S
        {1,5,1,6,0,4,0,5}, // Z
        {0,4,0,5,1,4,1,5}, // O
        {1,3,1,4,1,5,0,4}  // T
    };

    for(int i = 0; i < 8; i++)
        mat_coor[pieza_a_resetear][i] = plantillas[pieza_a_resetear][i];
}

void rotar_universal(int pieza[8], uint8_t tablero[FILAS][COLS])
{
    int f_pivote = pieza[2], c_pivote = pieza[3], aux[8], posible = 1;
    int f_rel, c_rel;

    for (int i = 0; i < 8; i += 2)
    {
        f_rel = pieza[i] - f_pivote;
        c_rel = pieza[i+1] - c_pivote;

        aux[i] = f_pivote + c_rel;
        aux[i+1] = c_pivote - f_rel;

        if (aux[i] < 0 || aux[i] >= FILAS ||
            aux[i+1] < 0 || aux[i+1] >= COLS ||
            tablero[aux[i]][aux[i+1]] == 2)
        {
            posible = 0;
            break;
        }
    }

    if (posible)
    {
        for (int i = 0; i < 8; i++)
            pieza[i] = aux[i];
    }
}

void mover_derecha(int pieza[8], uint8_t tablero[FILAS][COLS])
{
    int posible = 1;
    int c_nueva;

    for (int i = 0; i < 8; i += 2)
    {
        c_nueva = pieza[i+1] + 1;

        if (c_nueva >= COLS || tablero[pieza[i]][c_nueva] == 2)
        {
            posible = 0;
            break;
        }
    }

    if (posible)
    {
        for (int i = 1; i < 8; i += 2)
            pieza[i]++;
    }
}

void mover_izquierda(int pieza[8], uint8_t tablero[FILAS][COLS])
{
    int posible = 1;

    for (int i = 0; i < 8; i += 2)
    {
        int c_nueva = pieza[i+1] - 1;

        if (c_nueva < 0 || tablero[pieza[i]][c_nueva] == 2)
        {
            posible = 0;
            break;
        }
    }

    if (posible)
    {
        for (int i = 1; i < 8; i += 2)
            pieza[i]--;
    }
}*/
