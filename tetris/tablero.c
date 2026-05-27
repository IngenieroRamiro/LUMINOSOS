#include "tablero.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "piezas.h"
#include "puntuacion.h"

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

int partida_guardar(const char* ruta, int modo_juego, const tTablero* t, const void* p, const void* punt, float velocidad, int caidas)
{
    FILE* f = fopen(ruta, "wb");
    if (!f) return 0;

    fwrite(&modo_juego, sizeof(int), 1, f);
    fwrite(&t->filas, sizeof(int), 1, f);
    fwrite(&t->columnas, sizeof(int), 1, f);
    fwrite(p, sizeof(tPieza), 1, f);
    fwrite(punt, sizeof(tPuntuacion), 1, f);
    fwrite(&velocidad, sizeof(float), 1, f);
    fwrite(&caidas, sizeof(int), 1, f);

    for (int i = 0; i < t->filas; i++)
    {
        fwrite(t->celdas[i], sizeof(tCelda), t->columnas, f);
    }

    fclose(f);
    return 1;
}

int partida_cargar(const char* ruta, int* modo_juego, tTablero* t, void* p, void* punt, float* velocidad, int* caidas)
{
    FILE* f = fopen(ruta, "rb");
    if (!f) return 0;

    int filas, columnas;

    fread(modo_juego, sizeof(int), 1, f);
    fread(&filas, sizeof(int), 1, f);
    fread(&columnas, sizeof(int), 1, f);
    fread(p, sizeof(tPieza), 1, f);
    fread(punt, sizeof(tPuntuacion), 1, f);
    fread(velocidad, sizeof(float), 1, f);
    fread(caidas, sizeof(int), 1, f);

    tablero_destruir(t);
    tablero_crear(t, filas, columnas);

    for (int i = 0; i < t->filas; i++)
    {
        fread(t->celdas[i], sizeof(tCelda), t->columnas, f);
    }

    fclose(f);
    return 1;
}
