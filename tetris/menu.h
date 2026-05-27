#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "fuentes.h"
<<<<<<< Updated upstream

void Pantalla_Inicio (tFuente *fuente,int *juego);
void Pausar_Juego (tFuente *fuente, int *juego);
void Game_over(tFuente *fuente, int *juego);
void Pantalla_Ingresar_Nombre(tFuente *fuente, char *destino, int max_chars);
void Pantalla_Records(tFuente *fuente, const tRecords *records);
#endif // MENU_H_INCLUDED
=======
#include "tipos.h"
#include "tablero.h"
#include "piezas.h"
#include "puntuacion.h"

void Pantalla_Inicio(tFuente *fuente, int *juego, tConfiguracion* config);
void Pausar_Juego(tFuente *fuente, int *juego, const tTablero* t, const tPieza* p, const tPuntuacion* punt, float velocidad, int caidas);
void Game_over(tFuente *fuente, int *juego, const tPuntuacion *punt);
void Pantalla_Configuracion(tFuente *fuente, int *juego, tConfiguracion* config);
void Pantalla_Records(tFuente *fuente, int *juego);
void Pantalla_Ingresar_Nombre(tFuente *fuente, char *nombre_out);

#endif
>>>>>>> Stashed changes
