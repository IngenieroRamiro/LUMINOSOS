#ifndef PUNTUACION_H
#define PUNTUACION_H

#include "tipos.h"


typedef struct
{
    int puntaje;
    int lineas;
    int nivel;
} tPuntuacion;

void puntuacion_iniciar(tPuntuacion *p);


void puntuacion_sumar_lineas(tPuntuacion *p, int cant_lineas);


void puntuacion_sumar_soft_drop(tPuntuacion *p, int celdas);

#endif /* PUNTUACION_H */
