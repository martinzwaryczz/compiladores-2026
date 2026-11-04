#ifndef MATRIZ_ACCIONES_H
#define MATRIZ_ACCIONES_H

#include "matriz_estados.h"

typedef enum {
    ACT_FN = 0, /* f_nada */
    ACT_F1 = 1, /* f_acumular_id */
    ACT_F2 = 2, /* f_fin_id */
    ACT_F3 = 3, /* f_acumular_num */
    ACT_F4 = 4, /* f_fin_num */
    ACT_F5 = 5, /* f_acumular_op */
    ACT_F6 = 6, /* f_contar_linea */
    ACT_F7 = 7, /* f_inicio_coment */
    ACT_F8 = 8, /* f_fin_coment */
    ACT_FE = 9  /* f_error_lexico */
} CodigoAccionSemantica;

static const int matriz_acciones[CANT_ESTADOS][CANT_EVENTOS] = {
    /* LET,    DIG,      =,      +,      -,      *,      /,      <,      >,      !,      (,      ),      {,      },      ;,      :,      .,     BL,    FDA,    OTR */
    { ACT_F1, ACT_F3, ACT_F5, ACT_F5, ACT_F5, ACT_F5, ACT_F5, ACT_F5, ACT_F5, ACT_F5, ACT_F5, ACT_F5, ACT_F5, ACT_F5, ACT_F5, ACT_F5, ACT_FE, ACT_F6, ACT_FN, ACT_FE }, /* E0: estado inicial */
    { ACT_F1, ACT_F1, ACT_F2, ACT_F2, ACT_F2, ACT_F2, ACT_F2, ACT_F2, ACT_F2, ACT_F2, ACT_F2, ACT_F2, ACT_F2, ACT_F2, ACT_F2, ACT_F2, ACT_F2, ACT_F2, ACT_F2, ACT_F2 }, /* E1: palabra */
    { ACT_F4, ACT_F3, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F3, ACT_F4, ACT_F4, ACT_F4 }, /* E2: entero */
    { ACT_F4, ACT_F3, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4, ACT_F4 }, /* E3: real */
    { ACT_FN, ACT_FN, ACT_F5, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN }, /* E4: asigancion (=) */
    { ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN }, /* E5: suma (+) */
    { ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN }, /* E6: resta (-) */
    { ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN }, /* E7: multiplicación (*) */
    { ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_F7, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN }, /* E8: división (/) */
    { ACT_FN, ACT_FN, ACT_F5, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN }, /* E9: menor (< ) */
    { ACT_FN, ACT_FN, ACT_F5, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN }, /* E10: mayor (>) */
    { ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN }, /* E11: menor o igual (<=) */
    { ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN }, /* E12: mayor o igual (>=) */
    { ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN }, /* E13: igualdad (==) */
    { ACT_FE, ACT_FE, ACT_F5, ACT_FE, ACT_FE, ACT_FE, ACT_FE, ACT_FE, ACT_FE, ACT_FE, ACT_FE, ACT_FE, ACT_FE, ACT_FE, ACT_FE, ACT_FE, ACT_FE, ACT_FE, ACT_FE, ACT_FE }, /* E14: posible distinto */
    { ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN }, /* E15: distinto ( !=) */
    { ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN }, /* E16: abre paréntesis */
    { ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN }, /* E17: cierra paréntesis */
    { ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN }, /* E18: llave apertura */
    { ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN }, /* E19: llave cierre */
    { ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN }, /* E20: fin sentencia (;) */
    { ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN }, /* E21: separador (:) */
    { ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_F6, ACT_FE, ACT_FN }, /* E22: comentario (/* ) */
    { ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_F8, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_FN, ACT_F6, ACT_FE, ACT_FN }  /* E23: posible fin comentario */
};

#endif /* MATRIZ_ACCIONES_H */
