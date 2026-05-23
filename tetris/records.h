#ifndef RECORDS_H
#define RECORDS_H

#include "tipos.h"

#define MAX_RECORDS 5
#define MAX_NOMBRE  8   /* sin contar el null terminator */

/* Registro individual de high score. */
typedef struct
{
    char nombre[MAX_NOMBRE + 1];  /* +1 para el '\0' */
    int  puntaje;
    int  lineas;
    int  nivel;
} tRecord;

/*
 * TDA tRecords - Top MAX_RECORDS ordenado descendente por puntaje.
 *
 * Array estatico (sin heap): tamanio fijo conocido en compilacion,
 * sin riesgo de leaks. Si en el futuro se necesita tope variable,
 * se reemplaza por el TDA Vector sin tocar la interfaz publica.
 */
typedef struct
{
    tRecord lista[MAX_RECORDS];
    int     cant;  /* 0 <= cant <= MAX_RECORDS */
} tRecords;

/* Deja la lista en estado valido y vacio. */
void records_iniciar(tRecords *r);

/*
 * Lee records desde un archivo binario.
 *
 * Devuelve:
 *   0 si cargo OK,
 *   1 si hubo error (archivo inexistente, corrupto o truncado).
 *
 * En cualquier caso, el TDA queda en un estado valido: si algo falla,
 * la lista queda vacia (cant=0). Esto permite usar la misma funcion
 * en la primera ejecucion del juego, cuando aun no existe el archivo.
 */
int records_cargar(tRecords *r, const char *ruta);

/*
 * Persiste los records en un archivo binario. Sobreescribe.
 * Devuelve 0 si OK, 1 si error.
 */
int records_guardar(const tRecords *r, const char *ruta);

/*
 * Devuelve 1 si 'puntaje' entraria al ranking, 0 si no.
 * Util para preguntar el nombre del jugador SOLO cuando va a entrar.
 *
 * Criterio: si la lista no esta llena, cualquier puntaje entra.
 * Si esta llena, debe ser ESTRICTAMENTE mayor al ultimo.
 */
int records_es_top(const tRecords *r, int puntaje);

/*
 * Inserta un nuevo record manteniendo el orden descendente.
 * Si la lista esta llena y el puntaje no entra, no hace nada.
 * Si esta llena pero entra, desplaza al de menor puntaje.
 */
void records_agregar(tRecords *r, const tRecord *nuevo);

#endif /* RECORDS_H */
