#include "stdio.h"
#include "tablero.h"
#include "tipos.h"

void borrar(uint8_t mat[FILAS][COLS], int mat_coor[])
{
    int j;

    for (j = 0; j < 7; j += 2)
    {
        int f = mat_coor[j];
        int c = mat_coor[j + 1];

        if (f >= 0 && f < FILAS && mat[f][c] == 1)
        {
            mat[f][c] = 0;
        }
    }

    for (j = 0; j < 7; j += 2)
    {
        mat_coor[j] = mat_coor[j] + 1;
    }
}

void figuras_caen(uint8_t mat[FILAS][COLS], int mat_coor[])
{
    int j;
    for (j = 0; j < 7; j = j + 2)
    {
        int f = mat_coor[j];

        int c = mat_coor[j + 1];

        if (f >= 0 && f < FILAS)
        {
            mat[f][c] = 1;
        }
    }
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

void Reiniciar_Tablero (uint8_t mat[FILAS][COLS])
{
    for (int f = 0; f < FILAS; f++)
    {
        for (int c = 0; c < COLS; c++)
        {
            mat[f][c] = 0;
        }
    }
}

int Cargar_Partida_Archivo(uint8_t mat[FILAS][COLS], int coords_pieza[8], int *figura_tipo, int *p_caidas, float *vel_actual, tPuntuacion *puntuacion, int *modo_deluxe)
{
    FILE *arch = fopen("partida.sav", "rb");
    if (arch == NULL) return 0;

    fread(mat, sizeof(uint8_t), FILAS * COLS, arch);

    fread(coords_pieza, sizeof(int), 8, arch);

    fread(figura_tipo, sizeof(int), 1, arch);
    fread(p_caidas, sizeof(int), 1, arch);
    fread(vel_actual, sizeof(float), 1, arch);

    fread(puntuacion, sizeof(tPuntuacion), 1, arch);

    fread(modo_deluxe, sizeof(int), 1, arch);

    fclose(arch);
    return 1; // Éxito
}
