#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "render.h"
#include "GBT/gbt.h"
#include "records.h"

// En menu.c -> Pantalla_Inicio
void Pantalla_Inicio(tFuente *fuente, int *juego, tConfiguracion* config)
{
    int centro_x = config->ventana_ancho / 2;

    *juego = 2;
    int seleccion = 1; // 1:Clásico, 2:Deluxe, 3:Estadísticas, 4:Configuración, 5:Cargar

    while(*juego == 2)
    {
        gbt_procesar_entrada();

        if(gbt_tecla_presionada(GBTK_w)) {
            seleccion--;
            if(seleccion < 1) seleccion = 5; // Cambiado a 5
            gbt_esperar(120);
        }
        if(gbt_tecla_presionada(GBTK_s)) {
            seleccion++;
            if(seleccion > 5) seleccion = 1; // Cambiado a 5
            gbt_esperar(120);
        }

        if(gbt_tecla_presionada(GBTK_ENTER)) {
            if(seleccion == 1) *juego = 1; // Normal
            if(seleccion == 2) *juego = 3; // Deluxe
            if(seleccion == 3) *juego = 4; // Récords
            if(seleccion == 4) *juego = 5; // Configuración
            if(seleccion == 5) *juego = 6; // <-- NUEVO ESTADO: Cargar Partida
        }

        if(gbt_tecla_presionada(GBTK_ESCAPE)) *juego = 0;

        gbt_borrar_backbuffer(0);
        dibujar_fondo(fuente, config);

        fuente_dibujar_texto(centro_x - 30, 100, "menu", FONDO_TAB, 2, fuente);

        fuente_dibujar_texto(centro_x - 70, 140, "1 - MODO NORMAL", (seleccion == 1) ? COLOR_SELECCION : 0, 1, fuente);
        fuente_dibujar_texto(centro_x - 70, 175, "2 - MODO DELUXE", (seleccion == 2) ? COLOR_SELECCION : 0, 1, fuente);
        fuente_dibujar_texto(centro_x - 70, 210, "3 - ESTADISTICAS", (seleccion == 3) ? COLOR_SELECCION : 0, 1, fuente);
        fuente_dibujar_texto(centro_x - 70, 245, "4 - CONFIGURACION", (seleccion == 4) ? COLOR_SELECCION : 0, 1, fuente);
        fuente_dibujar_texto(centro_x - 70, 280, "5 - CARGAR PARTIDA", (seleccion == 5) ? COLOR_SELECCION : 0, 1, fuente);
        fuente_dibujar_texto(centro_x - 70, 340, "ESC - SALIR", 8, 1, fuente);

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }
}

void Pausar_Juego(tFuente *fuente, int *juego, const tTablero* t, const tPieza* p, const tPuntuacion* punt, float velocidad, int caidas, tConfiguracion* config)
{
    int centro_x = config->ventana_ancho / 2;

    int en_pausa = 1;
    int seleccion = 1; // 1: CONTINUAR, 2: GUARDAR PARTIDA, 3: VOLVER AL MENU
    int color_opcion1;
    int color_opcion2;
    int color_opcion3;

    int* p_sel = &seleccion;
    int* p_pausa = &en_pausa;

    while (*p_pausa)
    {
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_w))
        {
            (*p_sel)--;
            if (*p_sel < 1) *p_sel = 3;
            gbt_esperar(120);
        }

        if (gbt_tecla_presionada(GBTK_s))
        {
            (*p_sel)++;
            if (*p_sel > 3) *p_sel = 1;
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
                partida_guardar("savegame.dat", *juego, t, p, punt, velocidad, caidas);

                fuente_dibujar_texto(centro_x - 50, 340, "PARTIDA GUARDADA!", 30, 1, fuente);
                gbt_volcar_backbuffer();
                gbt_esperar(600);
            }
            if (*p_sel == 3)
            {
                *p_pausa = 0;
                *juego = 2;
            }
        }

        if (gbt_tecla_presionada(GBTK_ESCAPE))
            *p_pausa = 0;

        fuente_dibujar_texto(centro_x - 90, 150, "JUEGO EN PAUSA", 31, 2, fuente);

        color_opcion1 = (*p_sel == 1) ? COLOR_SELECCION : 8;
        fuente_dibujar_texto(centro_x - 70, 220, "1 - CONTINUAR", color_opcion1, 1, fuente);

        color_opcion2 = (*p_sel == 2) ? COLOR_SELECCION : 8;
        fuente_dibujar_texto(centro_x - 70, 250, "2 - GUARDAR PARTIDA", color_opcion2, 1, fuente);

        color_opcion3 = (*p_sel == 3) ? COLOR_SELECCION : 8;
        fuente_dibujar_texto(centro_x - 70, 280, "3 - VOLVER AL MENU", color_opcion3, 1, fuente);

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }
}

void Pantalla_Configuracion(tFuente *fuente, int *juego, tConfiguracion* config)
{
    int centro_x = config->ventana_ancho / 2;

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
        dibujar_fondo(fuente, config);

        fuente_dibujar_texto(centro_x - 40, 100, "configuracion", 31, 2, fuente);

        sprintf(buffer, "PALETA: %s", (config->paleta_color == 0) ? "CLASICA" : (config->paleta_color == 1) ? "LUMINOSA" : "NEON");
        fuente_dibujar_texto(centro_x - 70, 130, buffer, (seleccion == 1) ? COLOR_SELECCION : 8, 1, fuente);

        sprintf(buffer, "RESOLUCION: %s", (config->resolucion_logica == 0) ? "NORMAL" : (config->resolucion_logica == 1) ? "ALTA" : "RETRO");
        fuente_dibujar_texto(centro_x - 70, 170, buffer, (seleccion == 2) ? COLOR_SELECCION : 8, 1, fuente);

        sprintf(buffer, "VEL GRAVEDAD: %s", (config->velocidad_caida == 0) ? "LENTA" : (config->velocidad_caida == 1) ? "NORMAL" : "RAPIDA");
        fuente_dibujar_texto(centro_x - 70, 210, buffer, (seleccion == 3) ? COLOR_SELECCION : 8, 1, fuente);

        sprintf(buffer, "ANCHO TABLERO DX: %d", config->columnas_deluxe);
        fuente_dibujar_texto(centro_x - 70, 250, buffer, (seleccion == 4) ? COLOR_SELECCION : 8, 1, fuente);

        fuente_dibujar_texto(centro_x - 70, 320, "VOLVER AL MENU", (seleccion == 5) ? COLOR_SELECCION : 8, 1, fuente);

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }
    *juego = 2; // Vuelve al menú
}

void Game_over(tFuente *fuente, int *juego, const tPuntuacion *punt, tConfiguracion* config)
{
    int centro_x = config->ventana_ancho / 2;

    int en_pausa = 1;
    int seleccion = 1;
    tRecords records;
    tRecord  nuevo;
    char     nombre[MAX_NOMBRE + 1];

    // Si el puntaje entra al top 5, pedimos el nombre y guardamos.
    records_cargar(&records, RUTA_RECORDS);

    if (punt->puntaje > 0 && records_es_top(&records, punt->puntaje))
    {
        Pantalla_Ingresar_Nombre(fuente, nombre, config);

        // Si canceló con ESC, nombre queda vacío y no guardamos nada.
        if (nombre[0] != '\0')
        {
            memset(&nuevo, 0, sizeof(nuevo));   // zera padding del struct
            strncpy(nuevo.nombre, nombre, MAX_NOMBRE);
            nuevo.nombre[MAX_NOMBRE] = '\0';
            nuevo.puntaje = punt->puntaje;
            nuevo.lineas  = punt->lineas;
            nuevo.nivel   = punt->nivel;

            records_agregar(&records, &nuevo);
            records_guardar(&records, RUTA_RECORDS);
        }
    }

    gbt_borrar_backbuffer(0);

    while (en_pausa)
    {
        dibujar_fondo(fuente, config);

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

        fuente_dibujar_texto(centro_x - 50, 112, "Game", COLOR_SELECCION, 3, fuente);
        fuente_dibujar_texto(centro_x - 50, 154, "Over", COLOR_SELECCION, 3, fuente);

        int color_opcion1 = (seleccion == 1) ? COLOR_SELECCION : FONDO_TAB;
        fuente_dibujar_texto(centro_x - 70, 240, "jugar de nuevo", color_opcion1, 1, fuente);

        int color_opcion2 = (seleccion == 2) ? COLOR_SELECCION : FONDO_TAB;
        fuente_dibujar_texto(centro_x - 70, 280, "ESC - VOLVER AL MENU", color_opcion2, 1, fuente);

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }
}

void Pantalla_Ingresar_Nombre(tFuente *fuente, char *nombre_out, tConfiguracion* config)
{
    int centro_x = config->ventana_ancho / 2;

    // Tabla de teclas A-Z. No asumo que GBTK_a..GBTK_z sean contiguos.
    const struct { int tecla; char letra; } TECLAS[] = {
        {GBTK_a,'A'}, {GBTK_b,'B'}, {GBTK_c,'C'}, {GBTK_d,'D'}, {GBTK_e,'E'},
        {GBTK_f,'F'}, {GBTK_g,'G'}, {GBTK_h,'H'}, {GBTK_i,'I'}, {GBTK_j,'J'},
        {GBTK_k,'K'}, {GBTK_l,'L'}, {GBTK_m,'M'}, {GBTK_n,'N'}, {GBTK_o,'O'},
        {GBTK_p,'P'}, {GBTK_q,'Q'}, {GBTK_r,'R'}, {GBTK_s,'S'}, {GBTK_t,'T'},
        {GBTK_u,'U'}, {GBTK_v,'V'}, {GBTK_w,'W'}, {GBTK_x,'X'}, {GBTK_y,'Y'},
        {GBTK_z,'Z'}
    };
    const int cant_teclas = sizeof(TECLAS) / sizeof(TECLAS[0]);

    char buffer[MAX_NOMBRE + 1];
    char display[MAX_NOMBRE + 2];   // +1 cursor, +1 '\0'
    int  largo = 0;
    int  terminado = 0;
    int  cancelado = 0;

    buffer[0] = '\0';

    while (!terminado)
    {
        gbt_procesar_entrada();

        // A-Z: agrego una letra si todavia queda lugar.
        for (int i = 0; i < cant_teclas && largo < MAX_NOMBRE; i++)
        {
            if (gbt_tecla_presionada(TECLAS[i].tecla))
            {
                buffer[largo] = TECLAS[i].letra;
                largo++;
                buffer[largo] = '\0';
                gbt_esperar(150);
                break;
            }
        }

        if (gbt_tecla_presionada(GBTK_IZQUIERDA) && largo > 0)
        {
            largo--;
            buffer[largo] = '\0';
            gbt_esperar(150);
        }

        if (gbt_tecla_presionada(GBTK_ENTER) && largo > 0)
            terminado = 1;

        if (gbt_tecla_presionada(GBTK_ESCAPE))
        {
            cancelado = 1;
            terminado = 1;
        }

        gbt_borrar_backbuffer(0);
        dibujar_fondo(fuente, config);

        fuente_dibujar_texto(centro_x - 30, 115, "NUEVO RECORD!", COLOR_TEXTO, 2, fuente);
        fuente_dibujar_texto(centro_x - 30, 170, "INGRESA TU NOMBRE:", COLOR_TEXTO, 1, fuente);


        if (largo < MAX_NOMBRE)
            snprintf(display, sizeof(display), "%s_", buffer);
        else
            snprintf(display, sizeof(display), "%s", buffer);

        fuente_dibujar_texto(centro_x, 220, display, COLOR_SELECCION, 2, fuente);

        fuente_dibujar_texto(centro_x - 70, 320, "A-Z: ESCRIBIR", FONDO_TAB, 1, fuente);
        fuente_dibujar_texto(centro_x - 70, 340, "FLECHA IZQ: BORRAR", FONDO_TAB, 1, fuente);
        fuente_dibujar_texto(centro_x - 70, 360, "ENTER: CONFIRMAR    ESC: CANCELAR", FONDO_TAB, 1, fuente);

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }

    if (cancelado)
    {
        nombre_out[0] = '\0';
    }
    else
    {
        strncpy(nombre_out, buffer, MAX_NOMBRE);
        nombre_out[MAX_NOMBRE] = '\0';
    }
}

// En menu.c
 // Asegurate de que esté este include arriba

void Pantalla_Records(tFuente *fuente, int *juego, tConfiguracion* config)
{
    int centro_x = config->ventana_ancho / 2;

    tRecords r;
    char buffer[64];

    // Intentamos cargar los récords desde un archivo binario
    // Si el archivo no existe o falla, records_cargar inicializa la lista en 0
    records_cargar(&r, RUTA_RECORDS);

    int mostrando = 1;
    while (mostrando)
    {
        gbt_procesar_entrada();

        // Si presiona ENTER o ESCAPE, volvemos al menú principal
        if (gbt_tecla_presionada(GBTK_ENTER) || gbt_tecla_presionada(GBTK_ESCAPE))
        {
            mostrando = 0;
        }

        gbt_borrar_backbuffer(0);
        dibujar_fondo(fuente, config);

        // Título de la pantalla
        fuente_dibujar_texto(centro_x - 35, 100, "TOP 5 RECORDS", COLOR_SELECCION, 2, fuente);

        // Cabecera de la tabla
        fuente_dibujar_texto(centro_x - 70, 130, "POS   NOMBRE   PUNTAJE   LINEAS   NIVEL", COLOR_TEXTO, 1, fuente);
        fuente_dibujar_texto(centro_x - 70, 145, "---------------------------------------", COLOR_TEXTO, 1, fuente);

        int y_pos = 170;
        if (r.cant == 0)
        {
            fuente_dibujar_texto(centro_x - 80, y_pos + 30, "NO HAY RECORDS GUARDADOS", COLOR_TEXTO, 1, fuente);
        }
        else
        {
            for (int i = 0; i < r.cant; i++)
            {
                // Formateamos una línea por cada récord usando sprintf
                sprintf(buffer, " %d     %-8s   %06d     %03d      %02d",
                        i + 1,
                        r.lista[i].nombre[0] != '\0' ? r.lista[i].nombre : "AAA",
                        r.lista[i].puntaje,
                        r.lista[i].lineas,
                        r.lista[i].nivel);

                // Resaltamos el primer puesto con otro color si quieren
                int color_linea = (i == 0) ? COLOR_SELECCION : FONDO_TAB;
                fuente_dibujar_texto(centro_x - 170, y_pos, buffer, color_linea, 1, fuente);
                y_pos += 25;
            }
        }

        fuente_dibujar_texto(centro_x - 70, 380, "ENTER/ESC - VOLVER", FONDO_TAB, 1, fuente);

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }

    *juego = 2; // Al salir, seteamos el estado para que main vuelva a abrir el Menú de Inicio
}

