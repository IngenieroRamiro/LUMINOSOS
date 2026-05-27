#ifndef RECORDS_H
#define RECORDS_H

#include "tipos.h"

#define MAX_RECORDS 5
#define MAX_NOMBRE  8

<<<<<<< Updated upstream
=======
#define RUTA_ESTADISTICAS "estadisticas.dat"
>>>>>>> Stashed changes

typedef struct
{
    char nombre[MAX_NOMBRE + 1];
    int  puntaje;
    int  lineas;
    int  nivel;
} tRecord;


typedef struct
{
    tRecord lista[MAX_RECORDS];
    int     cant;
} tRecords;


void records_iniciar(tRecords *r);

int records_cargar(tRecords *r, const char *ruta);


int records_guardar(const tRecords *r, const char *ruta);


int records_es_top(const tRecords *r, int puntaje);

void records_agregar(tRecords *r, const tRecord *nuevo);

#endif /* RECORDS_H */
