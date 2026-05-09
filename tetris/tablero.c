#include "tablero.h"

void borrar(uint8_t mat[FILAS][COLS], int mat_coor[PIEZAS][8], int *j, int *nivel)
{
    for ((*j) = 0; (*j) < 7; (*j) += 2)
    {
        int f = mat_coor[PRUEBA][*j];
        int c = mat_coor[PRUEBA][*j + 1];

        if (f >= 0 && f < FILAS && mat[f][c] == 1)
        {
            mat[f][c] = 0;
        }
    }

    for ((*j) = 0; (*j) < 7; (*j) += 2)
    {
        mat_coor[PRUEBA][*j] = mat_coor[PRUEBA][*j] + 1;
    }
}

void figuras_caen(uint8_t mat[FILAS][COLS], int mat_coor[PIEZAS][8], int *j, int *nivel)
{
    for ((*j) = 0; (*j) < 7; (*j) = (*j) + 2)
    {
        int f = mat_coor[PRUEBA][*j];

        int c = mat_coor[PRUEBA][*j + 1];

        if (f >= 0 && f < FILAS)
        {
            mat[f][c] = 1;
        }
    }
}

void figueras_tetris(uint8_t mat[FILAS][COLS], int mat_coor[PIEZAS][8], int *j, int *nivel)
{
    figuras_caen(mat, mat_coor, j, nivel);
}

void fijar_pieza(uint8_t mat[FILAS][COLS], int pieza[8])
{
    int f;
    int c;

    for (int i = 0; i < 8; i += 2)
    {
        f = pieza[i];
        c = pieza[i+1];

        if (f >= 0 && f < FILAS)
            mat[f][c] = 2;
    }
}

int eliminar_lineas(uint8_t mat[FILAS][COLS])
{
    int eliminadas = 0;
    int f = FILAS - 1;

    while (f >= 0)
    {
        int completa = 1;
        uint8_t *p   = mat[f];
        uint8_t *fin = mat[f] + COLS;

        while (p < fin)
        {
            if (*p != 2)
            {
                completa = 0;
                break;
            }
            p++;
        }

        if (completa)
        {
            for (int k = f; k > 0; k--)
            {
                uint8_t *dst = mat[k];
                uint8_t *src = mat[k-1];
                uint8_t *tope = src + COLS;

                while (src < tope)
                    *dst++ = *src++;
            }

            uint8_t *q   = mat[0];
            uint8_t *qfin = mat[0] + COLS;

            while (q < qfin)
                *q++ = 0;

            eliminadas++;
        }
        else
        {
            f--;
        }
    }

    return eliminadas;
}
