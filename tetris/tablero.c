#include "tablero.h"
#include <stdlib.h>
#include <string.h>

int tablero_crear(tTablero* t, int filas, int columnas)
{
    t->filas = filas;
    t->columnas = columnas;

    t->celdas = malloc(sizeof(tCelda*) * filas);

    if (!t->celdas)
        return 0;

    for (int i = 0; i < filas; i++)
    {
        t->celdas[i] = calloc(columnas, sizeof(tCelda));

        if (!t->celdas[i])
        {
            for (int j = 0; j < i; j++)
                free(t->celdas[j]);

            free(t->celdas);
            return 0;
        }
    }

    return 1;
}

void tablero_destruir(tTablero* t)
{
    for (int i = 0; i < t->filas; i++)
        free(t->celdas[i]);

    free(t->celdas);
    t->celdas = NULL;
}

void tablero_limpiar(tTablero* t)
{
    for (int i = 0; i < t->filas; i++)
        memset(t->celdas[i], 0, t->columnas * sizeof(tCelda));
}

int tablero_dentro(const tTablero* t, int f, int c)
{
    return ((f >= 0) && (f < t->filas) && (c >= 0) && (c < t->columnas));
}

int tablero_ocupado(const tTablero* t, int f, int c)
{
    if (!tablero_dentro(t, f, c))
        return 1;

    return t->celdas[f][c] != 0;
}

void tablero_fijar_celda(tTablero* t, int f, int c, uint8_t valor)
{
    if (tablero_dentro(t, f, c))
        t->celdas[f][c] = valor;
}

static int fila_completa(const tTablero* t, int fila)
{
    for (int c = 0; c < t->columnas; c++)
    {
        if (t->celdas[fila][c] == 0)
            return 0;
    }

    return 1;
}

int eliminar_lineas(tTablero* t)
{
    int eliminadas = 0;

    for (int f = t->filas - 1; f >= 0; f--)
    {
        if (fila_completa(t, f))
        {
            tCelda* aux = t->celdas[f];

            for (int k = f; k > 0; k--)
                t->celdas[k] = t->celdas[k - 1];

            t->celdas[0] = aux;

            memset(t->celdas[0], 0, t->columnas * sizeof(tCelda));

            eliminadas++;
            f++;
        }
    }

    return eliminadas;
}


/// ////////////////////// ///
/// ARQUITECTURA ANTERIOR ///

/*

#include "tablero.h"

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
}*/
