#include "tablero.h"

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

    // voy de abajo para arriba, asi cuando elimino una fila y todo cae, vuelvo a fijarme la misma posicion
    while (f >= 0)
    {
        // me fijo  si la fila f esta toda en 2
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
            // corro cada fila de arriba un escalon hacia abajo
            for (int k = f; k > 0; k--)
            {
                uint8_t *dst = mat[k];
                uint8_t *src = mat[k-1];
                uint8_t *tope = src + COLS;

                while (src < tope)
                    *dst++ = *src++;
            }

            // la fila 0 queda vacia
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
