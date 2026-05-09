#include "piezas.h"

void borrar(uint8_t mat[FILAS][COLS], int mat_coor[PIEZAS][8], int *j, int *nivel)
{
    (void)nivel;

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
    (void)nivel;

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

void reiniciar_pieza(int pieza[8])
{
    int iniciales[8] = {0,3,0,4,0,5,0,6};

    for(int i=0; i<8; i++)
        pieza[i] = iniciales[i];
}
