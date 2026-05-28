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
void dibujar_hud(const tPuntuacion *p, const tFuente *fuente, float velocidad);
void inicializar_paleta_gbt(int n_paleta);

#endif //RENDER_H
