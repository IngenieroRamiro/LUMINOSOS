#include "dificultad.h"

#define PIEZAS_AUMENTAR 3
#define VELOCIDAD_AUMENTAR 0.1f
#define MAX_VELOCIDAD 0.7

void actualizar_velocidad(float* velocidad_actual, int p_caidas, tGBT_Temporizador **reloj_caida)
{
    if(p_caidas % PIEZAS_AUMENTAR == 0)
    {
        if(*velocidad_actual > MAX_VELOCIDAD)
        {
            *velocidad_actual = *velocidad_actual * (1 - VELOCIDAD_AUMENTAR);
            if(*velocidad_actual < MAX_VELOCIDAD)
                *velocidad_actual = MAX_VELOCIDAD;
            gbt_temporizador_destruir(*reloj_caida);
            *reloj_caida = gbt_temporizador_crear(*velocidad_actual);
        }
    }
}
