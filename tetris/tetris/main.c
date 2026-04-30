#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "GBT/gbt.h"

#define TAM_VENTANA_X  640
#define TAM_VENTANA_Y  480

#define FILAS 22
#define COLS 10
#define TAM_MINO 12

#define PIEZAS 7
#define PRUEBA 0

void dibujar_tablero(uint8_t mat[FILAS][COLS]);
void figueras_tetris(uint8_t mat[FILAS][COLS], int mat_coor[PIEZAS][8], int *j, int *nivel);
void figuras_caen(uint8_t mat[FILAS][COLS], int mat_coor[PIEZAS][8], int *j, int *nivel);
void borrar(uint8_t mat[FILAS][COLS], int mat_coor[PIEZAS][8], int *j, int *nivel);

void rotar_universal(int pieza[8], uint8_t tablero[FILAS][COLS]);
void mover_derecha(int pieza[8], uint8_t tablero[FILAS][COLS]);
void mover_izquierda(int pieza[8], uint8_t tablero[FILAS][COLS]);

int verificar_colision(uint8_t mat[FILAS][COLS], int pieza[8]);
void fijar_pieza(uint8_t mat[FILAS][COLS], int pieza[8]);
void reiniciar_pieza(int pieza[8]);

int main()
{
    if (gbt_iniciar() < 0)
        return 1;

    if (gbt_crear_ventana("Tetris UNLaM - Luminosos", TAM_VENTANA_X, TAM_VENTANA_Y, 2) < 0)
        return 1;

    srand(time(NULL));

    uint8_t tablero[FILAS][COLS] = {0};
    int juego_corriendo = 1;
    int j = 0;
    int nivel = 0;

    int mat_coordenads[PIEZAS][8] = {{0,3,0,4,0,5,0,6},
                                     {1,4,1,5,1,6,0,6},
                                     {1,4,1,5,1,6,0,4},
                                     {1,4,1,5,0,5,0,6},
                                     {1,5,1,6,0,4,0,5},
                                     {0,4,0,5,1,4,1,5},
                                     {1,3,1,4,1,5,0,4}};


    tGBT_Temporizador* reloj_caida = gbt_temporizador_crear(0.8);

    while (juego_corriendo)
    {
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_ESCAPE)) juego_corriendo = 0;


        if (gbt_temporizador_consumir(reloj_caida))
        {
            if (verificar_colision(tablero, mat_coordenads[PRUEBA]))
            {
                fijar_pieza(tablero, mat_coordenads[PRUEBA]);

                reiniciar_pieza(mat_coordenads[PRUEBA]);
            }
            else
            {
                borrar(tablero, mat_coordenads, &j, &nivel);

                figueras_tetris(tablero, mat_coordenads, &j, &nivel);
            }
        }

        if (gbt_tecla_presionada(GBTK_w) && PRUEBA != 5)
        {
            borrar(tablero, mat_coordenads, &j, &nivel);

            for(int i=0; i<8; i+=2)
                mat_coordenads[PRUEBA][i]--;

            rotar_universal(mat_coordenads[PRUEBA], tablero);

            figueras_tetris(tablero, mat_coordenads, &j, &nivel);

            gbt_esperar(150);
        }

        if (gbt_tecla_presionada(GBTK_d))
        {
            borrar(tablero, mat_coordenads, &j, &nivel);

            for(int i=0; i<8; i+=2)
                mat_coordenads[PRUEBA][i]--;

            mover_derecha(mat_coordenads[PRUEBA], tablero);

            figueras_tetris(tablero, mat_coordenads, &j, &nivel);

            gbt_esperar(100);
        }

        if (gbt_tecla_presionada(GBTK_a))
        {
            borrar(tablero, mat_coordenads, &j, &nivel);

            for(int i=0; i<8; i+=2)
                mat_coordenads[PRUEBA][i]--;

            mover_izquierda(mat_coordenads[PRUEBA], tablero);

            figueras_tetris(tablero, mat_coordenads, &j, &nivel);

            gbt_esperar(100);
        }

        gbt_borrar_backbuffer(0);
        dibujar_tablero(tablero);
        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }

    gbt_temporizador_destruir(reloj_caida);
    gbt_cerrar();
    return 0;
}

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

void dibujar_tablero(uint8_t mat[FILAS][COLS])
{
    int pos_pantalla_x = (TAM_VENTANA_X / 2) - (COLS * TAM_MINO)/2;

    int pos_pantalla_y = 70;

    for (int f = 0; f < FILAS; f++)
    {
        for (int c = 0; c < COLS; c++)
        {
            int px = pos_pantalla_x + (c * TAM_MINO);
            int py = pos_pantalla_y + (f * TAM_MINO);

            int color_borde = (mat[f][c] == 0) ? 8 : 7;

            for (int i = 0; i < TAM_MINO; i++)
                for (int j = 0; j < TAM_MINO; j++)
                    gbt_dibujar_pixel(px + i, py + j, color_borde);

            int color_centro = (mat[f][c] == 0) ? 0 : mat[f][c];

            for (int i = 1; i < TAM_MINO - 1; i++)
                for (int j = 1; j < TAM_MINO - 1; j++)
                    gbt_dibujar_pixel(px + i, py + j, color_centro);
        }
    }
}


int verificar_colision(uint8_t mat[FILAS][COLS], int pieza[8])
{
    int prox_f;
    int c;

    for (int i = 0; i < 8; i += 2)
    {
        prox_f = pieza[i] + 1;
        c = pieza[i+1];


        if (prox_f >= FILAS || (prox_f >= 0 && mat[prox_f][c] == 2))
            return 1;
    }

    return 0;
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

void reiniciar_pieza(int pieza[8])
{
    int iniciales[8] = {0,3,0,4,0,5,0,6};

    for(int i=0; i<8; i++)
        pieza[i] = iniciales[i];
}


void rotar_universal(int pieza[8], uint8_t tablero[FILAS][COLS])
{
    int f_pivote = pieza[2], c_pivote = pieza[3], aux[8], posible = 1;
    int f_rel;
    int c_rel;

    for (int i = 0; i < 8; i += 2)
    {
        f_rel = pieza[i] - f_pivote, c_rel = pieza[i+1] - c_pivote;

        aux[i] = f_pivote + c_rel; aux[i+1] = c_pivote - f_rel;

        if (aux[i] < 0 || aux[i] >= FILAS || aux[i+1] < 0 || aux[i+1] >= COLS || tablero[aux[i]][aux[i+1]] == 2)
        {
            posible = 0;
            break;///REVISAR LOGICA
        }
    }
    if (posible)
        for (int i = 0; i < 8; i++)
            pieza[i] = aux[i];
}

void mover_derecha(int pieza[8], uint8_t tablero[FILAS][COLS])
{
    int posible = 1;
    int c_nueva;

    for (int i = 0; i < 8; i += 2)
    {
        c_nueva = pieza[i+1] + 1;

        if (c_nueva >= COLS || tablero[pieza[i]][c_nueva] == 2)
            posible = 0;
             break; ///REVISAR LOGICA


    }

    if (posible)
        for (int i = 1; i < 8; i += 2)
            pieza[i]++;
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
            break;///REVISAR LOGICA
        }
    }

    if (posible)
        for (int i = 1; i < 8; i += 2)
            pieza[i]--;
}
