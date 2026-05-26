#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "render.h"
#include "GBT/gbt.h"

void Pantalla_Inicio (tFuente *fuente, int *juego)
{

    *juego = 2;
    int seleccion = 1; // 1 = Clásico, 2 = Deluxe, 3 = Estadísticas


    while(*juego == 2)
    {

        gbt_procesar_entrada();

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
            if(seleccion == 1)
                *juego = 1; // Modo Normal
            if(seleccion == 2)
                *juego = 3; // Modo Deluxe
            if(seleccion == 3)
                *juego = 4; // Estadísticas
        }


        if(gbt_tecla_presionada(GBTK_1))
            *juego = 1;
        if(gbt_tecla_presionada(GBTK_2))
            *juego = 3;
        if(gbt_tecla_presionada(GBTK_3))
            *juego = 4;

        if(gbt_tecla_presionada(GBTK_ESCAPE))
            *juego = 0;

        gbt_borrar_backbuffer(0);

        dibujar_fondo(fuente);

        fuente_dibujar_texto(290, 100, "menu", 31, 2, fuente);

        int color_opcion1 = (seleccion == 1) ? 30 : 8;
        fuente_dibujar_texto(250, 150, "1 - MODO NORMAL", color_opcion1, 1, fuente);

        int color_opcion2 = (seleccion == 2) ? 30 : 8;
        fuente_dibujar_texto(250, 200, "2 - MODO DELUXE", color_opcion2, 1, fuente);

        int color_opcion3 = (seleccion == 3) ? 30 : 8;
        fuente_dibujar_texto(250, 250, "3 - ESTADISTICAS", color_opcion3, 1, fuente);

        // Opción fija para salir en color Gris (8)
        fuente_dibujar_texto(250, 350, "ESC - SALIR", 8, 1, fuente);

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

        if(gbt_tecla_presionada(GBTK_ESCAPE))
            {
                en_pausa = 0;
                *juego = 2;
            }
        fuente_dibujar_texto(220, 180, "JUEGO EN PAUSA", 31, 2, fuente); // Blanco (7)


        int color_opcion1 = (seleccion == 1) ? 30 : 8;
        fuente_dibujar_texto(240, 240, "ENTER - CONTINUAR", color_opcion1, 1, fuente);

        int color_opcion2 = (seleccion == 2) ? 30 : 8;
        fuente_dibujar_texto(240, 280, "ESC - VOLVER AL MENU", color_opcion2, 1, fuente);

        gbt_volcar_backbuffer();

        gbt_esperar(16);
    }
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

static char tecla_presionada_a_char(void)
{
    for (int i = 0; i < 26; i++)
        if (gbt_tecla_presionada(GBTK_a + i))
            return (char)('A' + i);

    for (int i = 0; i < 10; i++)
        if (gbt_tecla_presionada(GBTK_0 + i))
            return (char)('0' + i);

    return 0;
}

void Pantalla_Ingresar_Nombre(tFuente *fuente, char *destino, int max_chars)
{
    int len = 0;
    int corriendo = 1;
    int frame = 0;

    destino[0] = '\0';

    while (corriendo)
    {
        gbt_procesar_entrada();

        /* ENTER confirma, pero solo si hay al menos una letra */
        if (gbt_tecla_presionada(GBTK_ENTER) && len > 0)
        {
            corriendo = 0;
            gbt_esperar(150);
        }

        /* ESC cancela: nombre por defecto */
        if (gbt_tecla_presionada(GBTK_ESCAPE))
        {
            strcpy(destino, "ANON");
            corriendo = 0;
            gbt_esperar(150);
        }

        /* Flecha izquierda hace backspace */
        if (gbt_tecla_presionada(GBTK_IZQUIERDA) && len > 0)
        {
            len--;
            destino[len] = '\0';
            gbt_esperar(120);
        }

        /* Letra o digito, si hay espacio */
        if (len < max_chars)
        {
            char c = tecla_presionada_a_char();
            if (c != 0)
            {
                destino[len++] = c;
                destino[len] = '\0';
                gbt_esperar(140);
            }
        }

        gbt_borrar_backbuffer(0);
        dibujar_fondo(fuente);

        fuente_dibujar_texto(TAM_VENTANA_X/2 - 90, 112, "NUEVO", 31, 3, fuente);
        fuente_dibujar_texto(TAM_VENTANA_X/2 - 90, 154, "RECORD!", 31, 3, fuente);
        fuente_dibujar_texto(220, 230, "INGRESA TU NOMBRE", 30, 1, fuente);

        char display[16];
        snprintf(display, sizeof(display), "%s%s",
                 destino,
                 ((frame / 30) % 2 == 0 && len < max_chars) ? "_" : "");
        fuente_dibujar_texto(260, 270, display, 31, 2, fuente);

        fuente_dibujar_texto(220, 340, "<- BORRAR",          8, 1, fuente);
        fuente_dibujar_texto(220, 360, "ENTER - CONFIRMAR",  8, 1, fuente);
        fuente_dibujar_texto(220, 380, "ESC - ANONIMO",      8, 1, fuente);

        gbt_volcar_backbuffer();
        gbt_esperar(16);
        frame++;
    }
}

void Pantalla_Records(tFuente *fuente, const tRecords *records)
{
    int corriendo = 1;

    while (corriendo)
    {
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_ENTER) || gbt_tecla_presionada(GBTK_ESCAPE))
        {
            corriendo = 0;
            gbt_esperar(150); /* evita que la tecla se "filtre" al menu de atras */
        }

        gbt_borrar_backbuffer(0);
        dibujar_fondo(fuente);

        fuente_dibujar_texto(TAM_VENTANA_X/2 - 90, 70, "RECORDS", 31, 3, fuente);

        if (records->cant == 0)
        {
            fuente_dibujar_texto(230, 250, "AUN NO HAY RECORDS", 30, 1, fuente);
        }
        else
        {
            /* Encabezados */
            fuente_dibujar_texto( 80, 150, "POS",     30, 1, fuente);
            fuente_dibujar_texto(140, 150, "NOMBRE",  30, 1, fuente);
            fuente_dibujar_texto(280, 150, "PUNTAJE", 30, 1, fuente);
            fuente_dibujar_texto(400, 150, "LINEAS",  30, 1, fuente);
            fuente_dibujar_texto(500, 150, "NIVEL",   30, 1, fuente);

            char buf[16];
            int y = 180;
            int pos = 1;
            for (const tRecord *p = records->lista;
                 p < records->lista + records->cant;
                 p++)
            {
                snprintf(buf, sizeof(buf), "%d", pos);
                fuente_dibujar_texto( 80, y, buf, 31, 1, fuente);

                fuente_dibujar_texto(140, y, p->nombre, 31, 1, fuente);

                snprintf(buf, sizeof(buf), "%d", p->puntaje);
                fuente_dibujar_texto(280, y, buf, 31, 1, fuente);

                snprintf(buf, sizeof(buf), "%d", p->lineas);
                fuente_dibujar_texto(400, y, buf, 31, 1, fuente);

                snprintf(buf, sizeof(buf), "%d", p->nivel);
                fuente_dibujar_texto(500, y, buf, 31, 1, fuente);


                y += 25;
                pos++;
            }
        }

        fuente_dibujar_texto(180, 420, "ENTER/ESC PARA VOLVER", 8, 1, fuente);
        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }
}
