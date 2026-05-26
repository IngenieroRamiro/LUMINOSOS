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

void reiniciar_pieza_10(int mat_coordenads[11][10], int figura)
{
    int moldes[11][10] =
    {
        // Clásicas
        {0,3, 0,4, 0,5, 0,6,  0,0}, // I
        {1,4, 1,5, 1,6, 0,6,  0,0}, // J
        {1,4, 1,5, 1,6, 0,4,  0,0}, // L
        {1,4, 1,5, 0,5, 0,6,  0,0}, // O
        {1,5, 1,6, 0,4, 0,5,  0,0}, // S
        {0,4, 0,5, 1,4, 1,5,  0,0}, // Z
        {1,3, 1,4, 1,5, 0,4,  0,0}, // T
        // Deluxe
        {0,5, 0,5, 0,5, 0,5,  0,5}, // 7) Monomino
        {0,4, 0,5, 1,4, 2,4,  2,5}, // 8) Forma de C
        {0,4, 0,5, 1,4, 1,5,  2,4}, // 9) Forma de P
        {0,4, 0,6, 1,4, 1,6,  2,5}  // 10) Forma de U
    };

    for (int i = 0; i < 10; i++)
    {
        mat_coordenads[figura][i] = moldes[figura][i];
    }
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
}

void rotar_deluxe(int coords[10], uint8_t tablero[FILAS][COLS])
{
    int f_pivote = coords[2];
    int c_pivote = coords[3];
    int coords_nuevas[10];
    int puede_rotar = 1;

    for (int i = 0; i < 10; i += 2)
    {
        int f_actual = coords[i];
        int c_actual = coords[i + 1];

        if (c_actual - c_pivote > COLS / 2)
        {
            c_actual -= COLS;
        }
        else if (c_pivote - c_actual > COLS / 2)
        {
            c_actual += COLS;
        }

        int f_nueva = f_pivote + (c_actual - c_pivote);
        int c_nueva = c_pivote - (f_actual - f_pivote);

        if (c_nueva < 0)
        {
            c_nueva = (c_nueva % COLS) + COLS;
        }
        c_nueva %= COLS;

        coords_nuevas[i] = f_nueva;
        coords_nuevas[i + 1] = c_nueva;
    }

    for (int i = 0; i < 10; i += 2)
    {
        int f = coords_nuevas[i];
        int c = coords_nuevas[i + 1];

        if (f < 0 || f >= FILAS || tablero[f][c] != 0)
        {
            puede_rotar = 0;
            break;
        }
    }

    if (puede_rotar)
    {
        for (int i = 0; i < 10; i++)
        {
            coords[i] = coords_nuevas[i];
        }
    }
}
