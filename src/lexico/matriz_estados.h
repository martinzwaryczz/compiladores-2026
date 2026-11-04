#ifndef MATRIZ_ESTADOS_H
#define MATRIZ_ESTADOS_H

#define CANT_ESTADOS 24
#define CANT_EVENTOS 20

typedef enum {
    EST_INICIAL               = 0,
    EST_PALABRA               = 1,
    EST_ENTERO                = 2,
    EST_REAL                  = 3,
    EST_ASIGNACION            = 4,
    EST_SUMA                  = 5,
    EST_RESTA                 = 6,
    EST_MULTIPLICACION        = 7,
    EST_DIVISION              = 8,
    EST_MENOR                 = 9,
    EST_MAYOR                 = 10,
    EST_MENOR_IGUAL           = 11,
    EST_MAYOR_IGUAL           = 12,
    EST_IGUALDAD              = 13,
    EST_POSIBLE_DISTINTO      = 14,
    EST_DISTINTO              = 15,
    EST_ABRE_PAREN            = 16,
    EST_CIERRA_PAREN          = 17,
    EST_ABRE_LLAVE            = 18,
    EST_CIERRA_LLAVE          = 19,
    EST_FIN_SENTENCIA         = 20,
    EST_SEPARADOR             = 21,
    EST_COMENTARIO            = 22,
    EST_POSIBLE_FIN_COMENTARIO= 23,
    EST_FINAL                 = -1
} EstadoLexico;

typedef enum {
    EV_LETRA        = 0,
    EV_DIGITO       = 1,
    EV_IGUAL        = 2,
    EV_MAS          = 3,
    EV_MENOS        = 4,
    EV_POR          = 5,
    EV_BARRA        = 6,
    EV_MENOR        = 7,
    EV_MAYOR        = 8,
    EV_ADMIRACION   = 9,
    EV_ABRE_PAREN   = 10,
    EV_CIERRA_PAREN = 11,
    EV_ABRE_LLAVE   = 12,
    EV_CIERRA_LLAVE = 13,
    EV_PUNTO_COMA   = 14,
    EV_DOS_PUNTOS   = 15,
    EV_PUNTO        = 16,
    EV_BLANCO       = 17,
    EV_FDA          = 18,
    EV_OTRO         = 19
} EventoLexico;

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
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E12: mayor o igual (>=) */
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
