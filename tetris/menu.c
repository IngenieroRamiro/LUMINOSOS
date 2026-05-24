#include <stdio.h>
#include "fuentes.h"
#include "GBT/gbt.h"

void Pantalla_Inicio (tFuente *fuente, int *juego)
{

    *juego = 2;
    int seleccion = 1; // 1 = Clásico, 2 = Deluxe, 3 = Estadísticas

    while(*juego == 2)
    {
        gbt_procesar_entrada();

        // 1. CONTROL DE NAVEGACIÓN (Flechas del teclado)
        if(gbt_tecla_presionada(GBTK_w))
        {
            seleccion--;
            if(seleccion < 1)
                seleccion = 3;
            gbt_esperar(120);
        }

        if(gbt_tecla_presionada(GBTK_s))
        {
            seleccion++;
            if(seleccion > 3)
                seleccion = 1;
            gbt_esperar(120);
        }

        if(gbt_tecla_presionada(GBTK_ENTER))
        {
            if(seleccion == 1) *juego = 1; // Modo Normal
            if(seleccion == 2) *juego = 3; // Modo Deluxe
            if(seleccion == 3) *juego = 4; // Estadísticas
        }


        if(gbt_tecla_presionada(GBTK_1)) *juego = 1;
        if(gbt_tecla_presionada(GBTK_2)) *juego = 3;
        if(gbt_tecla_presionada(GBTK_3)) *juego = 4;

        if(gbt_tecla_presionada(GBTK_ESCAPE)) *juego = 0;

        gbt_borrar_backbuffer(0);


        fuente_dibujar_texto(220, 50, "TETRIS - LUMINOSOS", 7, fuente);

        int color_opcion1 = (seleccion == 1) ? 7 : 8;
        fuente_dibujar_texto(250, 150, "1 - MODO NORMAL", color_opcion1, fuente);

        int color_opcion2 = (seleccion == 2) ? 7 : 8;
        fuente_dibujar_texto(250, 200, "2 - MODO DELUXE", color_opcion2, fuente);

        int color_opcion3 = (seleccion == 3) ? 7 : 8;
        fuente_dibujar_texto(250, 250, "3 - ESTADISTICAS", color_opcion3, fuente);

        // Opción fija para salir en color Gris (8)
        fuente_dibujar_texto(250, 350, "ESC - SALIR", 8, fuente);

        gbt_volcar_backbuffer();

        // Limita los FPS del menú
        gbt_esperar(16);
    }
}

void Pausar_Juego (tFuente *fuente, int *juego)
{
    int en_pausa = 1;
    int seleccion = 1;


    while (en_pausa)
    {
        gbt_procesar_entrada();


        if (gbt_tecla_presionada(GBTK_w))
        {
            seleccion--;
            if (seleccion < 1) seleccion = 2;
            gbt_esperar(120);
        }

        if (gbt_tecla_presionada(GBTK_s))
        {
            seleccion++;
            if (seleccion > 2) seleccion = 1;
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
                en_pausa = 0;
                *juego = 2;
            }
        }
        fuente_dibujar_texto(260, 180, "JUEGO EN PAUSA", 7, fuente); // Blanco (7)


        int color_opcion1 = (seleccion == 1) ? 7 : 8;
        fuente_dibujar_texto(240, 240, "ENTER - CONTINUAR", color_opcion1, fuente);

        int color_opcion2 = (seleccion == 2) ? 7 : 8;
        fuente_dibujar_texto(220, 280, "ESC - VOLVER AL MENU", color_opcion2, fuente);

        gbt_volcar_backbuffer();

        gbt_esperar(16);
    }
}
