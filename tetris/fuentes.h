#ifndef FUENTES_H_INCLUDED
#define FUENTES_H_INCLUDED

#include <stdint.h>

#include "records.h"
typedef struct
{
    uint8_t pixel[128][8];
    uint8_t ancho[128];
    uint8_t alto;
}tFuente;

void fuente_inicializar(tFuente * fuente);
void dibujar_pixel_escala(int x, int y, int escala, uint8_t color);
void fuente_dibujar_caracter(int x, int y, char c, uint8_t color, int escala, const tFuente *fuente);
void fuente_dibujar_texto(int x, int y, const char *texto, uint8_t color, int escala, const tFuente *fuente);

#endif // FUENTES_H_INCLUDED
