/*

Apellido, Nombre: Gil, Alen Emmanuel
DNI: 45073489
Usuario: AlenEmG
Entrega: Sí

Apellido, Nombre: Spinetta, Luis Alberto
DNI: 12345678
Usuario: LuisAS21
Entrega: Sí

*/

#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "GBT/gbt.h"

#include "tipos.h"
#include "render.h"
#include "tablero.h"
#include "piezas.h"
#include "dificultad.h"
#include "fuentes.h"
#include "menu.h"
#include "puntuacion.h"

int main()
{
    tConfiguracion config_juego;
    tTablero tablero;
    int juego_corriendo;
    int p_caidas;
    float velocidad_actual;
    tFuente fuente;
    tPuntuacion puntuacion;
    int figura;
    tPieza pieza;
    tGBT_Temporizador* reloj_caida;

    int* p_juego;
    float* p_vel;
    int* p_caidas_aux;
    tTablero* p_tab;
    tConfiguracion* p_conf;
    int columnas_a_crear;
    int lineas;

    if (gbt_iniciar() < 0)
        return 1;

    if (gbt_crear_ventana("Tetris UNLaM - Luminosos", TAM_VENTANA_X, TAM_VENTANA_Y, 2) < 0)
        return 1;

    srand(time(NULL));

    config_juego.paleta_color = 0;
    config_juego.resolucion_logica = 0;
    config_juego.velocidad_caida = 1;
    config_juego.columnas_deluxe = COLS_NORMAL;

    if (!tablero_crear(&tablero, FILAS, COLS_NORMAL))
        return 1;

    juego_corriendo = 2;
    p_caidas = 0;
    velocidad_actual = VELOCIDAD_INICIAL;

    fuente_inicializar(&fuente);
    puntuacion_iniciar(&puntuacion);

    figura = rand() % 7;
    pieza_generar(&pieza, figura);

    reloj_caida = gbt_temporizador_crear(velocidad_actual);

    p_juego = &juego_corriendo;
    p_vel = &velocidad_actual;
    p_caidas_aux = &p_caidas;

    while (*p_juego)
    {
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_ESCAPE))
        {
            Pausar_Juego(&fuente, p_juego);
        }

        if (*p_juego == 2)
        {
            Pantalla_Inicio(&fuente, p_juego, &config_juego);

            if(*p_juego == 1 || *p_juego == 3)
            {
                p_tab = &tablero;
                tablero_destruir(p_tab);

                p_conf = &config_juego;
                columnas_a_crear = (*p_juego == 3) ? p_conf->columnas_deluxe : COLS_NORMAL;

                tablero_crear(p_tab, FILAS, columnas_a_crear);

                figura = rand() % ((*p_juego == 3) ? PIEZAS_DELUXE : PIEZAS_NORMAL);
                pieza_generar(&pieza, figura);

                puntuacion_iniciar(&puntuacion);

                if (p_conf->velocidad_caida == 0)      *p_vel = 1.3f;
                else if (p_conf->velocidad_caida == 1) *p_vel = 1.0f;
                else                                   *p_vel = 0.6f;

                *p_caidas_aux = 0;

                gbt_temporizador_destruir(reloj_caida);
                reloj_caida = gbt_temporizador_crear(*p_vel);
            }
        }

        if (*p_juego == 5)
        {
            Pantalla_Configuracion(&fuente, p_juego, &config_juego);
        }

        if (*p_juego == 1 || *p_juego == 3)
        {
            if (gbt_temporizador_consumir(reloj_caida))
            {
                if (pieza_puede_mover(&tablero, &pieza, 1, 0))
                {
                    pieza_mover(&pieza, 1, 0);
                }
                else
                {
                    pieza_fijar(&tablero, &pieza);
                    (*p_caidas_aux)++;
                    actualizar_velocidad(p_vel, *p_caidas_aux, &reloj_caida, 0);

                    lineas = eliminar_lineas(&tablero);
                    if (lineas > 0)
                        puntuacion_sumar_lineas(&puntuacion, lineas);

                    figura = rand() % ((*p_juego == 3) ? PIEZAS_DELUXE : PIEZAS_NORMAL);
                    pieza_generar(&pieza, figura);

                    if (!pieza_puede_mover(&tablero, &pieza, 0, 0))
                    {
                        tablero_limpiar(&tablero);
                        puntuacion_iniciar(&puntuacion);
                        *p_vel = VELOCIDAD_INICIAL;
                        *p_caidas_aux = 0;
                        actualizar_velocidad(p_vel, *p_caidas_aux, &reloj_caida, 1);
                        Game_over(&fuente, p_juego);
                    }
                    continue;
                }
            }

            if (gbt_tecla_presionada(GBTK_w))
            {
                if (*p_juego == 3)
                {
                    pieza_rotar_deluxe(&tablero, &pieza);
                }
                else
                {
                    if (pieza_puede_rotar(&tablero, &pieza))
                        pieza_rotar(&pieza);
                }
                gbt_esperar(150);
            }

            if (gbt_tecla_presionada(GBTK_d))
            {
                if (*p_juego == 3)
                    pieza_mover_deluxe_horizontal(&tablero, &pieza, 1); // Pac-Man
                else if (pieza_puede_mover(&tablero, &pieza, 0, 1))
                    pieza_mover(&pieza, 0, 1);
                gbt_esperar(100);
            }

            if (gbt_tecla_presionada(GBTK_a))
            {
                if (*p_juego == 3)
                    pieza_mover_deluxe_horizontal(&tablero, &pieza, -1); // Pac-Man
                else if (pieza_puede_mover(&tablero, &pieza, 0, -1))
                    pieza_mover(&pieza, 0, -1);
                gbt_esperar(100);
            }

            if (gbt_tecla_presionada(GBTK_ESPACIO))
            {
                while (pieza_puede_mover(&tablero, &pieza, 1, 0))
                {
                    pieza_mover(&pieza, 1, 0);
                }

                pieza_fijar(&tablero, &pieza);
                (*p_caidas_aux)++;
                actualizar_velocidad(p_vel, *p_caidas_aux, &reloj_caida, 0);

                lineas = eliminar_lineas(&tablero);
                if (lineas > 0)
                    puntuacion_sumar_lineas(&puntuacion, lineas);

                figura = rand() % ((*p_juego == 3) ? PIEZAS_DELUXE : PIEZAS_NORMAL);
                pieza_generar(&pieza, figura);

                if (!pieza_puede_mover(&tablero, &pieza, 0, 0))
                {
                    tablero_limpiar(&tablero);
                    puntuacion_iniciar(&puntuacion);
                    *p_vel = VELOCIDAD_INICIAL;
                    *p_caidas_aux = 0;
                    actualizar_velocidad(p_vel, *p_caidas_aux, &reloj_caida, 1);
                    Game_over(&fuente, p_juego);
                }
                gbt_esperar(120);
                continue;
            }

            gbt_borrar_backbuffer(0);
            dibujar_fondo(&fuente);
            dibujar_tablero(&tablero, &pieza);
            dibujar_hud(&puntuacion, &fuente);
            gbt_volcar_backbuffer();
            gbt_esperar(16);
        }
    }

    gbt_temporizador_destruir(reloj_caida);
    tablero_destruir(&tablero);
    gbt_cerrar();
    return 0;
}
