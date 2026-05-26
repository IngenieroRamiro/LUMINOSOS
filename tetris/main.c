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
#include "records.h"

#define RUTA_RECORDS "records.dat"

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

    tFuente fuente;
    fuente_inicializar(&fuente);

    tPuntuacion puntuacion;
    puntuacion_iniciar(&puntuacion);

    tRecords records;
    records_cargar(&records, RUTA_RECORDS);

    int figura = 0;
    int enteros_pieza = 8;

    int mat_coordenads[11][10] =
    {
        // --- CLÁSICAS (0 a 6: Completadas con ceros) ---
        {0,3, 0,4, 0,5, 0,6,  0,0}, // I
        {1,4, 1,5, 1,6, 0,6,  0,0}, // J
        {1,4, 1,5, 1,6, 0,4,  0,0}, // L
        {1,4, 1,5, 0,5, 0,6,  0,0}, // O
        {1,5, 1,6, 0,4, 0,5,  0,0}, // S
        {0,4, 0,5, 1,4, 1,5,  0,0}, // Z
        {1,3, 1,4, 1,5, 0,4,  0,0}, // T

        // --- NUEVAS "TETRIS DX" (7 a 10: 5 bloques reales) ---
        {0,5, 0,5, 0,5, 0,5,  0,5}, // 7) Monomino
        {0,4, 0,5, 1,4, 2,4,  2,5}, // 8) Forma de C
        {0,4, 0,5, 1,4, 1,5,  2,4}, // 9) Forma de P
        {0,4, 0,6, 1,4, 1,6,  2,5}  // 10) Forma de U de la UNLaM
    };

    Pantalla_Inicio (&fuente, &juego_corriendo);

    tGBT_Temporizador* reloj_caida = gbt_temporizador_crear(velocidad_actual);

    while (juego_corriendo)
    {
        gbt_procesar_entrada();

        if (gbt_tecla_presionada(GBTK_ESCAPE))
        {
            Pausar_Juego (&fuente, &juego_corriendo);
        }

        if (juego_corriendo == 2)
        {
            Pantalla_Inicio(&fuente, &juego_corriendo);

            if(juego_corriendo == 1 || juego_corriendo == 3)
            {
                Reiniciar_Tablero(tablero);
                puntuacion_iniciar(&puntuacion);
                p_caidas = 0;
                velocidad_actual = VELOCIDAD_INICIAL;

                if (juego_corriendo == 3)
                {
                    figura = rand() % 11;
                    enteros_pieza = (figura >= 7) ? 10 : 8;
                }
                else
                {
                    figura = rand() % 7;
                    enteros_pieza = 8;
                }

                int figura_fijada = figura;
                reiniciar_pieza_10(mat_coordenads, figura_fijada);
                figura = figura_fijada;
            }
        }

        if (juego_corriendo == 4)
        {
            Pantalla_Records(&fuente, &records);
            juego_corriendo = 2;
        }

        if (gbt_tecla_presionada(GBTK_ESCAPE))
            juego_corriendo = 0;

        if (juego_corriendo == 1 || juego_corriendo == 3)
        {
            if (gbt_temporizador_consumir(reloj_caida))
            {
                if (verificar_colision(tablero, mat_coordenads[figura], enteros_pieza))
                {
                    fijar_pieza(tablero, mat_coordenads[figura], enteros_pieza);
                    p_caidas ++;
                    actualizar_velocidad(&velocidad_actual, p_caidas, &reloj_caida, 0);

                    int lineas = eliminar_lineas(tablero);
                    if (lineas > 0)
                        puntuacion_sumar_lineas(&puntuacion, lineas);

                    if (juego_corriendo == 3)
                    {
                        figura = rand() % 11;
                        enteros_pieza = (figura >= 7) ? 10 : 8;
                    }
                    else
                    {
                        figura = rand() % 7;
                        enteros_pieza = 8;
                    }

                    int figura_fijada = figura;
                    reiniciar_pieza_10(mat_coordenads, figura_fijada);
                    figura = figura_fijada;

                    if(fin_juego(tablero, mat_coordenads[figura]))
                    {
                        if (records_es_top(&records, puntuacion.puntaje))
                        {
                            tRecord nuevo;
                            Pantalla_Ingresar_Nombre(&fuente, nuevo.nombre, MAX_NOMBRE);
                            nuevo.puntaje = puntuacion.puntaje;
                            nuevo.lineas  = puntuacion.lineas;
                            nuevo.nivel   = puntuacion.nivel;
                            records_agregar(&records, &nuevo);
                            records_guardar(&records, RUTA_RECORDS);
                        }

                        Reiniciar_Tablero (tablero);
                        reiniciar_pieza_10(mat_coordenads, figura);
                        Game_over(&fuente, &juego_corriendo);
                        puntuacion_iniciar(&puntuacion);
                        actualizar_velocidad(&velocidad_actual, p_caidas, &reloj_caida, 1);
                    }

                    if (juego_corriendo == 2)
                        Pantalla_Inicio (&fuente, &juego_corriendo);
                }
                else
                {
                    borrar(tablero, mat_coordenads[figura], enteros_pieza);
                    figuras_caen(tablero, mat_coordenads[figura], enteros_pieza);
                }
            }

            if (gbt_tecla_presionada(GBTK_w) && (juego_corriendo == 3 || figura != 5))
            {
                borrar(tablero, mat_coordenads[figura], enteros_pieza);

                if (juego_corriendo == 3)
                {
                    rotar_deluxe(mat_coordenads[figura], tablero);
                }
                else
                {
                    rotar_universal(mat_coordenads[figura], tablero);
                }

                figuras_caen(tablero, mat_coordenads[figura], enteros_pieza);
                gbt_esperar(150);
            }

        if (gbt_tecla_presionada(GBTK_d))
        {
            borrar(tablero, mat_coordenads[figura], enteros_pieza);


            for(int i = 0; i < enteros_pieza; i += 2)
                mat_coordenads[figura][i]--;

            if (juego_corriendo == 3)
            {
                for(int i = 1; i < enteros_pieza; i += 2)
                {
                    mat_coordenads[figura][i]++;
                    if (mat_coordenads[figura][i] >= COLS)
                        mat_coordenads[figura][i] = 0;
                }

                int choco_lateral = 0;
                for (int i = 0; i < enteros_pieza; i += 2) {
                    if (tablero[mat_coordenads[figura][i]][mat_coordenads[figura][i+1]] == 2) {
                        choco_lateral = 1;
                        break;
                    }
                }

                if (choco_lateral) {
                    for(int i = 1; i < enteros_pieza; i += 2) {
                        mat_coordenads[figura][i]--;
                        if (mat_coordenads[figura][i] < 0)
                            mat_coordenads[figura][i] = COLS - 1;
                    }
                }
            }
            else
            {
                mover_derecha(mat_coordenads[figura], tablero);
            }

            figuras_caen(tablero, mat_coordenads[figura], enteros_pieza);
            gbt_esperar(100);
        }

        if (gbt_tecla_presionada(GBTK_a))
        {
            borrar(tablero, mat_coordenads[figura], enteros_pieza);

            for(int i = 0; i < enteros_pieza; i += 2)
                mat_coordenads[figura][i]--;

            if (juego_corriendo == 3)
            {
                for(int i = 1; i < enteros_pieza; i += 2)
                {
                    mat_coordenads[figura][i]--;
                    if (mat_coordenads[figura][i] < 0)
                        mat_coordenads[figura][i] = COLS - 1;
                }

                int choco_lateral = 0;
                for (int i = 0; i < enteros_pieza; i += 2) {
                    if (tablero[mat_coordenads[figura][i]][mat_coordenads[figura][i+1]] == 2) {
                        choco_lateral = 1;
                        break;
                    }
                }

                if (choco_lateral) {
                    for(int i = 1; i < enteros_pieza; i += 2) {
                        mat_coordenads[figura][i]++;
                        if (mat_coordenads[figura][i] >= COLS)
                            mat_coordenads[figura][i] = 0;
                    }
                }
            }
            else
            {
                mover_izquierda(mat_coordenads[figura], tablero);
            }

            figuras_caen(tablero, mat_coordenads[figura], enteros_pieza);
            gbt_esperar(100);
        }

            if( gbt_tecla_presionada(GBTK_ESPACIO) )
            {
                borrar(tablero, mat_coordenads[figura], enteros_pieza);

                while (verificar_colision(tablero, mat_coordenads[figura], enteros_pieza) == 0)
                {
                    for(int i = 0; i < enteros_pieza; i += 2)
                        mat_coordenads[figura][i]++;
                }

                fijar_pieza(tablero, mat_coordenads[figura], enteros_pieza);
                p_caidas++;
                actualizar_velocidad(&velocidad_actual, p_caidas, &reloj_caida, 0);

                int lineas = eliminar_lineas(tablero);
                if (lineas > 0)
                    puntuacion_sumar_lineas(&puntuacion, lineas);

                if (juego_corriendo == 3)
                {
                    figura = rand() % 11;
                    enteros_pieza = (figura >= 7) ? 10 : 8;
                }
                else
                {
                    figura = rand() % 7;
                    enteros_pieza = 8;
                }

                int figura_fijada = figura;
                reiniciar_pieza_10(mat_coordenads, figura_fijada);
                figura = figura_fijada;

                gbt_esperar(180);
            }
        }

        gbt_borrar_backbuffer(0);
        dibujar_fondo(&fuente);
        dibujar_tablero(tablero);
        dibujar_hud(&puntuacion, &fuente);
        gbt_volcar_backbuffer();

        gbt_esperar(16);
    }

    gbt_temporizador_destruir(reloj_caida);
    gbt_cerrar();
    return 0;
}
