#ifndef MATRIZ_TOKENS_H
#define MATRIZ_TOKENS_H

#ifndef ESTADOS
#define ESTADOS 24
#endif

#ifndef COLUMNAS
#define COLUMNAS 19
#endif

#define NO_DEVUELVE -1

/* Se consulta con [ultimo_estado][ultima_columna], es decir, la transicion que llevo a EF.
   NO_DEVUELVE = la transicion no cierra token.
   337 = ERROR LEXICO (caracter '.' suelto, '!' sin '=', comentario sin cerrar).
   0   = fin de archivo en E0 (no hay mas tokens). */

static const int matriz_tokens[ESTADOS][COLUMNAS] = {
    /*     Let           Dig           =             +             -             *             /             <             >             !             (             )             {             }             ;             :             .             BLANCO        FDA */
    /* 0  */ { NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  337,          NO_DEVUELVE,  0 },
    /* 1  */ { NO_DEVUELVE,  NO_DEVUELVE,  314,          314,          314,          314,          314,          314,          314,          314,          314,          314,          314,          314,          314,          314,          314,          314,          314 },
    /* 2  */ { 315,          NO_DEVUELVE,  315,          315,          315,          315,          315,          315,          315,          315,          315,          315,          315,          315,          315,          315,          NO_DEVUELVE,  315,          315 },
    /* 3  */ { 316,          NO_DEVUELVE,  316,          316,          316,          316,          316,          316,          316,          316,          316,          316,          316,          316,          316,          316,          316,          316,          316 }, 
    /* 4  */ { 317,          317,          NO_DEVUELVE,  317,          317,          317,          317,          317,          317,          317,          317,          317,          317,          317,          317,          317,          317,          317,          317 },
    /* 5  */ { 318,          318,          318,          318,          318,          318,          318,          318,          318,          318,          318,          318,          318,          318,          318,          318,          318,          318,          318 },
    /* 6  */ { 319,          319,          319,          319,          319,          319,          319,          319,          319,          319,          319,          319,          319,          319,          319,          319,          319,          319,          319 },
    /* 7  */ { 320,          320,          320,          320,          320,          320,          320,          320,          320,          320,          320,          320,          320,          320,          320,          320,          320,          320,          320 },
    /* 8  */ { 321,          321,          321,          321,          321,          NO_DEVUELVE,  321,          321,          321,          321,          321,          321,          321,          321,          321,          321,          321,          321,          321 },
    /* 9  */ { 322,          322,          NO_DEVUELVE,  322,          322,          322,          322,          322,          322,          322,          322,          322,          322,          322,          322,          322,          322,          322,          322 },
    /* 10 */ { 323,          323,          NO_DEVUELVE,  323,          323,          323,          323,          323,          323,          323,          323,          323,          323,          323,          323,          323,          323,          323,          323 },
    /* 11 */ { 324,          324,          324,          324,          324,          324,          324,          324,          324,          324,          324,          324,          324,          324,          324,          324,          324,          324,          324 },
    /* 12 */ { 325,          325,          325,          325,          325,          325,          325,          325,          325,          325,          325,          325,          325,          325,          325,          325,          325,          325,          325 },
    /* 13 */ { 326,          326,          326,          326,          326,          326,          326,          326,          326,          326,          326,          326,          326,          326,          326,          326,          326,          326,          326 },
    /* 14 */ { 337,          337,          NO_DEVUELVE,  337,          337,          337,          337,          337,          337,          337,          337,          337,          337,          337,          337,          337,          337,          337,          337 },
    /* 15 */ { 327,          327,          327,          327,          327,          327,          327,          327,          327,          327,          327,          327,          327,          327,          327,          327,          327,          327,          327 },
    /* 16 */ { 328,          328,          328,          328,          328,          328,          328,          328,          328,          328,          328,          328,          328,          328,          328,          328,          328,          328,          328 },
    /* 17 */ { 329,          329,          329,          329,          329,          329,          329,          329,          329,          329,          329,          329,          329,          329,          329,          329,          329,          329,          329 },
    /* 18 */ { 330,          330,          330,          330,          330,          330,          330,          330,          330,          330,          330,          330,          330,          330,          330,          330,          330,          330,          330 },
    /* 19 */ { 331,          331,          331,          331,          331,          331,          331,          331,          331,          331,          331,          331,          331,          331,          331,          331,          331,          331,          331 },
    /* 20 */ { 332,          332,          332,          332,          332,          332,          332,          332,          332,          332,          332,          332,          332,          332,          332,          332,          332,          332,          332 },
    /* 21 */ { 334,          334,          334,          334,          334,          334,          334,          334,          334,          334,          334,          334,          334,          334,          334,          334,          334,          334,          334 },
    /* 22 */ { NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  337 },
    /* 23 */ { NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  NO_DEVUELVE,  337 }
};

#endif
