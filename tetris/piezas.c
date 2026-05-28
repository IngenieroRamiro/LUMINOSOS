#include "piezas.h"
#include <stdlib.h>

// Matriz de 11 figuras unificadas
static const int FORMAS_UNIFICADAS[11][10] =
{
    {1,3, 1,4, 1,5, 1,6,  0,0}, // I
    {2,4, 2,5, 2,6, 1,6,  0,0}, // J
    {2,4, 2,5, 2,6, 1,4,  0,0}, // L
    {2,4, 2,5, 1,5, 1,6,  0,0}, // O
    {2,5, 2,6, 1,4, 1,5,  0,0}, // S
    {1,4, 1,5, 2,4, 2,5,  0,0}, // Z
    {2,3, 2,4, 2,5, 1,4,  0,0}, // T
    // Deluxe
    {0,5, 0,5, 0,5, 0,5,  0,5}, // 7) Monomino
    {0,4, 0,5, 1,4, 2,4,  2,5}, // 8) Forma de C
    {0,4, 0,5, 1,4, 1,5,  2,4}, // 9) Forma de P
    {0,4, 0,6, 1,4, 1,6,  2,5}  // 10) Forma de U
};

void pieza_generar(tPieza* p, int tipo)
{
    p->tipo = tipo;
    p->color = pieza_color(tipo);
    p->cant_bloques = (tipo >= 7) ? 5 : 4;

    const int* fila_matriz = *(FORMAS_UNIFICADAS + tipo);
    tBloque* b = p->bloques;

    for (int i = 0; i < p->cant_bloques; i++)
    {
        (b + i)->f = *(fila_matriz + (i * 2));
        (b + i)->c = *(fila_matriz + (i * 2 + 1));
    }
}

int pieza_puede_mover(const tTablero* t, const tPieza* p, int moverF, int moverC)
{
    const tBloque* b = p->bloques;

    for (int i = 0; i < p->cant_bloques; i++)
    {
        int nuevaF = (b + i)->f + moverF;
        int nuevaC = (b + i)->c + moverC;

        if (tablero_ocupado(t, nuevaF, nuevaC))
            return 0;
    }
    return 1;
}

void pieza_mover(tPieza* p, int moverF, int moverC)
{
    tBloque* b = p->bloques;

    for (int i = 0; i < p->cant_bloques; i++)
    {
        (b + i)->f += moverF;
        (b + i)->c += moverC;
    }
}

void pieza_mover_deluxe_horizontal(const tTablero* t, tPieza* p, int moverC)
{
    tPieza copia = *p;
    tBloque* b_copia = copia.bloques;

    for (int i = 0; i < copia.cant_bloques; i++)
    {
        (b_copia + i)->c += moverC;
        if ((b_copia + i)->c >= t->columnas) (b_copia + i)->c = 0;
        if ((b_copia + i)->c < 0) (b_copia + i)->c = t->columnas - 1;
    }

    int choca = 0;
    for (int i = 0; i < copia.cant_bloques; i++)
    {
        if (tablero_dentro(t, (b_copia + i)->f, (b_copia + i)->c) &&
            *(*(t->celdas + (b_copia + i)->f) + (b_copia + i)->c) != 0)
        {
            choca = 1;
            break;
        }
    }
    if (!choca)
    {
        *p = copia;
    }
}

int pieza_puede_rotar(const tTablero* t, const tPieza* p, int sentido)
{
    if (p->tipo == 5) return 0;

    const tBloque* b = p->bloques;
    tBloque pivot = *(b + 1);

    for (int i = 0; i < p->cant_bloques; i++)
    {
        int moverF = (b + i)->f - pivot.f;
        int moverC = (b + i)->c - pivot.c;

        int nf, nc;

        if(sentido) // 1 = izquierda
        {
            nf = pivot.f - moverC;
            nc = pivot.c + moverF;
        }else // 0 = derecha
        {
            nf = pivot.f + moverC;
            nc = pivot.c - moverF;
        }

        if (tablero_ocupado(t, nf, nc))
            return 0;
    }
    return 1;
}

void pieza_rotar(tPieza* p, int sentido)
{
    tBloque* b = p->bloques;
    tBloque pivot = *(b + 1);

    for (int i = 0; i < p->cant_bloques; i++)
    {
        int moverF = (b + i)->f - pivot.f;
        int moverC = (b + i)->c - pivot.c;

        if(sentido) //1 = izquierda
        {
            (b + i)->f = pivot.f - moverC;
            (b + i)->c = pivot.c + moverF;
        }else //0 = derecha
        {
            (b + i)->f = pivot.f + moverC;
            (b + i)->c = pivot.c - moverF;
        }
    }
}

void pieza_fijar(tTablero* t, const tPieza* p)
{
    const tBloque* b = p->bloques;

    for (int i = 0; i < p->cant_bloques; i++)
    {
        tablero_fijar_celda(t, (b + i)->f, (b + i)->c, 2);
    }
}

int pieza_color(int figura)
{
    const int colores[] = {COLOR_PIEZA_I, COLOR_PIEZA_J, COLOR_PIEZA_L,
        COLOR_PIEZA_O, COLOR_PIEZA_S, COLOR_PIEZA_Z, COLOR_PIEZA_T};

    return colores[figura % 7];
}

void pieza_rotar_deluxe(const tTablero* t, tPieza* p, int sentido)
{
    if (p->tipo == 5)
        return;

    int coords_nuevas[10];
    int puede_rotar;
    int col_mitad;
    int i;

    tBloque* b_orig = p->bloques;
    int f_pivote = (b_orig + 1)->f;
    int c_pivote = (b_orig + 1)->c;

    puede_rotar = 1;
    col_mitad = t->columnas / 2;

    for (i = 0; i < p->cant_bloques * 2; i += 2)
    {
        int f_actual = (b_orig + (i / 2))->f;
        int c_actual = (b_orig + (i / 2))->c;

        if (c_actual - c_pivote > col_mitad)
            c_actual -= t->columnas;
        else if (c_pivote - c_actual > col_mitad)
            c_actual += t->columnas;

        int f_nueva, c_nueva;

        if (sentido) // 1 = Izquierda
        {
            f_nueva = f_pivote - (c_actual - c_pivote);
            c_nueva = c_pivote + (f_actual - f_pivote);
        }
        else // 0 = Derecha
        {
            f_nueva = f_pivote + (c_actual - c_pivote);
            c_nueva = c_pivote - (f_actual - f_pivote);
        }

        if (c_nueva < 0)
            c_nueva = (c_nueva % t->columnas) + t->columnas;
        c_nueva %= t->columnas;

        *(coords_nuevas + i) = f_nueva;
        *(coords_nuevas + i + 1) = c_nueva;
    }

    for (i = 0; i < p->cant_bloques * 2; i += 2)
    {
        int f = *(coords_nuevas + i);
        int c = *(coords_nuevas + i + 1);

        if (f < 0 || f >= t->filas || (tablero_dentro(t, f, c) && *(*(t->celdas + f) + c) != 0))
        {
            puede_rotar = 0;
            break;
        }
    }

    if (puede_rotar)
    {
        for (i = 0; i < p->cant_bloques; i++)
        {
            (b_orig + i)->f = *(coords_nuevas + (i * 2));
            (b_orig + i)->c = *(coords_nuevas + (i * 2 + 1));
        }
    }
}
