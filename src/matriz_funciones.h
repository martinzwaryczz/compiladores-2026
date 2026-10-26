#ifndef MATRIZ_FUNCIONES_H
#define MATRIZ_FUNCIONES_H

#ifndef ESTADOS
#define ESTADOS 24
#endif

#ifndef COLUMNAS
#define COLUMNAS 19
#endif

/* Prototipos de las acciones semanticas */
int fn(char c);
int f0(char c);
int f1(char c);
int f2(char c);
int f3(char c);
int f4(char c);
int f5(char c);
int f6(char c);
int f7(char c);
int f8(char c);
int f9(char c);
int f10(char c);
int f11(char c);
int f12(char c);
int f13(char c);
int fe(char c);

static int (*matriz_funciones[ESTADOS][COLUMNAS])(char c) = {
    /*           L    D    =    +    -    *    /    <    >    !    (    )    {    }    ;    :    .  BLANCO FDA */
    /* 0: E0  */ { f1,  f2,  f7,  f7,  f7,  f7,  f7,  f7,  f7,  f7,  f7,  f7,  f7,  f7,  f7,  f7,  fe,   f9,  fn },
    /* 1: E1  */ { f3,  f3,  f6,  f6,  f6,  f6,  f6,  f6,  f6,  f6,  f6,  f6,  f6,  f6,  f6,  f6,  f6,   f6,  f6 },
    /* 2: E2  */ { f5,  f4,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f4,   f5,  f5 },
    /* 3: E3  */ { f5,  f4,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,   f5,  f5 },
    /* 4: E4  */ { f0,  f0,  f8,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,   f0,  f0 },
    /* 5: E5  */ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,   f0,  f0 },
    /* 6: E6  */ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,   f0,  f0 },
    /* 7: E7  */ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,   f0,  f0 },
    /* 8: E8  */ { f0,  f0,  f0,  f0,  f0,  f12, f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,   f0,  f0 },
    /* 9: E9  */ { f0,  f0,  f8,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,   f0,  f0 },
    /* 10: E10*/ { f0,  f0,  f8,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,   f0,  f0 },
    /* 11: E11*/ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,   f0,  f0 },
    /* 12: E12*/ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,   f0,  f0 },
    /* 13: E13*/ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,   f0,  f0 },
    /* 14: E14*/ { f10, f10, f8,  f10, f10, f10, f10, f10, f10, f10, f10, f10, f10, f10, f10, f10, f10,  f10, f10 },
    /* 15: E15*/ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,   f0,  f0 },
    /* 16: E16*/ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,   f0,  f0 },
    /* 17: E17*/ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,   f0,  f0 },
    /* 18: E18*/ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,   f0,  f0 },
    /* 19: E19*/ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,   f0,  f0 },
    /* 20: E20*/ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,   f0,  f0 },
    /* 21: E21*/ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,   f0,  f0 },
    /* 22: E22*/ { fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   f9,  f11 },
    /* 23: E23*/ { fn,  fn,  fn,  fn,  fn,  fn,  f13, fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,   f9,  f11 }
};

#endif
