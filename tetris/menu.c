#include <stdio.h>

#include "menu.h"
#include "render.h"
#include "GBT/gbt.h"

#include "menu.h"
#include "render.h"
#include "GBT/gbt.h"

void Pantalla_Inicio(tFuente *fuente, int *juego, tConfiguracion* config)
{
    *juego = 2;
    int seleccion = 1; // 1:Clásico, 2:Deluxe, 3:Estadísticas, 4:Configuración

    while(*juego == 2)
    {
        gbt_procesar_entrada();

        if(gbt_tecla_presionada(GBTK_w)) {
            seleccion--;
            if(seleccion < 1) seleccion = 4;
            gbt_esperar(120);
        }
        if(gbt_tecla_presionada(GBTK_s)) {
            seleccion++;
            if(seleccion > 4) seleccion = 1;
            gbt_esperar(120);
        }

        if(gbt_tecla_presionada(GBTK_ENTER)) {
            if(seleccion == 1) *juego = 1; // Normal
            if(seleccion == 2) *juego = 3; // Deluxe
            if(seleccion == 3) *juego = 4; // Récords
            if(seleccion == 4) *juego = 5; // Configuración
        }

        if(gbt_tecla_presionada(GBTK_ESCAPE)) *juego = 0;

        gbt_borrar_backbuffer(0);
        dibujar_fondo(fuente);

        fuente_dibujar_texto(290, 80, "menu", 31, 2, fuente);

        fuente_dibujar_texto(220, 140, "1 - MODO NORMAL", (seleccion == 1) ? 30 : 8, 1, fuente);
        fuente_dibujar_texto(220, 180, "2 - MODO DELUXE", (seleccion == 2) ? 30 : 8, 1, fuente);
        fuente_dibujar_texto(220, 220, "3 - ESTADISTICAS", (seleccion == 3) ? 30 : 8, 1, fuente);
        fuente_dibujar_texto(220, 260, "4 - CONFIGURACION", (seleccion == 4) ? 30 : 8, 1, fuente);
        fuente_dibujar_texto(220, 340, "ESC - SALIR", 8, 1, fuente);

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }
}

void Pausar_Juego(tFuente *fuente, int *juego)
{
    int en_pausa = 1;
    int seleccion = 1;
    int color_opcion1;
    int color_opcion2;

    int* p_sel = &seleccion;
    int* p_pausa = &en_pausa;

    while (*p_pausa)
    {
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_w))
        {
            (*p_sel)--;
            if (*p_sel < 1) *p_sel = 2;
            gbt_esperar(120);
        }

        if (gbt_tecla_presionada(GBTK_s))
        {
            (*p_sel)++;
            if (*p_sel > 2) *p_sel = 1;
            gbt_esperar(120);
        }

        if (gbt_tecla_presionada(GBTK_ENTER))
        {
            if (*p_sel == 1)
            {
                *p_pausa = 0;
            }
            if (*p_sel == 2)
            {
                *p_pausa = 0;
                *juego = 2;
            }
        }

        if (gbt_tecla_presionada(GBTK_ESCAPE))
        {
            *p_pausa = 0;
            *juego = 2;       // También vuelve al menú con ESC
        }

        // Renderizado del cartel de Pausa sobre el frame actual
        fuente_dibujar_texto(220, 180, "JUEGO EN PAUSA", 31, 2, fuente);

        color_opcion1 = (*p_sel == 1) ? 30 : 8;
        fuente_dibujar_texto(240, 240, "ENTER - CONTINUAR", color_opcion1, 1, fuente);

        color_opcion2 = (*p_sel == 2) ? 30 : 8;
        fuente_dibujar_texto(240, 280, "ESC - VOLVER AL MENU", color_opcion2, 1, fuente);

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }
}

void Pantalla_Configuracion(tFuente *fuente, int *juego, tConfiguracion* config)
{
    int en_config = 1;
    int seleccion = 1; // 1: Paleta, 2: Resolución, 3: Velocidad, 4: Tamaño Tablero DX, 5: Volver
    char buffer[32];

    while(en_config)
    {
        gbt_procesar_entrada();

        if(gbt_tecla_presionada(GBTK_w)) {
            seleccion--;
            if(seleccion < 1) seleccion = 5;
            gbt_esperar(120);
        }
        if(gbt_tecla_presionada(GBTK_s)) {
            seleccion++;
            if(seleccion > 5) seleccion = 1;
            gbt_esperar(120);
        }

        // Modificación horizontal de valores
        if(gbt_tecla_presionada(GBTK_d)) {
            if(seleccion == 1) config->paleta_color = (config->paleta_color + 1) % 3;
            if(seleccion == 2) config->resolucion_logica = (config->resolucion_logica + 1) % 3;
            if(seleccion == 3) config->velocidad_caida = (config->velocidad_caida + 1) % 3;
            if(seleccion == 4) {
                config->columnas_deluxe += 2;
                if(config->columnas_deluxe > 16) config->columnas_deluxe = 8;
            }
            gbt_esperar(120);
        }
        if(gbt_tecla_presionada(GBTK_a)) {
            if(seleccion == 1) config->paleta_color = (config->paleta_color - 1 + 3) % 3;
            if(seleccion == 2) config->resolucion_logica = (config->resolucion_logica - 1 + 3) % 3;
            if(seleccion == 3) config->velocidad_caida = (config->velocidad_caida - 1 + 3) % 3;
            if(seleccion == 4) {
                config->columnas_deluxe -= 2;
                if(config->columnas_deluxe < 8) config->columnas_deluxe = 16;
            }
            gbt_esperar(120);
        }

        if(gbt_tecla_presionada(GBTK_ENTER) && seleccion == 5) en_config = 0;
        if(gbt_tecla_presionada(GBTK_ESCAPE)) en_config = 0;

        gbt_borrar_backbuffer(0);
        dibujar_fondo(fuente);

        fuente_dibujar_texto(220, 60, "configuracion", 31, 2, fuente);

        sprintf(buffer, "PALETA: %s", (config->paleta_color == 0) ? "CLASICA" : (config->paleta_color == 1) ? "LUMINOSA" : "NEON");
        fuente_dibujar_texto(180, 130, buffer, (seleccion == 1) ? 30 : 8, 1, fuente);

        sprintf(buffer, "RESOLUCION: %s", (config->resolucion_logica == 0) ? "NORMAL" : (config->resolucion_logica == 1) ? "ALTA" : "RETRO");
        fuente_dibujar_texto(180, 170, buffer, (seleccion == 2) ? 30 : 8, 1, fuente);

        sprintf(buffer, "VEL GRAVEDAD: %s", (config->velocidad_caida == 0) ? "LENTA" : (config->velocidad_caida == 1) ? "NORMAL" : "RAPIDA");
        fuente_dibujar_texto(180, 210, buffer, (seleccion == 3) ? 30 : 8, 1, fuente);

        sprintf(buffer, "ANCHO TABLERO DX: %d", config->columnas_deluxe);
        fuente_dibujar_texto(180, 250, buffer, (seleccion == 4) ? 30 : 8, 1, fuente);

        fuente_dibujar_texto(180, 320, "VOLVER AL MENU", (seleccion == 5) ? 30 : 8, 1, fuente);

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }
    *juego = 2; // Vuelve al menú
}

void Game_over(tFuente *fuente, int *juego)
{

    int en_pausa = 1;
    int seleccion = 1;

    gbt_borrar_backbuffer(0);

    while (en_pausa)
    {

        dibujar_fondo(fuente);

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

        if(gbt_tecla_presionada(GBTK_ESCAPE))
            {
                en_pausa = 0;
                *juego = 2;
            }
        fuente_dibujar_texto(TAM_VENTANA_X/2 - 50, 112, "Game", 31, 3, fuente);
        fuente_dibujar_texto(TAM_VENTANA_X/2 - 50, 154, "Over", 31, 3, fuente);

        int color_opcion1 = (seleccion == 1) ? 30 : 8;
        fuente_dibujar_texto(240, 240, "jugar de nuevo", color_opcion1, 1, fuente);

        int color_opcion2 = (seleccion == 2) ? 30 : 8;
        fuente_dibujar_texto(240, 280, "ESC - VOLVER AL MENU", color_opcion2, 1, fuente);

        gbt_volcar_backbuffer();

        gbt_esperar(16);
    }
}


