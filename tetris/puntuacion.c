#include "puntuacion.h"
#include <limits.h>

#define LINEAS_POR_NIVEL 10

/* Tabla NES: puntos base segun cantidad de lineas eliminadas a la vez.
   El indice 0 nunca se usa (no hay puntaje por 0 lineas). */
static const int PUNTOS_POR_LINEAS[5] = { 0, 40, 100, 300, 1200 };

/*
 * Suma a y b saturando en INT_MAX. Evita UB por overflow signed,
 * que con -Wall -Wextra -pedantic seria un dolor de cabeza.
 */
static int sumar_saturado(int a, int b)
{
    if (b > 0 && a > INT_MAX - b)
        return INT_MAX;
    return a + b;
}

void puntuacion_iniciar(tPuntuacion *p)
{
    p->puntaje = 0;
    p->lineas  = 0;
    p->nivel   = 0;
}

void puntuacion_sumar_lineas(tPuntuacion *p, int cant_lineas)
{
    int incremento;

    if (cant_lineas < 1 || cant_lineas > 4)
        return;

    /* El multiplicador usa el nivel ANTES de actualizar las lineas. */
    incremento = PUNTOS_POR_LINEAS[cant_lineas] * (p->nivel + 1);
    p->puntaje = sumar_saturado(p->puntaje, incremento);

    p->lineas += cant_lineas;
    p->nivel = p->lineas / LINEAS_POR_NIVEL;
}

void puntuacion_sumar_soft_drop(tPuntuacion *p, int celdas)
{
    if (celdas > 0)
        p->puntaje = sumar_saturado(p->puntaje, celdas);
}
