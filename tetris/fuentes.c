#include <string.h>
#include <stdint.h>
#include <ctype.h>

#include "GBT/gbt.h"
#include "fuentes.h"

void fuente_inicializar(tFuente *fuente)
{
    memset(fuente,0,sizeof(*fuente));

    fuente->alto=8;

    // Espacio

    fuente->ancho[' ']=4;

    // Letra 'A'

    fuente->pixel['A'][0] = 0b00111100;
    fuente->pixel['A'][1] = 0b01000010;
    fuente->pixel['A'][2] = 0b01000010;
    fuente->pixel['A'][3] = 0b01111110;
    fuente->pixel['A'][4] = 0b01000010;
    fuente->pixel['A'][5] = 0b01000010;
    fuente->pixel['A'][6] = 0b01000010;
    fuente->pixel['A'][7] = 0b00000000;

    fuente->ancho['A']=8;

    // Letra 'B'

    fuente->pixel['B'][0] = 0b01111100;
    fuente->pixel['B'][1] = 0b01000010;
    fuente->pixel['B'][2] = 0b01000010;
    fuente->pixel['B'][3] = 0b01111100;
    fuente->pixel['B'][4] = 0b01000010;
    fuente->pixel['B'][5] = 0b01000010;
    fuente->pixel['B'][6] = 0b01111100;
    fuente->pixel['B'][7] = 0b00000000;

    fuente->ancho['B']=8;

    // Letra 'C'

    fuente->pixel['C'][0] = 0b00111100;
    fuente->pixel['C'][1] = 0b01000010;
    fuente->pixel['C'][2] = 0b01000000;
    fuente->pixel['C'][3] = 0b01000000;
    fuente->pixel['C'][4] = 0b01000000;
    fuente->pixel['C'][5] = 0b01000010;
    fuente->pixel['C'][6] = 0b00111100;
    fuente->pixel['C'][7] = 0b00000000;

    fuente->ancho['C']=8;

    // Letra 'D'

    fuente->pixel['D'][0] = 0b01111000;
    fuente->pixel['D'][1] = 0b01000100;
    fuente->pixel['D'][2] = 0b01000100;
    fuente->pixel['D'][3] = 0b01000100;
    fuente->pixel['D'][4] = 0b01000100;
    fuente->pixel['D'][5] = 0b01000100;
    fuente->pixel['D'][6] = 0b01111000;
    fuente->pixel['D'][7] = 0b00000000;

    fuente->ancho['D']=7;

    // Letra 'E'

    fuente->pixel['E'][0] = 0b01111100;
    fuente->pixel['E'][1] = 0b01000000;
    fuente->pixel['E'][2] = 0b01000000;
    fuente->pixel['E'][3] = 0b01111000;
    fuente->pixel['E'][4] = 0b01000000;
    fuente->pixel['E'][5] = 0b01000000;
    fuente->pixel['E'][6] = 0b01111100;
    fuente->pixel['E'][7] = 0b00000000;

    fuente->ancho['E']=7;

    // Letra 'F'

    fuente->pixel['F'][0] = 0b01111100;
    fuente->pixel['F'][1] = 0b01000000;
    fuente->pixel['F'][2] = 0b01000000;
    fuente->pixel['F'][3] = 0b01111000;
    fuente->pixel['F'][4] = 0b01000000;
    fuente->pixel['F'][5] = 0b01000000;
    fuente->pixel['F'][6] = 0b01000000;
    fuente->pixel['F'][7] = 0b00000000;

    fuente->ancho['F']=7;

    // Letra 'G'

    fuente->pixel['G'][0] = 0b00111100;
    fuente->pixel['G'][1] = 0b01000010;
    fuente->pixel['G'][2] = 0b01000000;
    fuente->pixel['G'][3] = 0b01001110;
    fuente->pixel['G'][4] = 0b01000010;
    fuente->pixel['G'][5] = 0b01000010;
    fuente->pixel['G'][6] = 0b00111100;
    fuente->pixel['G'][7] = 0b00000000;

    fuente->ancho['G']=8;

    // Letra 'H'

    fuente->pixel['H'][0] = 0b01000010;
    fuente->pixel['H'][1] = 0b01000010;
    fuente->pixel['H'][2] = 0b01000010;
    fuente->pixel['H'][3] = 0b01111110;
    fuente->pixel['H'][4] = 0b01000010;
    fuente->pixel['H'][5] = 0b01000010;
    fuente->pixel['H'][6] = 0b01000010;
    fuente->pixel['H'][7] = 0b00000000;

    fuente->ancho['H']=8;

    // Letra 'I'

    fuente->pixel['I'][0] = 0b01110000;
    fuente->pixel['I'][1] = 0b00100000;
    fuente->pixel['I'][2] = 0b00100000;
    fuente->pixel['I'][3] = 0b00100000;
    fuente->pixel['I'][4] = 0b00100000;
    fuente->pixel['I'][5] = 0b00100000;
    fuente->pixel['I'][6] = 0b01110000;
    fuente->pixel['I'][7] = 0b00000000;

    fuente->ancho['I']=5;

    // Letra 'J'

    fuente->pixel['J'][0] = 0b00111110;
    fuente->pixel['J'][1] = 0b00001000;
    fuente->pixel['J'][2] = 0b00001000;
    fuente->pixel['J'][3] = 0b00001000;
    fuente->pixel['J'][4] = 0b00001000;
    fuente->pixel['J'][5] = 0b01001000;
    fuente->pixel['J'][6] = 0b00110000;
    fuente->pixel['J'][7] = 0b00000000;

    fuente->ancho['J']=8;

    // Letra 'K'

    fuente->pixel['K'][0] = 0b01000100;
    fuente->pixel['K'][1] = 0b01000100;
    fuente->pixel['K'][2] = 0b01001000;
    fuente->pixel['K'][3] = 0b01110000;
    fuente->pixel['K'][4] = 0b01001000;
    fuente->pixel['K'][5] = 0b01000100;
    fuente->pixel['K'][6] = 0b01000100;
    fuente->pixel['K'][7] = 0b00000000;

    fuente->ancho['K']=7;

    // Letra 'L'

    fuente->pixel['L'][0] = 0b01000000;
    fuente->pixel['L'][1] = 0b01000000;
    fuente->pixel['L'][2] = 0b01000000;
    fuente->pixel['L'][3] = 0b01000000;
    fuente->pixel['L'][4] = 0b01000000;
    fuente->pixel['L'][5] = 0b01000000;
    fuente->pixel['L'][6] = 0b01111000;
    fuente->pixel['L'][7] = 0b00000000;

    fuente->ancho['L']=6;

    // Letra 'M'

    fuente->pixel['M'][0] = 0b01000010;
    fuente->pixel['M'][1] = 0b01100110;
    fuente->pixel['M'][2] = 0b01011010;
    fuente->pixel['M'][3] = 0b01000010;
    fuente->pixel['M'][4] = 0b01000010;
    fuente->pixel['M'][5] = 0b01000010;
    fuente->pixel['M'][6] = 0b01000010;
    fuente->pixel['M'][7] = 0b00000000;

    fuente->ancho['M']=8;

    // Letra 'N'

    fuente->pixel['N'][0] = 0b01000010;
    fuente->pixel['N'][1] = 0b01100010;
    fuente->pixel['N'][2] = 0b01010010;
    fuente->pixel['N'][3] = 0b01001010;
    fuente->pixel['N'][4] = 0b01000110;
    fuente->pixel['N'][5] = 0b01000010;
    fuente->pixel['N'][6] = 0b01000010;
    fuente->pixel['N'][7] = 0b00000000;

    fuente->ancho['N']=8;

    // Letra 'O'

    fuente->pixel['O'][0] = 0b00111100;
    fuente->pixel['O'][1] = 0b01000010;
    fuente->pixel['O'][2] = 0b01000010;
    fuente->pixel['O'][3] = 0b01000010;
    fuente->pixel['O'][4] = 0b01000010;
    fuente->pixel['O'][5] = 0b01000010;
    fuente->pixel['O'][6] = 0b00111100;
    fuente->pixel['O'][7] = 0b00000000;

    fuente->ancho['O']=8;

    // Letra 'P'

    fuente->pixel['P'][0] = 0b01111000;
    fuente->pixel['P'][1] = 0b01000100;
    fuente->pixel['P'][2] = 0b01000100;
    fuente->pixel['P'][3] = 0b01111000;
    fuente->pixel['P'][4] = 0b01000000;
    fuente->pixel['P'][5] = 0b01000000;
    fuente->pixel['P'][6] = 0b01000000;
    fuente->pixel['P'][7] = 0b00000000;

    fuente->ancho['P']=7;

    // Letra 'Q'

    fuente->pixel['Q'][0] = 0b00111100;
    fuente->pixel['Q'][1] = 0b01000010;
    fuente->pixel['Q'][2] = 0b01000010;
    fuente->pixel['Q'][3] = 0b01000010;
    fuente->pixel['Q'][4] = 0b01001010;
    fuente->pixel['Q'][5] = 0b01000100;
    fuente->pixel['Q'][6] = 0b00111010;
    fuente->pixel['Q'][7] = 0b00000000;

    fuente->ancho['Q']=8;

    // Letra 'R'

    fuente->pixel['R'][0] = 0b01111000;
    fuente->pixel['R'][1] = 0b01000100;
    fuente->pixel['R'][2] = 0b01000100;
    fuente->pixel['R'][3] = 0b01111000;
    fuente->pixel['R'][4] = 0b01001000;
    fuente->pixel['R'][5] = 0b01000100;
    fuente->pixel['R'][6] = 0b01000100;
    fuente->pixel['R'][7] = 0b00000000;

    fuente->ancho['R']=7;

    // Letra 'S'

    fuente->pixel['S'][0] = 0b00111100;
    fuente->pixel['S'][1] = 0b01000010;
    fuente->pixel['S'][2] = 0b01000000;
    fuente->pixel['S'][3] = 0b00111100;
    fuente->pixel['S'][4] = 0b00000010;
    fuente->pixel['S'][5] = 0b01000010;
    fuente->pixel['S'][6] = 0b00111100;
    fuente->pixel['S'][7] = 0b00000000;

    fuente->ancho['S']=8;

    // Letra 'T'

    fuente->pixel['T'][0] = 0b01111100;
    fuente->pixel['T'][1] = 0b00010000;
    fuente->pixel['T'][2] = 0b00010000;
    fuente->pixel['T'][3] = 0b00010000;
    fuente->pixel['T'][4] = 0b00010000;
    fuente->pixel['T'][5] = 0b00010000;
    fuente->pixel['T'][6] = 0b00010000;
    fuente->pixel['T'][7] = 0b00000000;

    fuente->ancho['T']=7;

    // Letra 'U'

    fuente->pixel['U'][0] = 0b01000010;
    fuente->pixel['U'][1] = 0b01000010;
    fuente->pixel['U'][2] = 0b01000010;
    fuente->pixel['U'][3] = 0b01000010;
    fuente->pixel['U'][4] = 0b01000010;
    fuente->pixel['U'][5] = 0b01000010;
    fuente->pixel['U'][6] = 0b00111100;
    fuente->pixel['U'][7] = 0b00000000;

    fuente->ancho['U']=8;

    // Letra 'V'

    fuente->pixel['V'][0] = 0b01000010;
    fuente->pixel['V'][1] = 0b01000010;
    fuente->pixel['V'][2] = 0b01000010;
    fuente->pixel['V'][3] = 0b01000010;
    fuente->pixel['V'][4] = 0b01000010;
    fuente->pixel['V'][5] = 0b00100100;
    fuente->pixel['V'][6] = 0b00011000;
    fuente->pixel['V'][7] = 0b00000000;

    fuente->ancho['V']=8;

    // Letra 'W'

    fuente->pixel['W'][0] = 0b01000010;
    fuente->pixel['W'][1] = 0b01000010;
    fuente->pixel['W'][2] = 0b01000010;
    fuente->pixel['W'][3] = 0b01011010;
    fuente->pixel['W'][4] = 0b01011010;
    fuente->pixel['W'][5] = 0b01100110;
    fuente->pixel['W'][6] = 0b01000010;
    fuente->pixel['W'][7] = 0b00000000;

    fuente->ancho['W']=8;

    // Letra 'X'

    fuente->pixel['X'][0] = 0b01000010;
    fuente->pixel['X'][1] = 0b01000010;
    fuente->pixel['X'][2] = 0b00100100;
    fuente->pixel['X'][3] = 0b00011000;
    fuente->pixel['X'][4] = 0b00100100;
    fuente->pixel['X'][5] = 0b01000010;
    fuente->pixel['X'][6] = 0b01000010;
    fuente->pixel['X'][7] = 0b00000000;

    fuente->ancho['X']=8;

    // Letra 'Y'

    fuente->pixel['Y'][0] = 0b01000100;
    fuente->pixel['Y'][1] = 0b01000100;
    fuente->pixel['Y'][2] = 0b00111000;
    fuente->pixel['Y'][3] = 0b00010000;
    fuente->pixel['Y'][4] = 0b00010000;
    fuente->pixel['Y'][5] = 0b00010000;
    fuente->pixel['Y'][6] = 0b00010000;
    fuente->pixel['Y'][7] = 0b00000000;

    fuente->ancho['Y']=7;

    // Letra 'Z'

    fuente->pixel['Z'][0] = 0b01111100;
    fuente->pixel['Z'][1] = 0b00000100;
    fuente->pixel['Z'][2] = 0b00001000;
    fuente->pixel['Z'][3] = 0b00010000;
    fuente->pixel['Z'][4] = 0b00100000;
    fuente->pixel['Z'][5] = 0b01000000;
    fuente->pixel['Z'][6] = 0b01111100;
    fuente->pixel['Z'][7] = 0b00000000;

    fuente->ancho['Z']=7;

    for(int i = 0; i < 128; i++)
    {
        if(fuente->ancho[i] == 0)
        {
            fuente->pixel[i][0] = 0b00000000;
            fuente->pixel[i][1] = 0b00000000;
            fuente->pixel[i][2] = 0b00111100;
            fuente->pixel[i][3] = 0b00100100;
            fuente->pixel[i][4] = 0b00100100;
            fuente->pixel[i][5] = 0b00111100;
            fuente->pixel[i][6] = 0b00000000;
            fuente->pixel[i][7] = 0b00000000;

            fuente->ancho[i] = 7;
        }

    }
}

void fuente_dibujar_caracter(int x, int y, char c, uint8_t color, const tFuente *fuente)
{
    c=toupper(c);

    for(int fila = 0; fila < fuente->alto ; fila++)
    {
        for(int col = 0; col < fuente->ancho[(int)c]; col++)
        {
            uint8_t mascara = 1 << (7 - col);
            if(fuente->pixel[(int)c][fila] & mascara)
            {
                gbt_dibujar_pixel(x + col, y + fila, color);
            }
        }
    }
}

void fuente_dibujar_texto(int x, int y, const char *texto, uint8_t color, const tFuente *fuente)
{
    int i = 0;

    while (texto[i] != '\0')
    {
        fuente_dibujar_caracter(x, y, texto[i], color, fuente);

        x += fuente->ancho[(int)toupper(texto[i])];

        i++;
    }
}
