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

    // Aritmética de punteros para leer la matriz y guardarla en la estructura
    const int* fila_matriz = *(FORMAS_UNIFICADAS + tipo);
    tBloque* b = p->bloques; // Puntero al inicio del array de bloques

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

int pieza_puede_rotar(const tTablero* t, const tPieza* p)
{
    if (p->tipo == 5) return 0;

    const tBloque* b = p->bloques;
    tBloque pivot = *(b + 1);

    for (int i = 0; i < p->cant_bloques; i++)
    {
        int moverF = (b + i)->f - pivot.f;
        int moverC = (b + i)->c - pivot.c;

        int nf = pivot.f + moverC;
        int nc = pivot.c - moverF;

        if (tablero_ocupado(t, nf, nc))
            return 0;
    }
    return 1;
}

void pieza_rotar(tPieza* p)
{
    tBloque* b = p->bloques;
    tBloque pivot = *(b + 1);

    for (int i = 0; i < p->cant_bloques; i++)
    {
        int moverF = (b + i)->f - pivot.f;
        int moverC = (b + i)->c - pivot.c;

        (b + i)->f = pivot.f + moverC;
        (b + i)->c = pivot.c - moverF;
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
    const int colores[] = {1, 176, 126, 45, 90, 130};
    return *(colores + (figura % 6));
}

void pieza_rotar_deluxe(const tTablero* t, tPieza* p)
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

        if (c_actual - c_pivote > col_mitad)       c_actual -= t->columnas;
        else if (c_pivote - c_actual > col_mitad)  c_actual += t->columnas;

        int f_nueva = f_pivote + (c_actual - c_pivote);
        int c_nueva = c_pivote - (f_actual - f_pivote);

        if (c_nueva < 0) c_nueva = (c_nueva % t->columnas) + t->columnas;
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
/// ////////////////////// ///
/// ARQUITECTURA ANTERIOR ///

/*


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
}*/
