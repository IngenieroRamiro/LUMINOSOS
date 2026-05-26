#include "colision.h"

int verificar_colision(uint8_t mat[FILAS][COLS], int pieza[], int tam)
{
    int prox_f;
    int c;

    for (int i = 0; i < tam; i += 2)
    {
        prox_f = pieza[i] + 1;
        c = pieza[i+1];

        if (prox_f >= FILAS || (prox_f >= 0 && mat[prox_f][c] == 2))
            return 1;
    }

    return 0;
}

int fin_juego(uint8_t mat[FILAS][COLS], int pieza[])
{
    int f;
    int c;

    for(int i=0; i<8 ; i+=2)
    {
        f=pieza[i];
        c=pieza[i+1];
        if(f>=0 && mat[f][c]==2)
            return 1;
    }
    return 0;
}
