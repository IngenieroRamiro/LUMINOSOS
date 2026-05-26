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


int main()
{
    if (gbt_iniciar() < 0)
        return 1;

    if (gbt_crear_ventana("Tetris UNLaM - Luminosos", TAM_VENTANA_X, TAM_VENTANA_Y, 2) < 0)
        return 1;

    srand(time(NULL));

    //uint8_t tablero[FILAS][COLS] = {0};
    tTablero tablero;

    if (!tablero_crear(&tablero, FILAS, COLS))
        return 1; //nuevo

    int juego_corriendo = 1;
    int p_caidas = 0;
    float velocidad_actual = VELOCIDAD_INICIAL;

    tFuente fuente;
    fuente_inicializar(&fuente);

    tPuntuacion puntuacion;
    puntuacion_iniciar(&puntuacion);


    int figura = rand () % 7;
    //int* figura = &num;

    tPieza pieza;
    pieza_generar(&pieza, figura);//nuevo

    /*int mat_coordenads[PIEZAS][8] =
    {
        {0,3,0,4,0,5,0,6},
        {1,4,1,5,1,6,0,6},
        {1,4,1,5,1,6,0,4},
        {1,4,1,5,0,5,0,6},
        {1,5,1,6,0,4,0,5},
        {0,4,0,5,1,4,1,5},
        {1,3,1,4,1,5,0,4}
    };*/

    Pantalla_Inicio (&fuente, &juego_corriendo);

    tGBT_Temporizador* reloj_caida = gbt_temporizador_crear(velocidad_actual); //PRUEBA

    while (juego_corriendo)
    {
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_ESCAPE))
        {
            Pausar_Juego (&fuente, &juego_corriendo);
        }

        if (juego_corriendo == 2)
        {
            Pantalla_Inicio (&fuente, &juego_corriendo);

            if(juego_corriendo == 1)
            {
                /*Reiniciar_Tablero (tablero);
                reiniciar_pieza(mat_coordenads, figura);*/
                tablero_limpiar(&tablero);
                figura = rand() % 7;
                pieza_generar(&pieza, figura);//nuevo
                puntuacion_iniciar(&puntuacion);
                velocidad_actual = VELOCIDAD_INICIAL;
                p_caidas = 0;
                actualizar_velocidad(&velocidad_actual, p_caidas, &reloj_caida, 1 );
            }
        }

        /*if (gbt_tecla_presionada(GBTK_ESCAPE))
            juego_corriendo = 0;*/ ///ya no

        /*if (gbt_temporizador_consumir(reloj_caida))
        {
            if (verificar_colision(tablero, mat_coordenads[figura]))
            {
                fijar_pieza(tablero, mat_coordenads[figura]);
                p_caidas ++;
                actualizar_velocidad(&velocidad_actual, p_caidas, &reloj_caida, 0);

                int lineas = eliminar_lineas(tablero);
                if (lineas > 0)

                    puntuacion_sumar_lineas(&puntuacion, lineas);

                reiniciar_pieza(mat_coordenads, figura);
                figura = rand() % 7;

                if(fin_juego(tablero, mat_coordenads[figura]))
                {
                    Reiniciar_Tablero (tablero);
                    reiniciar_pieza(mat_coordenads, figura);
                    Game_over(&fuente, &juego_corriendo);
                    puntuacion_iniciar(&puntuacion);
                    actualizar_velocidad(&velocidad_actual, p_caidas, &reloj_caida, 1);
                }

                if (juego_corriendo == 2)
                    Pantalla_Inicio (&fuente, &juego_corriendo);
            }
            else
            {
                borrar(tablero, mat_coordenads[figura]);

                figuras_caen(tablero, mat_coordenads[figura]);

            }
        }*/

        /*if (gbt_tecla_presionada(GBTK_w) && figura != 5)
        {
            borrar(tablero, mat_coordenads[figura]);

            for(int i=0; i<8; i+=2)
                mat_coordenads[figura][i]--;

            rotar_universal(mat_coordenads[figura], tablero);

            figuras_caen(tablero, mat_coordenads[figura]);

            gbt_esperar(150);
        }*/
        if (gbt_temporizador_consumir(reloj_caida))
        {
            if (pieza_puede_mover(&tablero, &pieza, 1, 0))
            {
                pieza_mover(&pieza, 1, 0);
            }
            else
            {
                pieza_fijar(&tablero, &pieza);

                p_caidas++;

                actualizar_velocidad(&velocidad_actual, p_caidas, &reloj_caida, 0);

                int lineas = eliminar_lineas(&tablero);

                if (lineas > 0)
                    puntuacion_sumar_lineas(&puntuacion, lineas);

                figura = rand() % 7;

                pieza_generar(&pieza, figura);

                if (!pieza_puede_mover(&tablero, &pieza, 0, 0))
                {
                    tablero_limpiar(&tablero);

                    puntuacion_iniciar(&puntuacion);

                    velocidad_actual = VELOCIDAD_INICIAL;

                    p_caidas = 0;

                    actualizar_velocidad( &velocidad_actual, p_caidas, &reloj_caida, 1);

                    Game_over(&fuente, &juego_corriendo);
                }

                continue;
            }
        }

        if (gbt_tecla_presionada(GBTK_w))
        {
            if (pieza_puede_rotar(&tablero, &pieza))
                pieza_rotar(&pieza);

            gbt_esperar(150);
        }//nuevo

        /*if (gbt_tecla_presionada(GBTK_d))
        {
            borrar(tablero, mat_coordenads[figura]);

            for(int i=0; i<8; i+=2)
                mat_coordenads[figura][i]--;

            mover_derecha(mat_coordenads[figura], tablero);

            figuras_caen(tablero, mat_coordenads[figura]);

            gbt_esperar(100);
        }*/
        if (gbt_tecla_presionada(GBTK_d))
        {
            if (pieza_puede_mover(&tablero, &pieza, 0, 1))
                pieza_mover(&pieza, 0, 1);

            gbt_esperar(100);
        }//nuevo

        /*if (gbt_tecla_presionada(GBTK_a))
        {
            borrar(tablero, mat_coordenads[figura]);

            for(int i=0; i<8; i+=2)
                mat_coordenads[figura][i]--;

            mover_izquierda(mat_coordenads[figura], tablero);

            figuras_caen(tablero, mat_coordenads[figura]);

            gbt_esperar(100);
        }*/
        if (gbt_tecla_presionada(GBTK_a))
        {
            if (pieza_puede_mover(&tablero, &pieza, 0, -1))
                pieza_mover(&pieza, 0, -1);

            gbt_esperar(100);
        }//nuevo

        /*if( gbt_tecla_presionada(GBTK_ESPACIO) )
        {
            borrar(tablero, mat_coordenads[figura]);

            while (verificar_colision(tablero, mat_coordenads[figura]) == 0)
                for(int i = 0; i < 8; i += 2)
                    mat_coordenads[figura][i]++;


            fijar_pieza(tablero, mat_coordenads[figura]);
            p_caidas++;
            actualizar_velocidad(&velocidad_actual, p_caidas, &reloj_caida, 0);

            int lineas = eliminar_lineas(tablero);

            if (lineas > 0)
                puntuacion_sumar_lineas(&puntuacion, lineas);

            reiniciar_pieza(mat_coordenads, figura);
            figura = rand() % 7;

            gbt_esperar(180);
        }*/
        if (gbt_tecla_presionada(GBTK_ESPACIO))
        {
            while (pieza_puede_mover(&tablero, &pieza, 1, 0))
            {
                pieza_mover(&pieza, 1, 0);
            }

            pieza_fijar(&tablero, &pieza);

            p_caidas++;

            actualizar_velocidad(&velocidad_actual, p_caidas, &reloj_caida, 0);

            int lineas = eliminar_lineas(&tablero);

            if (lineas > 0)
                puntuacion_sumar_lineas(&puntuacion, lineas);

            figura = rand() % 7;

            pieza_generar(&pieza, figura);

            if (!pieza_puede_mover(&tablero, &pieza, 0, 0))
            {
                tablero_limpiar(&tablero);

                puntuacion_iniciar(&puntuacion);

                velocidad_actual = VELOCIDAD_INICIAL;

                p_caidas = 0;

                actualizar_velocidad(&velocidad_actual, p_caidas, &reloj_caida, 1);

                Game_over(&fuente, &juego_corriendo);
            }

            gbt_esperar(120);

            continue;
        }//nuevo





        gbt_borrar_backbuffer(0);

        /*int tab = */dibujar_fondo(&fuente);

        //printf("T: %d",tab);

        //dibujar_tablero(tablero);
        dibujar_tablero(&tablero, &pieza);//nuevo
        dibujar_hud(&puntuacion, &fuente);
        gbt_volcar_backbuffer();

        gbt_esperar(16);
    }

    gbt_temporizador_destruir(reloj_caida);

    tablero_destruir(&tablero);//nuevo

    gbt_cerrar();

    return 0;
}
