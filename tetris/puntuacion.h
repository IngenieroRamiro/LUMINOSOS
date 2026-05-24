#ifndef PUNTUACION_H
#define PUNTUACION_H

#include "tipos.h"

/*
 * TDA tPuntuacion - Sistema de puntuacion estilo NES Tetris.
 *
 * El nivel del scoring sube cada 10 lineas eliminadas.
 * El multiplicador del puntaje se aplica con el nivel PREVIO a la
 * actualizacion (asi funciona el NES original).
 *
 * IMPORTANTE: este 'nivel' es solo del scoring. NO confundir con la
 * velocidad de caida, que segun el TP debe variar por cantidad de
 * piezas caidas (eso vive en dificultad.c, no aca).
 */

typedef struct
{
    int puntaje;
    int lineas;
    int nivel;
} tPuntuacion;

/* Resetea la puntuacion a cero. Precondicion: p != NULL. */
void puntuacion_iniciar(tPuntuacion *p);

/*
 * Suma el puntaje correspondiente a eliminar 'cant_lineas' lineas
 * de una vez, segun la tabla NES:
 *   1 (single)  =   40 * (nivel + 1)
 *   2 (double)  =  100 * (nivel + 1)
 *   3 (triple)  =  300 * (nivel + 1)
 *   4 (tetris)  = 1200 * (nivel + 1)
 *
 * Tambien actualiza el contador total de lineas y el nivel.
 * Si cant_lineas esta fuera de [1..4], la funcion no hace nada
 * (caso defensivo, no deberia ocurrir si el llamador es correcto).
 */
void puntuacion_sumar_lineas(tPuntuacion *p, int cant_lineas);

/*
 * Suma puntos por bajar manualmente la pieza (soft drop):
 * 1 punto por casillero. Llamar UNA vez por celda que la pieza
 * cae por accion del jugador, no por gravedad.
 */
void puntuacion_sumar_soft_drop(tPuntuacion *p, int celdas);

#endif /* PUNTUACION_H */
