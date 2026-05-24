#include "records.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Comparador estilo qsort: ordena descendente por puntaje.
 * Puntero a funcion, consigna de Unidad 3.
 */
static int cmp_record_desc(const void *a, const void *b)
{
    const tRecord *ra = (const tRecord *)a;
    const tRecord *rb = (const tRecord *)b;

    if (ra->puntaje > rb->puntaje) return -1;
    if (ra->puntaje < rb->puntaje) return 1;
    return 0;
}

void records_iniciar(tRecords *r)
{
    r->cant = 0;
    /* memset por higiene: aunque cant=0 hace los slots inaccesibles,
       dejar bytes basura puede confundir al debuggear. */
    memset(r->lista, 0, sizeof(r->lista));
}

int records_cargar(tRecords *r, const char *ruta)
{
    FILE *f;
    int   cant_leida;
    size_t leidos;

    records_iniciar(r);  /* Estado valido pase lo que pase */

    f = fopen(ruta, "rb");
    if (f == NULL)
        return 1;  /* Primera ejecucion: no hay archivo, sin drama */

    if (fread(&cant_leida, sizeof(int), 1, f) != 1)
    {
        fclose(f);
        return 1;
    }

    /* Validacion: si el archivo esta corrupto, no confiamos. */
    if (cant_leida < 0 || cant_leida > MAX_RECORDS)
    {
        fclose(f);
        return 1;
    }

    leidos = fread(r->lista, sizeof(tRecord), (size_t)cant_leida, f);
    fclose(f);

    if (leidos != (size_t)cant_leida)
    {
        /* Archivo truncado: descartamos lo leido a medias */
        records_iniciar(r);
        return 1;
    }

    r->cant = cant_leida;

    /* Defensivo: aseguramos null terminator en cada nombre.
       Si el archivo viene de una version anterior o fue tocado a mano,
       evita que un printf() lea memoria mas alla del buffer. */
    for (tRecord *p = r->lista; p < r->lista + r->cant; p++)
        p->nombre[MAX_NOMBRE] = '\0';

    return 0;
}

int records_guardar(const tRecords *r, const char *ruta)
{
    FILE *f;

    f = fopen(ruta, "wb");
    if (f == NULL)
        return 1;

    if (fwrite(&r->cant, sizeof(int), 1, f) != 1)
    {
        fclose(f);
        return 1;
    }

    if (r->cant > 0)
    {
        if (fwrite(r->lista, sizeof(tRecord), (size_t)r->cant, f)
                != (size_t)r->cant)
        {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

int records_es_top(const tRecords *r, int puntaje)
{
    if (r->cant < MAX_RECORDS)
        return 1;

    /* Lista llena: el de menor puntaje esta al final (orden desc). */
    return puntaje > r->lista[MAX_RECORDS - 1].puntaje;
}

void records_agregar(tRecords *r, const tRecord *nuevo)
{
    if (!records_es_top(r, nuevo->puntaje))
        return;

    if (r->cant < MAX_RECORDS)
    {
        r->lista[r->cant] = *nuevo;
        r->cant++;
    }
    else
    {
        /* Lista llena: reemplazamos al ultimo (el de menor puntaje). */
        r->lista[MAX_RECORDS - 1] = *nuevo;
    }

    /* Defensivo: por si el llamador no termino el nombre en '\0'. */
    r->lista[r->cant - 1].nombre[MAX_NOMBRE] = '\0';

    /* qsort con puntero a funcion: cmp_record_desc. */
    qsort(r->lista, (size_t)r->cant, sizeof(tRecord), cmp_record_desc);
}
