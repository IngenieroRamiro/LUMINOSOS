/*
 * test_puntuacion.c
 *
 * Lote de prueba para los modulos puntuacion y records.
 * Compila standalone:
 *   gcc -Wall -Wextra -pedantic -std=c11 \
 *       puntuacion.c records.c test_puntuacion.c -o test_puntuacion.exe
 *
 * Casos cubiertos:
 *  Puntuacion:
 *   - Estado inicial.
 *   - Single/double/triple/tetris en nivel 0.
 *   - Multiplicador correcto con nivel > 0.
 *   - Subida de nivel a mitad de jugada (que el tetris se cobre
 *     con el nivel previo, no el nuevo).
 *   - Inputs invalidos (0, 5, negativos).
 *   - Soft drop simple, cero, negativo.
 *   - Saturacion en INT_MAX sin overflow.
 *  Records:
 *   - Lista vacia.
 *   - Insercion mantiene orden descendente.
 *   - Lista llena: nuevo mayor desplaza, nuevo menor no entra.
 *   - records_es_top en los limites.
 *   - Persistencia ida y vuelta (guardar -> cargar).
 *   - Carga de archivo inexistente deja lista vacia.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "puntuacion.h"
#include "records.h"

static int tests_pasados = 0;
static int tests_totales = 0;

#define VERIFICAR(cond, descripcion) do {                    \
    tests_totales++;                                         \
    if (cond) {                                              \
        tests_pasados++;                                     \
        printf("  OK    %s\n", (descripcion));               \
    } else {                                                 \
        printf("  FALLO %s\n", (descripcion));               \
    }                                                        \
} while (0)

/* ---------- Tests de puntuacion ---------- */

static void test_puntuacion_inicial(void)
{
    tPuntuacion p;
    puntuacion_iniciar(&p);

    printf("test_puntuacion_inicial:\n");
    VERIFICAR(p.puntaje == 0, "puntaje inicial 0");
    VERIFICAR(p.lineas  == 0, "lineas iniciales 0");
    VERIFICAR(p.nivel   == 0, "nivel inicial 0");
}

static void test_puntuacion_NES_nivel0(void)
{
    tPuntuacion p;
    printf("test_puntuacion_NES_nivel0:\n");

    puntuacion_iniciar(&p);
    puntuacion_sumar_lineas(&p, 1);
    VERIFICAR(p.puntaje == 40,   "single nivel 0 = 40");

    puntuacion_iniciar(&p);
    puntuacion_sumar_lineas(&p, 2);
    VERIFICAR(p.puntaje == 100,  "double nivel 0 = 100");

    puntuacion_iniciar(&p);
    puntuacion_sumar_lineas(&p, 3);
    VERIFICAR(p.puntaje == 300,  "triple nivel 0 = 300");

    puntuacion_iniciar(&p);
    puntuacion_sumar_lineas(&p, 4);
    VERIFICAR(p.puntaje == 1200, "tetris nivel 0 = 1200");
}

static void test_puntuacion_NES_nivel_mayor(void)
{
    tPuntuacion p;
    printf("test_puntuacion_NES_nivel_mayor:\n");

    puntuacion_iniciar(&p);
    p.nivel = 1;
    puntuacion_sumar_lineas(&p, 1);
    VERIFICAR(p.puntaje == 80, "single nivel 1 = 80");

    puntuacion_iniciar(&p);
    p.nivel = 9;
    puntuacion_sumar_lineas(&p, 4);
    VERIFICAR(p.puntaje == 12000, "tetris nivel 9 = 12000");
}

static void test_puntuacion_subida_nivel(void)
{
    tPuntuacion p;
    int puntaje_antes;

    printf("test_puntuacion_subida_nivel:\n");

    /* Llevo el contador a 8 lineas con singles, pero seteo el puntaje
       a 0 a mano para que el assert del tetris sea limpio. */
    puntuacion_iniciar(&p);
    p.lineas = 8;
    p.nivel  = 0;
    p.puntaje = 0;

    puntaje_antes = p.puntaje;
    puntuacion_sumar_lineas(&p, 4);  /* tetris en nivel 0: 1200 puntos */

    VERIFICAR(p.lineas == 12, "12 lineas totales");
    VERIFICAR(p.nivel == 1,   "nivel paso a 1");
    VERIFICAR(p.puntaje - puntaje_antes == 1200,
              "el tetris se cobra con nivel previo (0), no con el nuevo");
}

static void test_puntuacion_invalidos(void)
{
    tPuntuacion p;
    printf("test_puntuacion_invalidos:\n");

    puntuacion_iniciar(&p);
    puntuacion_sumar_lineas(&p, 0);
    VERIFICAR(p.puntaje == 0 && p.lineas == 0, "cant_lineas=0 no hace nada");

    puntuacion_sumar_lineas(&p, 5);
    VERIFICAR(p.puntaje == 0 && p.lineas == 0, "cant_lineas=5 no hace nada");

    puntuacion_sumar_lineas(&p, -1);
    VERIFICAR(p.puntaje == 0 && p.lineas == 0, "cant_lineas=-1 no hace nada");
}

static void test_puntuacion_soft_drop(void)
{
    tPuntuacion p;
    printf("test_puntuacion_soft_drop:\n");

    puntuacion_iniciar(&p);
    puntuacion_sumar_soft_drop(&p, 5);
    VERIFICAR(p.puntaje == 5,  "soft drop 5 celdas = +5 puntos");

    puntuacion_sumar_soft_drop(&p, 0);
    VERIFICAR(p.puntaje == 5,  "soft drop 0 no suma");

    puntuacion_sumar_soft_drop(&p, -3);
    VERIFICAR(p.puntaje == 5,  "soft drop negativo no suma");
}

static void test_puntuacion_saturacion(void)
{
    tPuntuacion p;
    printf("test_puntuacion_saturacion:\n");

    puntuacion_iniciar(&p);
    p.puntaje = INT_MAX - 10;
    puntuacion_sumar_soft_drop(&p, 50);
    VERIFICAR(p.puntaje == INT_MAX, "satura en INT_MAX, sin overflow");
}

/* ---------- Tests de records ---------- */

static tRecord crear_record(const char *nombre, int puntaje)
{
    tRecord r;
    memset(&r, 0, sizeof(r));  /* zera padding -> binarios estables */
    strncpy(r.nombre, nombre, MAX_NOMBRE);
    r.nombre[MAX_NOMBRE] = '\0';
    r.puntaje = puntaje;
    r.lineas  = 0;
    r.nivel   = 0;
    return r;
}

static void test_records_vacio(void)
{
    tRecords r;
    printf("test_records_vacio:\n");
    records_iniciar(&r);
    VERIFICAR(r.cant == 0, "records inicia con cant 0");
    VERIFICAR(records_es_top(&r, 1), "cualquier puntaje es top si esta vacio");
}

static void test_records_agregar_orden(void)
{
    tRecords r;
    tRecord r1, r2, r3;

    printf("test_records_agregar_orden:\n");
    records_iniciar(&r);

    r1 = crear_record("ANA",   500);
    r2 = crear_record("BETO", 1000);
    r3 = crear_record("CECI",  750);

    records_agregar(&r, &r1);
    records_agregar(&r, &r2);
    records_agregar(&r, &r3);

    VERIFICAR(r.cant == 3,                "se agregaron 3 records");
    VERIFICAR(r.lista[0].puntaje == 1000, "primero es el mayor (1000)");
    VERIFICAR(r.lista[1].puntaje == 750,  "segundo es 750");
    VERIFICAR(r.lista[2].puntaje == 500,  "tercero es 500");
}

static void test_records_llena_y_desplaza(void)
{
    tRecords r;
    tRecord nuevo;
    int i;

    printf("test_records_llena_y_desplaza:\n");
    records_iniciar(&r);

    /* Lleno con 100, 200, 300, 400, 500 */
    for (i = 0; i < 5; i++)
    {
        tRecord aux = crear_record("JUG", 100 * (i + 1));
        records_agregar(&r, &aux);
    }

    VERIFICAR(r.cant == 5,                "lista llena con 5");
    VERIFICAR(r.lista[0].puntaje == 500,  "tope = 500");
    VERIFICAR(r.lista[4].puntaje == 100,  "ultimo = 100");

    /* 350 entra y desplaza al 100 */
    nuevo = crear_record("NEW", 350);
    records_agregar(&r, &nuevo);

    VERIFICAR(r.cant == 5,                "sigue siendo 5 (no crecio)");
    VERIFICAR(r.lista[0].puntaje == 500,  "tope intacto");
    VERIFICAR(r.lista[2].puntaje == 350,  "nuevo quedo en posicion 3");
    VERIFICAR(r.lista[4].puntaje == 200,  "ultimo ahora es 200");

    /* 50 NO entra */
    nuevo = crear_record("LOW", 50);
    records_agregar(&r, &nuevo);

    VERIFICAR(r.lista[4].puntaje == 200,  "puntaje bajo no afecta el ranking");
}

static void test_records_es_top(void)
{
    tRecords r;
    int i;

    printf("test_records_es_top:\n");
    records_iniciar(&r);

    for (i = 0; i < 5; i++)
    {
        tRecord aux = crear_record("X", 100 * (i + 1));
        records_agregar(&r, &aux);
    }

    VERIFICAR(records_es_top(&r, 600) == 1, "600 es top");
    VERIFICAR(records_es_top(&r, 150) == 1, "150 es top (mayor que el ultimo 100)");
    VERIFICAR(records_es_top(&r, 100) == 0, "100 NO es top (igual al ultimo)");
    VERIFICAR(records_es_top(&r,  50) == 0, "50 NO es top");
}

static void test_records_persistencia(void)
{
    tRecords r1, r2;
    const char *ruta = "test_records_tmp.dat";
    int i;

    printf("test_records_persistencia:\n");

    records_iniciar(&r1);
    for (i = 0; i < 3; i++)
    {
        tRecord aux = crear_record("PER", 1000 - i * 100);  /* 1000, 900, 800 */
        records_agregar(&r1, &aux);
    }

    VERIFICAR(records_guardar(&r1, ruta) == 0, "guardar OK");

    records_iniciar(&r2);
    VERIFICAR(records_cargar(&r2, ruta) == 0, "cargar OK");
    VERIFICAR(r2.cant == 3,                   "cargado con 3 records");
    VERIFICAR(r2.lista[0].puntaje == 1000,    "primer puntaje preservado");
    VERIFICAR(strcmp(r2.lista[0].nombre, "PER") == 0, "nombre preservado");

    remove(ruta);  /* limpieza */
}

static void test_records_archivo_inexistente(void)
{
    tRecords r;
    tRecord aux;
    int ret;

    printf("test_records_archivo_inexistente:\n");
    records_iniciar(&r);

    aux = crear_record("BAS", 999);
    records_agregar(&r, &aux);  /* lo cargo para verificar que cargar lo pise */

    ret = records_cargar(&r, "no_existe_seguro_xyz.dat");
    VERIFICAR(ret == 1,    "cargar archivo inexistente devuelve 1");
    VERIFICAR(r.cant == 0, "la lista queda vacia tras intento fallido");
}

int main(void)
{
    printf("=== Lote de prueba puntuacion ===\n");
    test_puntuacion_inicial();
    test_puntuacion_NES_nivel0();
    test_puntuacion_NES_nivel_mayor();
    test_puntuacion_subida_nivel();
    test_puntuacion_invalidos();
    test_puntuacion_soft_drop();
    test_puntuacion_saturacion();

    printf("\n=== Lote de prueba records ===\n");
    test_records_vacio();
    test_records_agregar_orden();
    test_records_llena_y_desplaza();
    test_records_es_top();
    test_records_persistencia();
    test_records_archivo_inexistente();

    printf("\nResultado: %d/%d tests pasados\n",
           tests_pasados, tests_totales);
    return (tests_pasados == tests_totales) ? 0 : 1;
}
