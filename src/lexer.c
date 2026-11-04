#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_MAX_ID 20

#include "matriz_estados.h"
#include "matriz_tokens.h"
#include "matriz_funciones.h"
#include "matriz_unreads.h"

FILE *inputFile = NULL;
int error = 0;
int yylineno = 1;

char buffer[128];
int bufLen = 0;
int c = 0;
int ultimo_estado = 0;
int ultima_columna = 0;
int dentro_comentario = 0;
int linea_comentario = 0;

int error_lexico(const char *codigo, const char *s) {
    fprintf(stderr, "\nError lexico (%s): %s en linea %d.\n", codigo, s, yylineno);
    error = 1;
    return -1;
}

int advertencia_lexica(const char *codigo, const char *s) {
    fprintf(stderr, "\nAdvertencia lexica (%s): %s en linea %d.\n", codigo, s, yylineno);
    return 0;
}

int palabras_reservadas(const char *s) {
    if (strcmp(s, "entero") == 0)    return 301;
    if (strcmp(s, "real") == 0)      return 302;
    if (strcmp(s, "funcion") == 0)   return 303;
    if (strcmp(s, "principal") == 0) return 304;
    if (strcmp(s, "retornar") == 0)  return 305;
    if (strcmp(s, "segun") == 0)     return 306;
    if (strcmp(s, "caso") == 0)      return 307;
    if (strcmp(s, "defecto") == 0)   return 308;
    if (strcmp(s, "mientras") == 0)  return 309;
    if (strcmp(s, "aEntero") == 0)   return 310;
    if (strcmp(s, "aReal") == 0)     return 311;
    if (strcmp(s, "y") == 0)         return 312;
    if (strcmp(s, "o") == 0)         return 313;
    if (strcmp(s, "escribir") == 0)  return 335;
    return 314; /* TK_ID */
}

int validar_rango_entero(const char *s) {
    int len = (int)strlen(s);
    if (len > 10) return 0;
    if (len == 10 && strcmp(s, "2147483647") > 0) return 0;
    return 1;
}

int validar_rango_real(const char *s) {
    const char *punto = strchr(s, '.');
    int len_entera = (punto != NULL) ? (int)(punto - s) : (int)strlen(s);
    if (len_entera > 38) return 0;
    return 1;
}

/* Acciones semánticas */

int fn(char caracter) {
    (void)caracter;
    return 0;
}

int fe(char caracter) {
    char msg[128];
    if (ultimo_estado == 14) {
        snprintf(msg, sizeof(msg), "Caracter '!' inesperado. Se esperaba '=' para formar '!='");
        error_lexico("L5", msg); /* Se asigna L5 */
    } else if (ultima_columna == 18) { /* FDA */
        int lin = yylineno;
        yylineno = linea_comentario;
        error_lexico("L4", "Fin de archivo inesperado. Comentario sin cerrar"); /* Se asigna L4 */
        yylineno = lin;
        dentro_comentario = 0;
        buffer[0] = '\0';
        return -1;
    } else {
        snprintf(msg, sizeof(msg), "Caracter '%c' no valido en el lenguaje", caracter);
        error_lexico("L1", msg); /* Se asigna L1 */
    }
    buffer[0] = '\0';
    return -1;
}

int f1(char caracter) {
    if (bufLen < 120) {
        buffer[bufLen++] = caracter;
        buffer[bufLen] = '\0';
    }
    return 0;
}

int f2(char caracter) {
    (void)caracter;
    if (strlen(buffer) > TAM_MAX_ID) {
        char msg[128];
        snprintf(msg, sizeof(msg), "Identificador '%s' supera el limite de 20 caracteres. Se truncara", buffer);
        advertencia_lexica("L2", msg);
        buffer[TAM_MAX_ID] = '\0';
    }
    return 0;
}

int f3(char caracter) {
    if (bufLen < 120) {
        buffer[bufLen++] = caracter;
        buffer[bufLen] = '\0';
    }
    return 0;
}

int f4(char caracter) {
    (void)caracter;
    if (strchr(buffer, '.') == NULL) {
        if (validar_rango_entero(buffer) == 0) {
            error_lexico("L3", "Constante entera fuera de rango (-2147483648 a 2147483647)");
            buffer[0] = '\0';
        }
    } else {
        if (validar_rango_real(buffer) == 0) {
            error_lexico("L3", "Constante real fuera de rango de 32 bits (max +/- 3.4028235e+38)");
            buffer[0] = '\0';
        }
    }
    return 0;
}

int f5(char caracter) {
    if (bufLen < 120) {
        buffer[bufLen++] = caracter;
        buffer[bufLen] = '\0';
    }
    return 0;
}

int f6(char caracter) {
    if (caracter == '\n') {
        yylineno++;
    }
    return 0;
}

int f7(char caracter) {
    (void)caracter;
    dentro_comentario = 1;
    linea_comentario = yylineno;
    bufLen = 0;
    buffer[0] = '\0';
    return 0;
}

int f8(char caracter) {
    (void)caracter;
    dentro_comentario = 0;
    bufLen = 0;
    buffer[0] = '\0';
    return 0;
}

int get_evento(int caracter) {
    if (caracter == EOF) return 18;                               /* FDA */
    if (dentro_comentario) {
        if (caracter == '*') return 5;                            /* * */
        if (caracter == '/') return 6;                            /* / */
        if (caracter == '\n' || caracter == ' ' || caracter == '\t' || caracter == '\r') return 17; /* BLANCO */
        return 0;                                                 /* LETRA */
    }

    if (isalpha(caracter)) return 0;   /* LETRA: a-z, A-Z */
    if (isdigit(caracter)) return 1;   /* DIGITO */
    if (caracter == '=') return 2;     /* = */
    if (caracter == '+') return 3;     /* + */
    if (caracter == '-') return 4;     /* - */
    if (caracter == '*') return 5;     /* * */
    if (caracter == '/') return 6;     /* / */
    if (caracter == '<') return 7;     /* < */
    if (caracter == '>') return 8;     /* > */
    if (caracter == '!') return 9;     /* ! */
    if (caracter == '(') return 10;    /* ( */
    if (caracter == ')') return 11;    /* ) */
    if (caracter == '{') return 12;    /* { */
    if (caracter == '}') return 13;    /* } */
    if (caracter == ';') return 14;    /* ; */
    if (caracter == ':') return 15;    /* : */
    if (caracter == '.') return 16;    /* . */
    if (caracter == ' ' || caracter == '\t' || caracter == '\r' || caracter == '\n') return 17; /* BLANCO */

    return 19;                         /* OTRO */
}

/* yylex */
int yylex(void) {
    int estado = 0;
    int estado_final = -1;
    int columna;
    int tipotoken;

    bufLen = 0;
    buffer[0] = '\0';

    while (estado != estado_final) {
        c = fgetc(inputFile);
        columna = get_evento(c);

        ultimo_estado = estado;
        ultima_columna = columna;

        matriz_funciones[estado][columna]((char)c);

        estado = matriz_estados[estado][columna];
    }

    /* Deslectura siguiendo la tabla matriz_unreads */
    if (matriz_unreads[ultimo_estado][ultima_columna] == 1 && c != EOF) {
        ungetc(c, inputFile);
    }

    tipotoken = matriz_tokens[ultimo_estado][ultima_columna];

    if (tipotoken == 314) {
        tipotoken = palabras_reservadas(buffer);
    }

  
    // printf("Token: %d | Lexema: '%s' | Linea: %d\n", tipotoken, buffer, yylineno);

    return tipotoken;
}
