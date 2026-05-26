#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>
#include "fuentes.h"
#include "tipos.h"
#include "puntuacion.h"      /* nuevo */

void dibujar_tablero(uint8_t mat[FILAS][COLS]);
void dibujar_forma(int x, int y, int ancho, int alto);
void dibujar_fondo(tFuente *fuente);
void dibujar_hud(const tPuntuacion *p, const tFuente *fuente);   /* nuevo */

#endif /* RENDER_H */
