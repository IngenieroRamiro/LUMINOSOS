#ifndef TIPOS_H
#define TIPOS_H

#include <stdint.h>

#define TAM_VENTANA_X   640
#define TAM_VENTANA_Y   480

#define FILAS 22
#define COLS_MAX 16
#define COLS_NORMAL 10
#define TAM_MINO 12

#define PIEZAS_NORMAL 7
#define PIEZAS_DELUXE 11
#define MAX_BLOQUES 5

#define PIEZAS_AUMENTAR 3
#define VELOCIDAD_AUMENTAR 0.1f
#define MAX_VELOCIDAD 0.7
#define VELOCIDAD_INICIAL 1.0f
#define PIEZAS_REDUCIR 10

typedef struct {
    int paleta_color;
    int resolucion_logica;
    int velocidad_caida;
    int columnas_deluxe;
} tConfiguracion;

#endif // TIPOS_H
