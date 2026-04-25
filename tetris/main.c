#include <stdio.h>
#include <stdint.h>
#include "GBT/gbt.h"

// Dimensiones del tablero de Tetris
#define FILAS 20
#define COLS 10
#define TAM_BLOQUE 15  // Tamaño en píxeles de cada cuadradito



int main()
{
    if (gbt_iniciar() < 0)
    {
        printf("ERROR AL INICIOAR LKA BIBLIOTECA GBT %s",gbt_obtener_log());
        return 1;
    }

    if(gbt_crear_ventana("Tetris UNLaM - Miguel", 200, 300, 2) < 0)
    {
        printf("ERROR AL CREAR LA VENTANA %s",gbt_obtener_log());
        return 1;
    }


    uint8_t Tablero [FILAS][COLS] = {0};

    int juego_corriendo = 1;

    while(juego_corriendo)
    {
        // 1. IMPORTANTE: Procesar eventos (teclado, mouse, ventana)
        gbt_procesar_entrada();

        // 2. Dibujar el píxel (esto va a la memoria invisible)
        gbt_dibujar_pixel(100, 150, 5);

        // 3. ¡ESTA ES LA QUE FALTA! Pasa el dibujo a la pantalla real
        gbt_volcar_backbuffer();

        // 4. Un pequeño respiro para el procesador
        gbt_esperar(16);
    }


}
