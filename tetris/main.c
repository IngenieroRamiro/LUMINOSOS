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

#define VELOCIDAD_INICIAL 1.0f

int main()
{
    if (gbt_iniciar() < 0)
        return 1;

    if (gbt_crear_ventana("Tetris UNLaM - Luminosos", TAM_VENTANA_X, TAM_VENTANA_Y, 2) < 0)
        return 1;

    srand(time(NULL));

    uint8_t tablero[FILAS][COLS] = {0};

    int juego_corriendo = 1;
    int p_caidas = 0;
    float velocidad_actual = VELOCIDAD_INICIAL;

    int j = 0;
    int nivel = 0;

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

    while (juego_corriendo)
    {
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_ESCAPE))
            juego_corriendo = 0;

        if (gbt_temporizador_consumir(reloj_caida))
        {
            if (verificar_colision(tablero, mat_coordenads[PRUEBA]))
            {
                fijar_pieza(tablero, mat_coordenads[PRUEBA]);
                p_caidas ++;
                actualizar_velocidad(&velocidad_actual, p_caidas, &reloj_caida);

                int lineas = eliminar_lineas(tablero);

                (void)lineas;

                reiniciar_pieza(mat_coordenads[PRUEBA]);
                if(fin_juego(tablero, mat_coordenads[PRUEBA]))
                    juego_corriendo = 0;

            }
            else
            {
                borrar(tablero, mat_coordenads, &j, &nivel);

                figueras_tetris(tablero, mat_coordenads, &j, &nivel);
            }
        }

        if (gbt_tecla_presionada(GBTK_w) && PRUEBA != 5)
        {
            borrar(tablero, mat_coordenads, &j, &nivel);

            for(int i=0; i<8; i+=2)
                mat_coordenads[PRUEBA][i]--;

            rotar_universal(mat_coordenads[PRUEBA], tablero);

            figueras_tetris(tablero, mat_coordenads, &j, &nivel);

            gbt_esperar(150);
        }

        if (gbt_tecla_presionada(GBTK_d))
        {
            borrar(tablero, mat_coordenads, &j, &nivel);

            for(int i=0; i<8; i+=2)
                mat_coordenads[PRUEBA][i]--;

            mover_derecha(mat_coordenads[PRUEBA], tablero);

            figueras_tetris(tablero, mat_coordenads, &j, &nivel);

            gbt_esperar(100);
        }

        if (gbt_tecla_presionada(GBTK_a))
        {
            borrar(tablero, mat_coordenads, &j, &nivel);

            for(int i=0; i<8; i+=2)
                mat_coordenads[PRUEBA][i]--;

            mover_izquierda(mat_coordenads[PRUEBA], tablero);

            figueras_tetris(tablero, mat_coordenads, &j, &nivel);

            gbt_esperar(100);
        }

        gbt_borrar_backbuffer(0);

        dibujar_tablero(tablero);

        gbt_volcar_backbuffer();

        gbt_esperar(16);
    }

    gbt_temporizador_destruir(reloj_caida);

    gbt_cerrar();

    return 0;
}
