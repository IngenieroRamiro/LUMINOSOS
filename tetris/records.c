#include "records.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    memset(r->lista, 0, sizeof(r->lista));
}

int records_cargar(tRecords *r, const char *ruta)
{
    FILE *f;
    int   cant_leida;
    size_t leidos;

    records_iniciar(r);

    f = fopen(ruta, "rb");
    if (f == NULL)
        return 1;

    if (fread(&cant_leida, sizeof(int), 1, f) != 1)
    {
        fclose(f);
        return 1;
    }

    if (cant_leida < 0 || cant_leida > MAX_RECORDS)
    {
        fclose(f);
        return 1;
    }

    leidos = fread(r->lista, sizeof(tRecord), (size_t)cant_leida, f);
    fclose(f);

    if (leidos != (size_t)cant_leida)
    {
        records_iniciar(r);
        return 1;
    }

    r->cant = cant_leida;

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
        r->lista[MAX_RECORDS - 1] = *nuevo;
    }

    r->lista[r->cant - 1].nombre[MAX_NOMBRE] = '\0';

    qsort(r->lista, (size_t)r->cant, sizeof(tRecord), cmp_record_desc);
}
