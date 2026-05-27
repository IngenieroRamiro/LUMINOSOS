#include "puntuacion.h"
#include <limits.h>

#define LINEAS_POR_NIVEL 10

static int puntos_base_nes(int cant_lineas)
{
    switch (cant_lineas)
    {
        case 1: return 40;    /* single */
        case 2: return 100;   /* double */
        case 3: return 300;   /* triple */
        case 4: return 1200;  /* tetris */
        default: return 0;
    }
}


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

    incremento = puntos_base_nes(cant_lineas) * (p->nivel + 1);
    p->puntaje = sumar_saturado(p->puntaje, incremento);

    p->lineas += cant_lineas;
    p->nivel = p->lineas / LINEAS_POR_NIVEL;
}

void puntuacion_sumar_soft_drop(tPuntuacion *p, int celdas)
{
    if (celdas > 0)
        p->puntaje = sumar_saturado(p->puntaje, celdas);
}
