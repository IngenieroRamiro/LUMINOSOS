#include "piezas.h"

void reiniciar_pieza(int pieza[8])
{
    int iniciales[8] = {0,3,0,4,0,5,0,6};

    for(int i=0; i<8; i++)
        pieza[i] = iniciales[i];
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
