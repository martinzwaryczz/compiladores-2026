#ifndef MATRIZ_ACCIONES_H
#define MATRIZ_ACCIONES_H

#include "matriz_estados.h"
/* Declaración de las acciones semánticas según spec.md */
int fn(char c); /* f_nada */
int fe(char c); /* f_error_lexico */
int f1(char c); /* f_acumular_id */
int f2(char c); /* f_fin_id */
int f3(char c); /* f_acumular_num */
int f4(char c); /* f_fin_num */
int f5(char c); /* f_acumular_op */
int f6(char c); /* f_contar_linea */
int f7(char c); /* f_inicio_coment */
int f8(char c); /* f_fin_coment */

static const int matriz_acciones[CANT_ESTADOS][CANT_EVENTOS] = {
    /*           0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19 */
    /*           L    D    =    +    -    *    /    <    >    !    (    )    {    }    ;    :    .   BL  FDA OTRO */
    /* 0: E0  */ { f1,  f3,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  fe,   f6,  fn,  fe }, /* E0: estado inicial */
    /* 1: E1  */ { f1,  f1,  f2,  f2,  f2,  f2,  f2,  f2,  f2,  f2,  f2,  f2,  f2,  f2,  f2,  f2,  f2,   f2,  f2,  f2 }, /* E1: palabra */
    /* 2: E2  */ { f4,  f3,  f4,  f4,  f4,  f4,  f4,  f4,  f4,  f4,  f4,  f4,  f4,  f4,  f4,  f4,  f3,   f4,  f4,  f4 }, /* E2: entero */
    /* 3: E3  */ { f4,  f3,  f4,  f4,  f4,  f4,  f4,  f4,  f4,  f4,  f4,  f4,  f4,  f4,  f4,  f4,  f4,   f4,  f4,  f4 }, /* E3: real */
    /* 4: E4  */ { fn,  fn,  f5,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   fn,  fn,  fn }, /* E4: asigancion (=) */
    /* 5: E5  */ { fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   fn,  fn,  fn }, /* E5: suma (+) */
    /* 6: E6  */ { fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   fn,  fn,  fn }, /* E6: resta (-) */
    /* 7: E7  */ { fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   fn,  fn,  fn }, /* E7: multiplicación (*) */
    /* 8: E8  */ { fn,  fn,  fn,  fn,  fn,  f7,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   fn,  fn,  fn }, /* E8: división (/) */
    /* 9: E9  */ { fn,  fn,  f5,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   fn,  fn,  fn }, /* E9: menor (< ) */
    /* 10: E10*/ { fn,  fn,  f5,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   fn,  fn,  fn }, /* E10: mayor (>) */
    /* 11: E11*/ { fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   fn,  fn,  fn }, /* E11: menor o igual (<=) */
    /* 12: E12*/ { fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   fn,  fn,  fn }, /* E12: mayor o igual (>=) */
    /* 13: E13*/ { fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   fn,  fn,  fn }, /* E13: igualdad (==) */
    /* 14: E14*/ { fe,  fe,  f5,  fe,  fe,  fe,  fe,  fe,  fe,  fe,  fe,  fe,  fe,  fe,  fe,  fe,  fe,   fe,  fe,  fe }, /* E14: posible distinto */
    /* 15: E15*/ { fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   fn,  fn,  fn }, /* E15: distinto ( !=) */
    /* 16: E16*/ { fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   fn,  fn,  fn }, /* E16: abre paréntesis */
    /* 17: E17*/ { fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   fn,  fn,  fn }, /* E17: cierra paréntesis */
    /* 18: E18*/ { fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   fn,  fn,  fn }, /* E18: llave apertura */
    /* 19: E19*/ { fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   fn,  fn,  fn }, /* E19: llave cierre */
    /* 20: E20*/ { fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   fn,  fn,  fn }, /* E20: fin sentencia (;) */
    /* 21: E21*/ { fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   fn,  fn,  fn }, /* E21: separador (:) */
    /* 22: E22*/ { fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   f6,  fe,  fn }, /* E22: comentario (/* ) */
    /* 23: E23*/ { fn,  fn,  fn,  fn,  fn,  fn,  f8,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   f6,  fe,  fn }  /* E23: posible fin comentario */
};
   
#endif /* MATRIZ_ACCIONES_H */
