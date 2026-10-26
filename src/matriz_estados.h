#ifndef MATRIZ_ESTADOS_H
#define MATRIZ_ESTADOS_H

#ifndef ESTADOS
#define ESTADOS 24
#endif

#ifndef COLUMNAS
#define COLUMNAS 19
#endif

#define EF -1

/* Columnas (eventos) del automata. get_evento() devuelve uno de estos valores.
   Columnas 0 a 16: ver cabecera de la matriz. */
#define COL_LETRA        0  /* DENTRO DE COMENTARIOS */
#define COL_BLANCO      17   /* espacio, tabulacion, salto de linea, retorno de carro */
#define COL_FDA         18   /* fin de archivo */

static int matriz_estados[ESTADOS][COLUMNAS] = {
    /*           Let    Dig    =    +    -    *    /    <    >    !    (    )    {    }    ;    :    .  BLANCO FDA */
    /* 0: E0  */ {  1,    2,   4,   5,   6,   7,   8,   9,  10,  14,  16,  17,  18,  19,  20,  21,  EF,    0,  EF },
    /* 1: E1  */ {  1,    1,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 2: E2  */ { EF,    2,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   3,   EF,  EF },
    /* 3: E3  */ { EF,    3,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 4: E4  */ { EF,   EF,  13,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 5: E5  */ { EF,   EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 6: E6  */ { EF,   EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 7: E7  */ { EF,   EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 8: E8  */ { EF,   EF,  EF,  EF,  EF,  22,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 9: E9  */ { EF,   EF,  11,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 10: E10*/ { EF,   EF,  12,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 11: E11*/ { EF,   EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 12: E12*/ { EF,   EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 13: E13*/ { EF,   EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 14: E14*/ { EF,   EF,  15,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 15: E15*/ { EF,   EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 16: E16*/ { EF,   EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 17: E17*/ { EF,   EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 18: E18*/ { EF,   EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 19: E19*/ { EF,   EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 20: E20*/ { EF,   EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 21: E21*/ { EF,   EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF },
    /* 22: E23 */{ 22,   22,  22,  22,  22,  23,  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,   22,  EF }, /* (comienzo de comentario) */
    /* 23: E24*/ { 22,   22,  22,  22,  22,  23,   0,  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,   22,  EF } /* (posible fin de comentario) */
};

#endif
