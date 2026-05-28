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
#define MAX_VELOCIDAD 0.2f
#define PIEZAS_REDUCIR 10

#define FONDO_TAB 1
#define COLOR_FONDO_1      10
#define COLOR_FONDO_2      11
#define COLOR_FONDO_3      12
#define COLOR_TEXTO        20
#define COLOR_BLOQUE_FIJO  30
#define COLOR_SELECCION    31
#define COLOR_BORDE_MINO   40


#define COLOR_PIEZA_I      50
#define COLOR_PIEZA_J      51
#define COLOR_PIEZA_L      52
#define COLOR_PIEZA_O      53
#define COLOR_PIEZA_S      54
#define COLOR_PIEZA_Z      55
#define COLOR_PIEZA_T      56

typedef struct {
    int paleta_color;
    int resolucion_logica;
    int velocidad_caida;
    int columnas_deluxe;
} tConfiguracion;

typedef enum {
    VELOCIDAD_NIVEL_LENTA  = 0,
    VELOCIDAD_NIVEL_NORMAL = 1,
    VELOCIDAD_NIVEL_RAPIDA = 2
} eVelocidadNivel;

#endif // TIPOS_H
