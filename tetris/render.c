#include "render.h"

#include "GBT/gbt.h"

void dibujar_tablero(uint8_t mat[FILAS][COLS])
{
    int pos_pantalla_x = (TAM_VENTANA_X / 2) - (COLS * TAM_MINO)/2;

    int pos_pantalla_y = 100;

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

void dibujar_forma(int x, int y, int ancho, int alto)
{
    for (int i = 0; i < ancho; i++)
        for (int j = 0; j < alto; j++)
            gbt_dibujar_pixel(x + i, y + j, 1);

    for (int i = 10; i < ancho - 10; i++)
        for (int j = 10; j < alto - 10; j++)
            gbt_dibujar_pixel(x + i, y + j, 9);

    for (int i = 25; i < ancho - 25; i++)
        for (int j = 25; j < alto - 25; j++)
            gbt_dibujar_pixel(x + i, y + j, 1);
}

void dibujar_fondo(tFuente *fuente)
{
    //int inicio_tablero = (TAM_VENTANA_X / 2) - (COLS * TAM_MINO)/2;

    int y = 0;
    int x = 0;

    for(int f = 0; f < 6; f++)
    {
        x = 0;
        for(int c = 0; c < 8; c++)
        {
            dibujar_forma(x, y, 80, 80);
            x += 80;
        }
        y += 80;
    }

    fuente_dibujar_texto(TAM_VENTANA_X/2 - 10, 70, "tetris", 11, fuente);

    /*for (int g= 0; g<20; g++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
                gbt_dibujar_pixel(20 + i + g*10, 70 + j, g);
        }
    }*/
}

/*void dibujar_fondo()
{
    int inicio_tablero = (TAM_VENTANA_X / 2) - (COLS * TAM_MINO)/2;

    int y = 0;
    int x = 0;

    for(int f = 0; f < 4; f++)
    {
        x = 0;
        for(int c = 0; c < 4; c++)
        {
            dibujar_forma(x, y);
            x += 65;
        }
        y += 120;
    }

    //return inicio_tablero;
}*/

/*
ancho: 260 / 20 = 13
alto: 480 / 20 = 24

c: 13 * 24
*/
