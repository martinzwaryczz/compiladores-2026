#ifndef MATRIZ_ESTADOS_H
#define MATRIZ_ESTADOS_H

#define ESTADOS 24
#define COLUMNAS 20
#define EF -1

static const int matriz_estados[ESTADOS][COLUMNAS] = {
    /*           0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 */
    /*           Let    Dig    =    +    -    *    /    <    >    !    (    )    {    }    ;    :    .   BL  FDA OTRO */
    /* 0: E0  */ {  1,   2,   4,   5,   6,   7,   8,   9,  10,  14,  16,  17,  18,  19,  20,  21,  EF,    0,  EF,   EF }, /* E0: estado inicial */
    /* 1: E1  */ {  1,   1,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E1: palabra */
    /* 2: E2  */ { EF,   2,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   3,   EF,  EF,   EF }, /* E2: entero */
    /* 3: E3  */ { EF,   3,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E3: real */
    /* 4: E4  */ { EF,  EF,  13,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E4: asigancion (=) */
    /* 5: E5  */ { EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E5: suma (+) */
    /* 6: E6  */ { EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E6: resta (-) */ 
    /* 7: E7  */ { EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E7: multiplicación (*) */
    /* 8: E8  */ { EF,  EF,  EF,  EF,  EF,  22,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E8: división (/) */
    /* 9: E9  */ { EF,  EF,  11,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E9: menor (< ) */
    /* 10: E10*/ { EF,  EF,  12,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E10: mayor (>) */
    /* 11: E11*/ { EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E11: menor o igual (<=) */
    /* 12: E12*/ { EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E12: mayor o igual (>=) */
    /* 13: E13*/ { EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E13: igualdad (==) */
    /* 14: E14*/ { EF,  EF,  15,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E14: posible distinto */
    /* 15: E15*/ { EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E15: distinto ( !=) */
    /* 16: E16*/ { EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E16: abre paréntesis */
    /* 17: E17*/ { EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E17: cierra paréntesis */
    /* 18: E18*/ { EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E18: llave apertura */
    /* 19: E19*/ { EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E19: llave cierre */
    /* 20: E20*/ { EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E20: fin sentencia (;) */
    /* 21: E21*/ { EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,  EF,   EF,  EF,   EF }, /* E21: separador (:) */
    /* 22: E22*/ { 22,  22,  22,  22,  22,  23,  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,   22,  EF,   22 }, /* E22: comentario (/* ) */
    /* 23: E23*/ { 22,  22,  22,  22,  22,  23,   0,  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,   22,  EF,   22 }  /* E23: posible fin comentario */
};

#endif


static const int nuevo_estado[CANT_ESTADOS][CANT_EVENTOS] = {
    /* LET, DIG,   =,   +,   -,   *,   /,   <,   >,   !,   (,   ),   {,   },   ;,   :,   .,  BL, FDA, OTR */
    {    1,   2,   4,   5,   6,   7,   8,   9,  10,  14,  16,  17,  18,  19,  20,  21,  -1,   0,  -1,   0 }, /* E0: estado inicial */
    {    1,   1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E1: palabra */
    {   -1,   2,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   3,  -1,  -1,  -1 }, /* E2: entero */
    {   -1,   3,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E3: real */
    {   -1,  -1,  13,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E4: asigancion (=) */
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E5: suma (+) */
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E6: resta (-) */
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E7: multiplicación (*) */
    {   -1,  -1,  -1,  -1,  -1,  22,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E8: división (/) */
    {   -1,  -1,  11,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E9: menor (< ) */
    {   -1,  -1,  12,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E10: mayor (>) */
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E11: menor o igual (<=) */
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E13: igualdad (==) */
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E13: igualdad (==) */
    {   -1,  -1,  15,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E14: posible distinto */
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E15: distinto ( !=) */
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E16: abre paréntesis */
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E17: cierra paréntesis */
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E18: llave apertura */
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E19: llave cierre */
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E20: fin sentencia (;) */
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E21: separador (:) */
    {   22,  22,  22,  22,  22,  23,  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,  -1,  22 }, /* E22: comentario (/* ) */
    {   22,  22,  22,  22,  22,  23,   0,  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,  22,  -1,  22 }  /* E23: posible fin comentario */
};

#endif /* MATRIZ_ESTADOS_H */
