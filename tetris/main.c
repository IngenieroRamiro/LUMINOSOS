/*

Apellido, Nombre: Gil, Alen Emmanuel
DNI: 45073489
Usuario: AlenEmG
Entrega: Sí

Apellido, Nombre: Spinetta, Luis Alberto
DNI: 12345678
Usuario: LuisAS21
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
#include "colision.h"
#include "piezas.h"
#include "dificultad.h"
#include "fuentes.h"
#include "menu.h"
#include "puntuacion.h"

#define VELOCIDAD_INICIAL 0.3f

int main()
{
    if (gbt_iniciar() < 0)
        return 1;

    if (gbt_crear_ventana("Tetris UNLaM - Luminosos", TAM_VENTANA_X, TAM_VENTANA_Y, 2) < 0)
        return 1;

    srand(time(NULL));

    uint8_t tablero[FILAS][COLS] = {0};

    int juego_estado = 0;
    int p_caidas = 0;
    float velocidad_actual = VELOCIDAD_INICIAL;

    tFuente fuente;
    fuente_inicializar(&fuente);

    tPuntuacion puntuacion;
    puntuacion_iniciar(&puntuacion);

    int num = rand () % 7;
    int* figura = &num;
    int modo_deluxe = 0;

    int mat_coordenads[PIEZAS][8] =
    {
        {0,3,0,4,0,5,0,6},
        {1,4,1,5,1,6,0,6},
        {1,4,1,5,1,6,0,4},
        {1,4,1,5,0,5,0,6},
        {1,5,1,6,0,4,0,5},
        {0,4,0,5,1,4,1,5},
        {1,3,1,4,1,5,0,4}
    };

    tGBT_Temporizador* reloj_caida = gbt_temporizador_crear(velocidad_actual);

    while (juego_estado != -1)
    {
        if (juego_estado == 0)
        {
            Pantalla_Inicio(&fuente, &juego_estado, tablero, mat_coordenads[*figura], figura, &p_caidas, &velocidad_actual, &modo_deluxe, &puntuacion);

            if (juego_estado == 0)
            {
                juego_estado = -1;
            }
        }

        if (juego_estado == 1)
        {
            Reiniciar_Tablero(tablero);
            reiniciar_pieza(mat_coordenads, *figura);
            puntuacion_iniciar(&puntuacion);
            p_caidas = 0;
            velocidad_actual = VELOCIDAD_INICIAL;

            gbt_temporizador_destruir(reloj_caida);
            reloj_caida = gbt_temporizador_crear(velocidad_actual);

            juego_estado = 2;
        }

        if (juego_estado == 3)
        {
            gbt_temporizador_destruir(reloj_caida);
            reloj_caida = gbt_temporizador_crear(velocidad_actual);

            juego_estado = 2;
        }

        while (juego_estado == 2)
        {
            gbt_procesar_entrada();


            if (gbt_tecla_presionada(GBTK_ESCAPE))
            {
                Pausar_Juego(&fuente, &juego_estado, tablero, mat_coordenads[*figura], *figura, p_caidas, velocidad_actual, &puntuacion, modo_deluxe);
            }


            if (juego_estado == 2 && gbt_temporizador_consumir(reloj_caida))
            {
                if (verificar_colision(tablero, mat_coordenads[*figura]))
                {
                    fijar_pieza(tablero, mat_coordenads[*figura]);
                    p_caidas++;
                    actualizar_velocidad(&velocidad_actual, p_caidas, &reloj_caida);

                    int lineas = eliminar_lineas(tablero);
                    if (lineas > 0)
                        puntuacion_sumar_lineas(&puntuacion, lineas);

                    reiniciar_pieza(mat_coordenads, *figura);
                    *figura = rand() % 7;

                    if (fin_juego(tablero, mat_coordenads[*figura]))
                    {
                        juego_estado = 0;
                    }
                }
                else
                {
                    borrar(tablero, mat_coordenads[*figura]);
                    figuras_caen(tablero, mat_coordenads[*figura]);
                }
            }


            if (gbt_tecla_presionada(GBTK_w) && *figura != 5)
            {
                borrar(tablero, mat_coordenads[*figura]);

                if (modo_deluxe)
                {
                    rotar_deluxe(mat_coordenads[*figura], tablero);
                }
                else
                {
                    for(int i = 0; i < 8; i += 2)
                        mat_coordenads[*figura][i]--;

                    rotar_universal(mat_coordenads[*figura], tablero);
                }

                figuras_caen(tablero, mat_coordenads[*figura]);
                gbt_esperar(150);
            }

            if (gbt_tecla_presionada(GBTK_d))
            {
                borrar(tablero, mat_coordenads[*figura]);

                if (modo_deluxe)
                {
                    for(int i = 1; i < 8; i += 2)
                    {
                        mat_coordenads[*figura][i]++;
                        if (mat_coordenads[*figura][i] >= COLS)
                            mat_coordenads[*figura][i] = 0;
                    }
                }
                else
                {
                    mover_derecha(mat_coordenads[*figura], tablero);
                }

                figuras_caen(tablero, mat_coordenads[*figura]);
                gbt_esperar(100);
            }

            if (gbt_tecla_presionada(GBTK_a))
            {
                borrar(tablero, mat_coordenads[*figura]);

                if (modo_deluxe)
                {
                    for(int i = 1; i < 8; i += 2)
                    {
                        mat_coordenads[*figura][i]--;
                        if (mat_coordenads[*figura][i] < 0)
                            mat_coordenads[*figura][i] = COLS - 1;
                    }
                }
                else
                {
                    mover_izquierda(mat_coordenads[*figura], tablero);
                }

                figuras_caen(tablero, mat_coordenads[*figura]);
                gbt_esperar(100);
            }

            if (gbt_tecla_presionada(GBTK_ESPACIO))
            {
                borrar(tablero, mat_coordenads[*figura]);

                while (verificar_colision(tablero, mat_coordenads[*figura]) == 0)
                    for(int i = 0; i < 8; i += 2)
                        mat_coordenads[*figura][i]++;

                fijar_pieza(tablero, mat_coordenads[*figura]);
                p_caidas++;
                actualizar_velocidad(&velocidad_actual, p_caidas, &reloj_caida);

                int lineas = eliminar_lineas(tablero);
                if (lineas > 0)
                    puntuacion_sumar_lineas(&puntuacion, lineas);

                reiniciar_pieza(mat_coordenads, *figura);
                *figura = rand() % 7;

                gbt_esperar(180);
            }

            gbt_borrar_backbuffer(0);

            dibujar_fondo(&fuente);
            dibujar_tablero(tablero);
            dibujar_hud(&puntuacion, &fuente);

            gbt_volcar_backbuffer();
            gbt_esperar(16);
        }
    }

    gbt_temporizador_destruir(reloj_caida);
    gbt_cerrar();

    return 0;
}
