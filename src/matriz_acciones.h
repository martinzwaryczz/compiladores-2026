#ifndef MATRIZ_ACCIONES_H
#define MATRIZ_ACCIONES_H

#define ESTADOS 27
#define COLUMNAS 19

// Declaraciones previas de las funciones de acción necesarias para inicializar la matriz
int fn(char c);
int f0(char c);
int f1(char c);
int f2(char c);
int f3(char c);
int f4(char c);
int f5(char c);
int fe(char c);

static int (*proceso[ESTADOS][COLUMNAS])(char c) = {
    /* E0     */ { f1,  f2,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fe,  fn },
    /* E1     */ { f3,  f3,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f3,  f0,  f0 },
    /* E2     */ { f3,  f3,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f3,  f0,  f0 },
    /* E2bis  */ { f3,  f3,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f3,  f0,  f0 },
    /* E3     */ { f0,  f0,  fn,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E4     */ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E5     */ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E6     */ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E7     */ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E8     */ { f0,  f0,  f0,  f0,  f0,  fn,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E9     */ { f0,  f0,  fn,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E10    */ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E11    */ { f0,  f0,  fn,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E12    */ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E13    */ { f0,  f0,  fn,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E14    */ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E15    */ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E16    */ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E17    */ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E18    */ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E19    */ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E21    */ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0 },
    /* E22    */ { f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  f0,  fn,  f0,  f0 },
    /* E23    */ { fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn },
    /* E24    */ { fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn,  fn },
    /* E25    */ { f5,  f4,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f4,  f5 },
    /* E26    */ { f5,  f4,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5,  f5 }
};

#endif
