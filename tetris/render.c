#include "render.h"
#include <stdio.h>
#include "GBT/gbt.h"

void dibujar_tablero(const tTablero* t, const tPieza* pieza)
{
    int pos_x = (TAM_VENTANA_X / 2) - (t->columnas * TAM_MINO)/2;
    int pos_y = 100;

    for (int f = 2; f < t->filas; f++)
    {
        for (int c = 0; c < t->columnas; c++)
        {
            int valor = t->celdas[f][c];

            for (int i = 0; i < pieza->cant_bloques; i++)
            {
                if ((pieza->bloques[i].f == f) && (pieza->bloques[i].c == c))
                    valor = pieza->color;
            }

            int px = pos_x + c * TAM_MINO;
            int py = pos_y + (f - 2) * TAM_MINO;

            int borde = COLOR_BORDE_MINO;

            for (int i = 0; i < TAM_MINO; i++)
            {
                for (int j = 0; j < TAM_MINO; j++)
                    gbt_dibujar_pixel(px + i, py + j, borde);
            }

            int centro = (valor == 0) ? FONDO_TAB : ((valor == 2) ? COLOR_BLOQUE_FIJO : valor);

            for (int i = 1; i < TAM_MINO - 1; i++)
            {
                for (int j = 1; j < TAM_MINO - 1; j++)
                    gbt_dibujar_pixel(px + i, py + j, centro);
            }
        }
    }
}

void dibujar_forma(int x, int y, int ancho, int alto, int c1, int c2, int c3)
{
    for (int i = 0; i < ancho; i++)
        for (int j = 0; j < alto; j++)
            gbt_dibujar_pixel(x + i, y + j, c1);

    for (int i = 15; i < ancho - 15; i++)
        for (int j = 15; j < alto - 15; j++)
            gbt_dibujar_pixel(x + i, y + j, c2);

    for (int i = 30; i < ancho - 30; i++)
        for (int j = 30; j < alto - 30; j++)
            gbt_dibujar_pixel(x + i, y + j, c3);
}

void dibujar_fondo(tFuente *fuente)
{
    int y = 0;
    int x = 0;

    for(int f = 0; f < 6; f++)
    {
        x = 0;
        for(int c = 0; c < 8; c++)
        {
            dibujar_forma(x, y, 80, 80, COLOR_FONDO_1, COLOR_FONDO_2, COLOR_FONDO_3);
            x += 80;
        }
        y += 80;
    }

    fuente_dibujar_texto(TAM_VENTANA_X/2 - 61, 70, "tetris", COLOR_TEXTO, 3, fuente);
}

void dibujar_hud(const tPuntuacion *p, const tFuente *fuente, float velocidad)
{
    char buffer[16];

    const int x = 440;
    const int y_base = 118;

    int inicio_tablero = (TAM_VENTANA_X / 2) - (COLS_NORMAL * TAM_MINO) / 2;

    dibujar_forma(inicio_tablero + (COLS_NORMAL * TAM_MINO) + 40, 95, 115, 170, COLOR_FONDO_2, COLOR_FONDO_1, COLOR_FONDO_1);

    fuente_dibujar_texto(x, y_base, "PUNTAJE", COLOR_FONDO_3, 1, fuente);
    snprintf(buffer, sizeof(buffer), "%d", p->puntaje);
    fuente_dibujar_texto(x, y_base + 12, buffer, 0, 1, fuente);

    fuente_dibujar_texto(x, y_base + 36, "LINEAS", COLOR_FONDO_3, 1, fuente);
    snprintf(buffer, sizeof(buffer), "%d", p->lineas);
    fuente_dibujar_texto(x, y_base + 48, buffer, 0, 1, fuente);

    fuente_dibujar_texto(x, y_base + 72, "NIVEL", COLOR_FONDO_3, 1, fuente);
    snprintf(buffer, sizeof(buffer), "%d", p->nivel);
    fuente_dibujar_texto(x, y_base + 84, buffer, 0, 1, fuente);

    fuente_dibujar_texto(x, y_base + 108, "VELOCIDAD", COLOR_FONDO_3, 1, fuente);
    snprintf(buffer, sizeof(buffer), "%.2fs", velocidad);
    fuente_dibujar_texto(x, y_base + 120, buffer, 0, 1, fuente);
}

void inicializar_paleta_gbt(int n_paleta)
{
    tGBT_ColorRGB paleta[PALETA_MAX_COLORES];

    for(int i = 0; i < PALETA_MAX_COLORES; i++)
        paleta[i] = (tGBT_ColorRGB){0, 0, 0};

    paleta[FONDO_TAB] = (tGBT_ColorRGB){55, 65, 85};

    if (n_paleta == 0) // CLÁSICA
    {
        paleta[COLOR_FONDO_1]     = (tGBT_ColorRGB){60, 90, 170};
        paleta[COLOR_FONDO_2]     = (tGBT_ColorRGB){0, 0, 120};
        paleta[COLOR_FONDO_3]     = (tGBT_ColorRGB){120, 170, 190};
        paleta[COLOR_TEXTO]       = (tGBT_ColorRGB){255, 255, 255};
        paleta[COLOR_SELECCION]   = (tGBT_ColorRGB){255, 255, 255};
        paleta[COLOR_BLOQUE_FIJO] = (tGBT_ColorRGB){150, 150, 150};
        paleta[COLOR_BORDE_MINO]  = (tGBT_ColorRGB){70, 70, 80};

        paleta[COLOR_PIEZA_I]     = (tGBT_ColorRGB){0, 230, 230};
        paleta[COLOR_PIEZA_J]     = (tGBT_ColorRGB){0, 0, 230};
        paleta[COLOR_PIEZA_L]     = (tGBT_ColorRGB){230, 130, 0};
        paleta[COLOR_PIEZA_O]     = (tGBT_ColorRGB){230, 230, 0};
        paleta[COLOR_PIEZA_S]     = (tGBT_ColorRGB){0, 230, 0};
        paleta[COLOR_PIEZA_Z]     = (tGBT_ColorRGB){230, 0, 0};
        paleta[COLOR_PIEZA_T]     = (tGBT_ColorRGB){150, 0, 230};

    }
    else if (n_paleta == 1) // LUMINOSA
    {
        paleta[COLOR_FONDO_1]     = (tGBT_ColorRGB){80, 140, 255};
        paleta[COLOR_FONDO_2]     = (tGBT_ColorRGB){170, 110, 255};
        paleta[COLOR_FONDO_3]     = (tGBT_ColorRGB){225, 235, 250};
        paleta[COLOR_TEXTO]       = (tGBT_ColorRGB){255, 255, 255};
        paleta[COLOR_SELECCION]   = (tGBT_ColorRGB){255, 180, 210};
        paleta[COLOR_BLOQUE_FIJO] = (tGBT_ColorRGB){130, 160, 190};
        paleta[COLOR_BORDE_MINO]  = (tGBT_ColorRGB){170, 110, 255};

        paleta[COLOR_PIEZA_I]     = (tGBT_ColorRGB){150, 210, 230};
        paleta[COLOR_PIEZA_J]     = (tGBT_ColorRGB){160, 180, 240};
        paleta[COLOR_PIEZA_L]     = (tGBT_ColorRGB){240, 180, 150};
        paleta[COLOR_PIEZA_O]     = (tGBT_ColorRGB){240, 220, 160};
        paleta[COLOR_PIEZA_S]     = (tGBT_ColorRGB){160, 220, 170};
        paleta[COLOR_PIEZA_Z]     = (tGBT_ColorRGB){230, 160, 160};
        paleta[COLOR_PIEZA_T]     = (tGBT_ColorRGB){210, 170, 230};
    }
    else // NEÓN
    {
        paleta[COLOR_FONDO_1]     = (tGBT_ColorRGB){15, 5, 30};
        paleta[COLOR_FONDO_2]     = (tGBT_ColorRGB){5, 2, 15};
        paleta[COLOR_FONDO_3]     = (tGBT_ColorRGB){30, 10, 50};
        paleta[COLOR_TEXTO]       = (tGBT_ColorRGB){0, 255, 255};
        paleta[COLOR_SELECCION]   = (tGBT_ColorRGB){120, 255, 80};
        paleta[COLOR_BLOQUE_FIJO] = (tGBT_ColorRGB){255, 0, 128};
        paleta[COLOR_BORDE_MINO]  = (tGBT_ColorRGB){60, 0, 110};

        paleta[COLOR_PIEZA_I]     = (tGBT_ColorRGB){0, 255, 220};
        paleta[COLOR_PIEZA_J]     = (tGBT_ColorRGB){0, 120, 255};
        paleta[COLOR_PIEZA_L]     = (tGBT_ColorRGB){255, 150, 0};
        paleta[COLOR_PIEZA_O]     = (tGBT_ColorRGB){255, 255, 0};
        paleta[COLOR_PIEZA_S]     = (tGBT_ColorRGB){50, 255, 50};
        paleta[COLOR_PIEZA_Z]     = (tGBT_ColorRGB){255, 0, 70};
        paleta[COLOR_PIEZA_T]     = (tGBT_ColorRGB){230, 0, 255};
    }

    gbt_aplicar_paleta(paleta, PALETA_MAX_COLORES, GBT_FORMATO_888);
}
