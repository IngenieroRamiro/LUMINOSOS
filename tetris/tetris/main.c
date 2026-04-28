#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "GBT/gbt.h"

#define TAM_VENTANA_X 640
#define TAM_VENTANA_Y 480

#define FILAS 22
#define COLS 10
#define TAM_MINO 20  // Tamaño en píxeles de cada cuadradito

#define PIEZAS 7 // cantidad de piezas diferentes
#define PRUEBA 2 // que pieza quiere que aparesca 0-I,1-L,2-J,3-S,4-Z,5-O,6-T


void dibujar_tablero(uint8_t mat[FILAS][COLS]);
void figueras_tetris(uint8_t mat[FILAS][COLS],int mat_coor [PIEZAS][8],int *j,int *nivel); //*j y *nivel no hacen nada momentaneamente
void figuras_caen (uint8_t mat[FILAS][COLS],int mat_coor [PIEZAS][8],int *j,int *nivel);
void borrar (uint8_t mat[FILAS][COLS],int mat_coor [PIEZAS][8],int *j,int *nivel);

int main()
{
    if (gbt_iniciar() < 0)
    {
        printf("ERROR AL INICIAR LA BIBLIOTECA GBT %s", gbt_obtener_log());
        return 1;
    }

    if(gbt_crear_ventana("Tetris UNLaM - Luminosos", TAM_VENTANA_X, TAM_VENTANA_Y, 2) < 0)
    {
        printf("ERROR AL CREAR LA VENTANA %s", gbt_obtener_log());
        return 1;
    }

    srand(time(NULL));

    uint8_t tablero[FILAS][COLS] = {0};
    int juego_corriendo = 1;
    int j = 0;
    int nivel = 1;

    int mat_coordenads [PIEZAS][8] = {{0,3,0,4,0,5,0,6},
                                      {1,4,1,5,1,6,0,6},
                                      {1,4,1,5,1,6,0,4},
                                      {1,4,1,5,0,5,0,6},
                                      {1,5,1,6,0,4,0,5},
                                      {0,4,0,5,1,4,1,5},
                                      {1,3,1,4,1,5,0,4}};

    tGBT_Temporizador* reloj_caida = gbt_temporizador_crear(0.8);

    if (reloj_caida == NULL)
    {
        printf("ERROR: No se pudo crear el temporizador.\n");
        return 1;
    }

    dibujar_tablero(tablero);
    gbt_volcar_backbuffer();

    while(juego_corriendo)
    {
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_ESCAPE)) juego_corriendo = 0;

        // --- LÓGICA DE TIEMPO ---
        if (gbt_temporizador_consumir(reloj_caida))
        {
            // 1. Borramos la posición vieja
            borrar(tablero, mat_coordenads, &j, &nivel);

            // 2. Dibujamos en la posición nueva (que ya tiene la fila + 1)
            figueras_tetris(tablero, mat_coordenads, &j, &nivel);
        }

        // --- RENDERIZADO ---
        gbt_borrar_backbuffer(0);
        dibujar_tablero(tablero);
        gbt_volcar_backbuffer();

        gbt_esperar(16);
    }

    gbt_temporizador_destruir(reloj_caida);
    gbt_cerrar();

    return 0;
}

void dibujar_tablero(uint8_t mat[FILAS][COLS])
{
    int pos_pantalla_x = (TAM_VENTANA_X / 2) - (COLS * TAM_MINO)/2;
    int pos_pantalla_y = 40;

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



void figueras_tetris(uint8_t mat[FILAS][COLS],int mat_coor [PIEZAS][8],int *j,int *nivel)
{
    //int pieza = ; //(rand() % 7) + 1;

    figuras_caen (mat,mat_coor,j,nivel);
}

void figuras_caen (uint8_t mat[FILAS][COLS],int mat_coor [PIEZAS][8],int *j,int *nivel)
{

    for((*j) = 0; (*j) < 7; (*j) = (*j) + 2)
    {
            mat[mat_coor [PRUEBA][*j]] [ mat_coor [PRUEBA][(*j)+1] ] = 1;
            dibujar_tablero(mat);

            gbt_volcar_backbuffer();


    }
}

void borrar (uint8_t mat[FILAS][COLS], int mat_coor [PIEZAS][8], int *j, int *nivel)
{
    for((*j) = 0; (*j) < 7; (*j) += 2)
        mat[mat_coor[PRUEBA][*j]][mat_coor[PRUEBA][*j + 1]] = 0;


    for((*j) = 0; (*j) < 7; (*j) += 2)
        mat_coor[PRUEBA][*j] = mat_coor[PRUEBA][*j] + 1;

}
