#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>
#include "fuentes.h"
#include "tipos.h"
#include "puntuacion.h"
#include "tablero.h"
#include "piezas.h"

void dibujar_tablero(const tTablero* t, const tPieza* pieza);
void dibujar_forma(int x, int y, int ancho, int alto, int c1, int c2, int c3);
void dibujar_fondo(tFuente *fuente);
void dibujar_hud(const tPuntuacion *p, const tFuente *fuente);

#endif //RENDER_H



/// ////////////////////// ///
/// ARQUITECTURA ANTERIOR ///

/*

#ifndef RENDER_H
#define RENDER_H

#include <stdint.h>
#include "fuentes.h"
#include "tipos.h"
#include "puntuacion.h"

void dibujar_tablero(uint8_t mat[FILAS][COLS]);
void dibujar_forma(int x, int y, int ancho, int alto, int c1, int c2, int c3);
void dibujar_fondo(tFuente *fuente);
void dibujar_hud(const tPuntuacion *p, const tFuente *fuente);

#endif RENDER_H */
