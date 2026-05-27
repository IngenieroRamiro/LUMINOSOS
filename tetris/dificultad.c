#include "dificultad.h"
#include "tipos.h"

void actualizar_velocidad(float* velocidad_actual, int p_caidas, tGBT_Temporizador **reloj_caida, int v_inicial, int estado)
{
    static int ult_p_caidas = 0;

    float velocidad_inicial_config = 1; // por defecto NORMAL
    if (v_inicial == VELOCIDAD_NIVEL_LENTA)
    {
        velocidad_inicial_config = 1.3;
    } else if (v_inicial == VELOCIDAD_NIVEL_RAPIDA)
    {
        velocidad_inicial_config = 0.6;
    }

    if(!estado && (p_caidas % PIEZAS_AUMENTAR == 0)) // estado = 0 -> aumentar velocidad
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

    if(estado == 1) // estado = 1 -> pierde, reiniciar velocidad
    {
        *velocidad_actual = velocidad_inicial_config;
        gbt_temporizador_destruir(*reloj_caida);
        ult_p_caidas = 0;
        *reloj_caida = gbt_temporizador_crear(*velocidad_actual);
    }

    if((estado == 2) && (p_caidas - ult_p_caidas) >= PIEZAS_REDUCIR) // estado = 2 -> reducir velocidad (tecla e) cada 10 piezas caídas
    {
        *velocidad_actual = *velocidad_actual * 1.1;
        if(*velocidad_actual > velocidad_inicial_config)
                *velocidad_actual = velocidad_inicial_config;

        gbt_temporizador_destruir(*reloj_caida);
        *reloj_caida = gbt_temporizador_crear(*velocidad_actual);

        ult_p_caidas = p_caidas;
    }
}
