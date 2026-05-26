#include "dificultad.h"
#include "tipos.h"


void actualizar_velocidad(float* velocidad_actual, int p_caidas, tGBT_Temporizador **reloj_caida, int pierde)
{
    if((p_caidas % PIEZAS_AUMENTAR == 0) && !pierde)
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
    if(pierde)
    {
        *velocidad_actual = VELOCIDAD_INICIAL;
        gbt_temporizador_destruir(*reloj_caida);
        *reloj_caida = gbt_temporizador_crear(*velocidad_actual);
    }
}
