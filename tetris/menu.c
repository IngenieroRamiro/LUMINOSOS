#include <stdio.h>
#include "tipos.h"
#include "fuentes.h"
#include "tablero.h"
#include "GBT/gbt.h"
#include "puntuacion.h"

void Pantalla_Inicio(tFuente *fuente, int *juego, uint8_t mat[FILAS][COLS], int coords_pieza[8], int *figura_tipo, int *p_caidas, float *vel_actual, int *modo_deluxe, tPuntuacion *puntuacion)
{
    int en_menu = 1;
    int seleccion = 1;

    while (en_menu)
    {
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_w))
        {
            seleccion--;
            if (seleccion < 1) seleccion = 4;
            gbt_esperar(120);
        }

        if (gbt_tecla_presionada(GBTK_s))
        {
            seleccion++;
            if (seleccion > 4) seleccion = 1;
            gbt_esperar(120);
        }

        if (gbt_tecla_presionada(GBTK_ENTER))
        {
            if (seleccion == 1)
            {
                en_menu = 0;
                *juego = 1;
                *modo_deluxe = 0;
                Reiniciar_Tablero(mat);
            }
            if (seleccion == 2)
            {
                en_menu = 0;
                *juego = 1;
                *modo_deluxe = 1;
                Reiniciar_Tablero(mat);
            }
            if (seleccion == 3)
            {
                borrar(mat, coords_pieza);
                if (Cargar_Partida_Archivo(mat, coords_pieza, figura_tipo, p_caidas, vel_actual, puntuacion, modo_deluxe))
                {
                    en_menu = 0;
                    *juego = 3;
                }
                else
                {
                    gbt_esperar(100);
                }
            }
            if (seleccion == 4)
            {
                en_menu = 0;
                *juego = -1;
            }
        }

        gbt_borrar_backbuffer(0);
        fuente_dibujar_texto(260, 120, "TETRIS UNLAM", 7, 2, fuente);

        int col1 = (seleccion == 1) ? 7 : 8;
        fuente_dibujar_texto(240, 180, "MODO NORMAL", col1, 2, fuente);

        int col2 = (seleccion == 2) ? 7 : 8;
        fuente_dibujar_texto(240, 220, "MODO DELUXE", col2, 2, fuente);

        int col3 = (seleccion == 3) ? 7 : 8;
        fuente_dibujar_texto(240, 260, "CARGAR PARTIDA", col3, 2, fuente);

        int col4 = (seleccion == 4) ? 7 : 8;
        fuente_dibujar_texto(240, 300, "SALIR", col4, 2, fuente);

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }
}

void Guardar_Partida_Archivo(uint8_t mat[FILAS][COLS], int coords_pieza[8], int figura_tipo, int p_caidas, float vel_actual, tPuntuacion *puntuacion, int modo_deluxe)
{
    FILE *arch = fopen("partida.sav", "wb");
    if (arch == NULL) return;

    fwrite(mat, sizeof(uint8_t), FILAS * COLS, arch);
    fwrite(coords_pieza, sizeof(int), 8, arch);
    fwrite(&figura_tipo, sizeof(int), 1, arch);
    fwrite(&p_caidas, sizeof(int), 1, arch);
    fwrite(&vel_actual, sizeof(float), 1, arch);
    fwrite(puntuacion, sizeof(tPuntuacion), 1, arch);
    fwrite(&modo_deluxe, sizeof(int), 1, arch);

    fclose(arch);
}


void Pausar_Juego (tFuente *fuente, int *juego, uint8_t mat[FILAS][COLS], int coords_pieza[8], int figura_tipo, int p_caidas, float vel_actual, tPuntuacion *puntuacion, int modo_deluxe)
{
    int en_pausa = 1;
    int seleccion = 1;

    while (en_pausa)
    {
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_w))
        {
            seleccion--;
            if (seleccion < 1) seleccion = 3;
            gbt_esperar(120);
        }

        if (gbt_tecla_presionada(GBTK_s))
        {
            seleccion++;
            if (seleccion > 3) seleccion = 1;
            gbt_esperar(120);
        }

        if (gbt_tecla_presionada(GBTK_ENTER))
        {
            if (seleccion == 1)
            {
                en_pausa = 0;
            }
            if (seleccion == 2)
            {
                Guardar_Partida_Archivo(mat, coords_pieza, figura_tipo, p_caidas, vel_actual, puntuacion, modo_deluxe);
                en_pausa = 0;
            }
            if (seleccion == 3)
            {
                en_pausa = 0;
                *juego = 0;
            }
        }

        fuente_dibujar_texto(260, 160, "JUEGO EN PAUSA", 7, 2, fuente);

        int col_opc1 = (seleccion == 1) ? 7 : 8;
        fuente_dibujar_texto(240, 220, "ENTER - CONTINUAR", col_opc1, 2, fuente);

        int col_opc2 = (seleccion == 2) ? 7 : 8;
        fuente_dibujar_texto(240, 260, "ENTER - GUARDAR PARTIDA", col_opc2, 2, fuente);

        int col_opc3 = (seleccion == 3) ? 7 : 8;
        fuente_dibujar_texto(220, 300, "ESC - VOLVER AL MENU", col_opc3, 2, fuente);

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }
}


