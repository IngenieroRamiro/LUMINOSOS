#include "render.h"
#include <stdio.h>
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
            gbt_dibujar_pixel(x + i, y + j, 176);

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

    fuente_dibujar_texto(TAM_VENTANA_X/2 - 61, 70, "tetris", 11, 3, fuente);

    ///Paleta de colores

    /*for (int g= 0; g<20; g++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
                gbt_dibujar_pixel(20 + i + g*10, 70 + j, g);
        }
    }

    for (int g= 0; g<20; g++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
                gbt_dibujar_pixel(20 + i + g*10, 85 + j, g+20);
        }
    }

    for (int g= 0; g<20; g++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
                gbt_dibujar_pixel(20 + i + g*10, 100 + j, g+40);
        }
    }

    for (int g= 0; g<20; g++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
                gbt_dibujar_pixel(20 + i + g*10, 115 + j, g+60);
        }
    }

    for (int g= 0; g<20; g++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
                gbt_dibujar_pixel(20 + i + g*10, 130 + j, g+80);
        }
    }

    for (int g= 0; g<20; g++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
                gbt_dibujar_pixel(20 + i + g*10, 145 + j, g+100);
        }
    }

    for (int g= 0; g<20; g++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
                gbt_dibujar_pixel(20 + i + g*10, 160 + j, g+120);
        }
    }

    for (int g= 0; g<20; g++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
                gbt_dibujar_pixel(20 + i + g*10, 175 + j, g+140);
        }
    }

    for (int g= 0; g<20; g++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
                gbt_dibujar_pixel(20 + i + g*10, 190 + j, g+160);
        }
    }

        for (int g= 0; g<20; g++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
                gbt_dibujar_pixel(20 + i + g*10, 205 + j, g+180);
        }
    }

        for (int g= 0; g<20; g++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
                gbt_dibujar_pixel(20 + i + g*10, 220 + j, g+200);
        }
    }

        for (int g= 0; g<20; g++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
                gbt_dibujar_pixel(20 + i + g*10, 235 + j, g+220);
        }
    }

        for (int g= 0; g<15; g++)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
                gbt_dibujar_pixel(20 + i + g*10, 250 + j, g+240);
        }
    }//*/
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
/*
 * Dibuja el HUD a la derecha del tablero: puntaje, lineas y nivel.
 * snprintf con buffer chico alcanza: con int de 32 bits el peor caso
 * es "-2147483648" (12 chars incluyendo el '\0').
 */
void dibujar_hud(const tPuntuacion *p, const tFuente *fuente)
{
    char buffer[16];

    const int x = 400;
    const int y_base = 120;

    fuente_dibujar_texto(x, y_base, "PUNTAJE", 11, 1, fuente);
    snprintf(buffer, sizeof(buffer), "%d", p->puntaje);
    fuente_dibujar_texto(x, y_base + 12, buffer, 7, 1, fuente);

    fuente_dibujar_texto(x, y_base + 36, "LINEAS", 11, 1, fuente);
    snprintf(buffer, sizeof(buffer), "%d", p->lineas);
    fuente_dibujar_texto(x, y_base + 48, buffer, 7, 1, fuente);

    fuente_dibujar_texto(x, y_base + 72, "NIVEL", 11, 1, fuente);
    snprintf(buffer, sizeof(buffer), "%d", p->nivel);
    fuente_dibujar_texto(x, y_base + 84, buffer, 7, 1, fuente);
}
