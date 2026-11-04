#ifndef MATRIZ_TOKENS_H
#define MATRIZ_TOKENS_H

#include "matriz_estados.h"

/* Definiciones canónicas de Tokens según especificación de DUOTIPO */
#define TK_INT         301
#define TK_REAL        302
#define TK_FUNCTION    303
#define TK_MAIN        304
#define TK_RETURN      305
#define TK_SWITCH      306
#define TK_CASE        307
#define TK_DEFAULT     308
#define TK_WHILE       309
#define TK_TOINT       310
#define TK_TOREAL      311
#define TK_AND         312
#define TK_OR          313
#define TK_ID          314
#define TK_NUM_INT     315
#define TK_NUM_REAL    316
#define TK_ASSIGN      317
#define TK_PLUS        318
#define TK_MINUS       319
#define TK_MULT        320
#define TK_DIV         321
#define TK_LT          322
#define TK_GT          323
#define TK_LE          324
#define TK_GE          325
#define TK_EQ          326
#define TK_NEQ         327
#define TK_LPAREN      328
#define TK_RPAREN      329
#define TK_LBRACE      330
#define TK_RBRACE      331
#define TK_SEMI        332
#define TK_COLON       334
#define TK_ESCR        335
#define TK_OTRO        337

/*
 * Matriz de Tokens:
 * Retorna el token asociado al alcanzar el estado final de aceptación (-1).
 * -1 = No emite token (transición interna o descartable)
 * 0  = Fin de archivo (YYEOF)
 */
static const int matriz_tokens[CANT_ESTADOS][CANT_EVENTOS] = {
    /* LET, DIG,   =,   +,   -,   *,   /,   <,   >,   !,   (,   ),   {,   },   ;,   :,   .,  BL, FDA, OTR */
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,   0,  -1 }, /* E0: estado inicial */
    {   -1,  -1, 314, 314, 314, 314, 314, 314, 314, 314, 314, 314, 314, 314, 314, 314, 314, 314, 314, 314 }, /* E1: palabra */
    {  315,  -1, 315, 315, 315, 315, 315, 315, 315, 315, 315, 315, 315, 315, 315, 315,  -1, 315, 315, 315 }, /* E2: entero */
    {  316,  -1, 316, 316, 316, 316, 316, 316, 316, 316, 316, 316, 316, 316, 316, 316, 316, 316, 316, 316 }, /* E3: real */
    {  317, 317,  -1, 317, 317, 317, 317, 317, 317, 317, 317, 317, 317, 317, 317, 317, 317, 317, 317, 317 }, /* E4: asigancion (=) */
    {  318, 318, 318, 318, 318, 318, 318, 318, 318, 318, 318, 318, 318, 318, 318, 318, 318, 318, 318, 318 }, /* E5: suma (+) */
    {  319, 319, 319, 319, 319, 319, 319, 319, 319, 319, 319, 319, 319, 319, 319, 319, 319, 319, 319, 319 }, /* E6: resta (-) */
    {  320, 320, 320, 320, 320, 320, 320, 320, 320, 320, 320, 320, 320, 320, 320, 320, 320, 320, 320, 320 }, /* E7: multiplicación (*) */
    {  321, 321, 321, 321, 321,  -1, 321, 321, 321, 321, 321, 321, 321, 321, 321, 321, 321, 321, 321, 321 }, /* E8: división (/) */
    {  322, 322,  -1, 322, 322, 322, 322, 322, 322, 322, 322, 322, 322, 322, 322, 322, 322, 322, 322, 322 }, /* E9: menor (< ) */
    {  323, 323,  -1, 323, 323, 323, 323, 323, 323, 323, 323, 323, 323, 323, 323, 323, 323, 323, 323, 323 }, /* E10: mayor (>) */
    {  324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324 }, /* E11: menor o igual (<=) */
    {  325, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325, 325 }, /* E12: mayor o igual (>=) */
    {  326, 326, 326, 326, 326, 326, 326, 326, 326, 326, 326, 326, 326, 326, 326, 326, 326, 326, 326, 326 }, /* E13: igualdad (==) */
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E14: posible distinto */
    {  327, 327, 327, 327, 327, 327, 327, 327, 327, 327, 327, 327, 327, 327, 327, 327, 327, 327, 327, 327 }, /* E15: distinto ( !=) */
    {  328, 328, 328, 328, 328, 328, 328, 328, 328, 328, 328, 328, 328, 328, 328, 328, 328, 328, 328, 328 }, /* E16: abre paréntesis */
    {  329, 329, 329, 329, 329, 329, 329, 329, 329, 329, 329, 329, 329, 329, 329, 329, 329, 329, 329, 329 }, /* E17: cierra paréntesis */
    {  330, 330, 330, 330, 330, 330, 330, 330, 330, 330, 330, 330, 330, 330, 330, 330, 330, 330, 330, 330 }, /* E18: llave apertura */
    {  331, 331, 331, 331, 331, 331, 331, 331, 331, 331, 331, 331, 331, 331, 331, 331, 331, 331, 331, 331 }, /* E19: llave cierre */
    {  332, 332, 332, 332, 332, 332, 332, 332, 332, 332, 332, 332, 332, 332, 332, 332, 332, 332, 332, 332 }, /* E20: fin sentencia (;) */
    {  334, 334, 334, 334, 334, 334, 334, 334, 334, 334, 334, 334, 334, 334, 334, 334, 334, 334, 334, 334 }, /* E21: separador (:) */
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }, /* E22: comentario (/* ) */
    {   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1 }  /* E23: posible fin comentario */
};

#endif /* MATRIZ_TOKENS_H */
