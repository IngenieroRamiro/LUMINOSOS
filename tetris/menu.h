#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "fuentes.h"
#include "tipos.h"

void Pantalla_Inicio(tFuente *fuente, int *juego, tConfiguracion* config);
void Pausar_Juego(tFuente *fuente, int *juego);
void Game_over(tFuente *fuente, int *juego);
void Pantalla_Configuracion(tFuente *fuente, int *juego, tConfiguracion* config);

#endif
