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

<<<<<<< Updated upstream
void Game_over(tFuente *fuente, int *juego)
=======
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

void Game_over(tFuente *fuente, int *juego, const tPuntuacion *punt)
>>>>>>> Stashed changes
{
    int en_pausa = 1;
    int seleccion = 1;
    tRecords records;
    tRecord  nuevo;
    char     nombre[MAX_NOMBRE + 1];

    /* Si el puntaje entra al top 5, le pedimos nombre y persistimos. */
    records_cargar(&records, RUTA_ESTADISTICAS);

    if (punt->puntaje > 0 && records_es_top(&records, punt->puntaje))
    {
        Pantalla_Ingresar_Nombre(fuente, nombre);

        if (nombre[0] != '\0')   /* si cancelo con ESC, no guarda */
        {
            memset(&nuevo, 0, sizeof(nuevo));  /* zera padding -> binario estable */
            strncpy(nuevo.nombre, nombre, MAX_NOMBRE);
            nuevo.nombre[MAX_NOMBRE] = '\0';
            nuevo.puntaje = punt->puntaje;
            nuevo.lineas  = punt->lineas;
            nuevo.nivel   = punt->nivel;

            records_agregar(&records, &nuevo);
            records_guardar(&records, RUTA_ESTADISTICAS);
        }
    }

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
                en_pausa = 0;
            if (seleccion == 2)
            {
                en_pausa = 0;
                *juego = 2;
            }
        }

        if (gbt_tecla_presionada(GBTK_ESCAPE))
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

<<<<<<< Updated upstream
    for (int i = 0; i < 10; i++)
        if (gbt_tecla_presionada(GBTK_0 + i))
            return (char)('0' + i);
=======
    records_cargar(&r, RUTA_ESTADISTICAS);
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
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
=======
        if (gbt_tecla_presionada(GBTK_ENTER) || gbt_tecla_presionada(GBTK_ESCAPE))
            mostrando = 0;
>>>>>>> Stashed changes

        gbt_borrar_backbuffer(0);
        dibujar_fondo(fuente);

<<<<<<< Updated upstream
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
=======
        fuente_dibujar_texto(220, 60, "TOP 5 RECORDS", 31, 2, fuente);
        fuente_dibujar_texto(120, 130, "POS   NOMBRE   PUNTAJE   LINEAS   NIVEL", 11, 1, fuente);
        fuente_dibujar_texto(120, 145, "---------------------------------------", 8, 1, fuente);

        int y_pos = 170;
        if (r.cant == 0)
        {
            fuente_dibujar_texto(200, y_pos + 30, "NO HAY RECORDS GUARDADOS", 8, 1, fuente);
        }
        else
        {
            for (int i = 0; i < r.cant; i++)
            {
                sprintf(buffer, " %d     %-8s   %06d     %03d      %02d",
                        i + 1,
                        r.lista[i].nombre[0] != '\0' ? r.lista[i].nombre : "AAA",
                        r.lista[i].puntaje,
                        r.lista[i].lineas,
                        r.lista[i].nivel);

                int color_linea = (i == 0) ? 30 : 7;
                fuente_dibujar_texto(120, y_pos, buffer, color_linea, 1, fuente);
                y_pos += 25;
            }
        }

        fuente_dibujar_texto(210, 380, "ENTER/ESC - VOLVER", 8, 1, fuente);
>>>>>>> Stashed changes

        gbt_volcar_backbuffer();
        gbt_esperar(16);
        frame++;
    }
<<<<<<< Updated upstream
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
=======

    *juego = 2;
}

void Pantalla_Ingresar_Nombre(tFuente *fuente, char *nombre_out)
{
    /* Tabla local: tecla GBT -> letra. No asumo contiguidad de GBTK_a..GBTK_z. */
    const struct { int tecla; char letra; } TECLAS_LETRAS[] = {
        {GBTK_a, 'A'}, {GBTK_b, 'B'}, {GBTK_c, 'C'}, {GBTK_d, 'D'}, {GBTK_e, 'E'},
        {GBTK_f, 'F'}, {GBTK_g, 'G'}, {GBTK_h, 'H'}, {GBTK_i, 'I'}, {GBTK_j, 'J'},
        {GBTK_k, 'K'}, {GBTK_l, 'L'}, {GBTK_m, 'M'}, {GBTK_n, 'N'}, {GBTK_o, 'O'},
        {GBTK_p, 'P'}, {GBTK_q, 'Q'}, {GBTK_r, 'R'}, {GBTK_s, 'S'}, {GBTK_t, 'T'},
        {GBTK_u, 'U'}, {GBTK_v, 'V'}, {GBTK_w, 'W'}, {GBTK_x, 'X'}, {GBTK_y, 'Y'},
        {GBTK_z, 'Z'}
    };
    const int cant_teclas = sizeof(TECLAS_LETRAS) / sizeof(TECLAS_LETRAS[0]);

    char buffer[MAX_NOMBRE + 1];
    char display[MAX_NOMBRE + 2];   /* +1 cursor, +1 '\0' */
    int  largo = 0;
    int  terminado = 0;
    int  cancelado = 0;

    buffer[0] = '\0';

    while (!terminado)
    {
        gbt_procesar_entrada();

        /* Letras: agrego una mientras quede lugar. */
        for (int i = 0; i < cant_teclas && largo < MAX_NOMBRE; i++)
        {
            if (gbt_tecla_presionada(TECLAS_LETRAS[i].tecla))
            {
                buffer[largo] = TECLAS_LETRAS[i].letra;
                largo++;
                buffer[largo] = '\0';
                gbt_esperar(150);
                break;
            }
        }

        /* Flecha izquierda: borrar ultima letra. */
        if (gbt_tecla_presionada(GBTK_IZQUIERDA) && largo > 0)
        {
            largo--;
            buffer[largo] = '\0';
            gbt_esperar(150);
        }

        /* Confirmar (necesita al menos una letra). */
        if (gbt_tecla_presionada(GBTK_ENTER) && largo > 0)
            terminado = 1;

        /* Cancelar: no se guarda nada. */
        if (gbt_tecla_presionada(GBTK_ESCAPE))
        {
            cancelado = 1;
            terminado = 1;
>>>>>>> Stashed changes
        }

        gbt_borrar_backbuffer(0);
        dibujar_fondo(fuente);

<<<<<<< Updated upstream
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
=======
        fuente_dibujar_texto(200, 100, "NUEVO RECORD!", 31, 2, fuente);
        fuente_dibujar_texto(200, 170, "INGRESA TU NOMBRE:", 11, 1, fuente);

        /* Cursor "_" mientras quede lugar para escribir. */
        if (largo < MAX_NOMBRE)
            snprintf(display, sizeof(display), "%s_", buffer);
        else
            snprintf(display, sizeof(display), "%s", buffer);

        fuente_dibujar_texto(250, 220, display, 30, 2, fuente);

        fuente_dibujar_texto(150, 320, "A-Z: ESCRIBIR", 8, 1, fuente);
        fuente_dibujar_texto(150, 340, "FLECHA IZQ: BORRAR", 8, 1, fuente);
        fuente_dibujar_texto(150, 360, "ENTER: CONFIRMAR    ESC: CANCELAR", 8, 1, fuente);

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
>>>>>>> Stashed changes
}
