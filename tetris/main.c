#include <stdio.h>

#include "GBT/gbt.h"
#include "fuentes.h"

int main()
{
    tFuente fuente;

    if (gbt_iniciar() != 0)
    {
        printf("Error iniciando GBT\n");
        return 1;
    }

    if (gbt_crear_ventana("Ejemplo Fuente",320,240,3) != 0)
    {
        printf("Error al crearr ventana\n");
        gbt_cerrar();
        return 1;
    }

    fuente_inicializar(&fuente);

    while (!gbt_tecla_sostenida(GBTK_ESCAPE))
    {

        gbt_procesar_entrada();

        gbt_borrar_backbuffer(0);

        fuente_dibujar_texto(100,100,"0123456789",15,&fuente);

        gbt_volcar_backbuffer();

        gbt_esperar(16);
    }

    gbt_destruir_ventana();

    gbt_cerrar();

    return 0;
}
