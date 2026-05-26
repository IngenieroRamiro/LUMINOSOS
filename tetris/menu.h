#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "fuentes.h"

void Pantalla_Inicio (tFuente *fuente,int *juego);
void Pausar_Juego (tFuente *fuente, int *juego);
void Game_over(tFuente *fuente, int *juego);
void Pantalla_Ingresar_Nombre(tFuente *fuente, char *destino, int max_chars);
void Pantalla_Records(tFuente *fuente, const tRecords *records);
#endif // MENU_H_INCLUDED
