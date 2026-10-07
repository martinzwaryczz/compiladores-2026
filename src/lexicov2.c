#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "matriz_estados.h"
#include "matriz_tokens.h"
#include "matriz_acciones.h"

char auxiliar[256];
int auxLen = 0;
int yylineno = 1;

// ------------------- FUNCIONES DE ACCIÓN -------------------
int fn(char c) { 
    (void)c;
    return 2; 
}

int f0(char c) {
    ungetc(c, stdin);
    if (c == '\n') yylineno--;
    return 3;
}

int f1(char c) {
    auxLen = 0;
    auxiliar[auxLen++] = c;
    auxiliar[auxLen] = '\0';
    return -1;
}

int f2(char c) {
    auxLen = 0;
    auxiliar[auxLen++] = c;
    auxiliar[auxLen] = '\0';
    return -1;
}

int f3(char c) {
    auxiliar[auxLen++] = c;
    auxiliar[auxLen] = '\0';
    return -1;
}

int f4(char c) {
    auxiliar[auxLen++] = c;
    auxiliar[auxLen] = '\0';
    return -1;
}

int f5(char c) {
    ungetc(c, stdin);
    if (c == '\n') yylineno--;
    return 3;
}

int yyerror(const char *s) {
    fprintf(stderr, "\nError lexico (L01): %s en linea %d.\n", s, yylineno);
    return 38;
}

int fe(char c) {
    char msg[100];
    sprintf(msg, "Caracter invalido '%c'", c);
    yyerror(msg);
    return 38;
}

// ------------------- PALABRAS RESERVADAS (DUOTIPO) -------------------
int palabras_reservadas(const char *s) {
    if (strcmp(s, "entero") == 0)    return 1;
    if (strcmp(s, "real") == 0)      return 2;
    if (strcmp(s, "funcion") == 0)   return 3;
    if (strcmp(s, "principal") == 0) return 4;
    if (strcmp(s, "retornar") == 0)  return 5;
    if (strcmp(s, "segun") == 0)     return 6;
    if (strcmp(s, "caso") == 0)      return 7;
    if (strcmp(s, "defecto") == 0)   return 8;
    if (strcmp(s, "mientras") == 0)  return 9;
    if (strcmp(s, "aEntero") == 0)   return 10;
    if (strcmp(s, "aReal") == 0)     return 11;
    if (strcmp(s, "y") == 0)         return 12;
    if (strcmp(s, "o") == 0)         return 13;
    return 14; 
}

// ------------------- CLASIFICADOR DE CARACTERES -------------------
int getColumn(int c) {
    if (c == '\n') yylineno++;
    if (isalpha(c)) return 0;       // letra
    if (isdigit(c)) return 1;       // digito
    if (c == '=') return 2;
    if (c == '+') return 3;
    if (c == '-') return 4;
    if (c == '*') return 5;
    if (c == '/') return 6;
    if (c == '<') return 7;
    if (c == '>') return 8;
    if (c == '!') return 9;
    if (c == '(') return 10;
    if (c == ')') return 11;
    if (c == '{') return 12;
    if (c == '}') return 13;
    if (c == ';') return 14;
    if (c == ':') return 15;
    if (c == '_') return 16;
    if (c == '.') return 17;
    if (isspace(c)) return 18;      // espacio / tab / salto de linea
    return 19;                      // invalido (OTRO)
}

// ------------------- ANALIZADOR LÉXICO (yylex) -------------------
int yylex(void) {
    int caracter;
    int estado = 0;
    int columna = 0;

    auxiliar[0] = '\0';
    auxLen = 0;

    while (estado != -1) {
        caracter = fgetc(stdin);

        if (caracter == EOF) {
            if (estado != 0 && tokens[estado][18] != -1) {
                if (tokens[estado][18] == 14)
                    return palabras_reservadas(auxiliar);
                return tokens[estado][18];
            }
            return 0;
        }

        columna = getColumn(caracter);
        if (columna == 19) {
            fe((char)caracter);
            return 38;
        }

        // Si estamos en E0 y leemos un símbolo/operador (no letra, no dígito, no espacio)
        if (estado == 0 && columna != 0 && columna != 1 && columna != 18) {
            auxLen = 0;
            auxiliar[auxLen++] = (char)caracter;
            auxiliar[auxLen] = '\0';
        }
        // Si estamos acumulando un identificador o palabra reservada
        else if ((estado == 1 || estado == 2 || estado == 2bis) && (columna == 0 || columna == 1 || columna == 16)) {
            if (auxLen < 255) {
                auxiliar[auxLen++] = (char)caracter;
                auxiliar[auxLen] = '\0';
            }
        }
        // Si estamos en un operador de 1 car y viene otro igual para hacer uno doble (==, <=, >=, !=)
        else if ((estado == 3 || estado == 9 || estado == 11 || estado == 13) && columna == 2) {
            if (auxLen < 255) {
                auxiliar[auxLen++] = (char)caracter;
                auxiliar[auxLen] = '\0';
            }
        }
        // Si estamos leyendo números enteros o reales
        else if ((estado == 25 || estado == 26) && (columna == 1 || columna == 17)) {
            if (auxLen < 255) {
                auxiliar[auxLen++] = (char)caracter;
                auxiliar[auxLen] = '\0';
            }
        }

        // Ejecutar rutina semántica de la matriz
        proceso[estado][columna]((char)caracter);

        // Si la celda define un corte (siguiente estado == -1)
        if (siguiente_estado[estado][columna] == -1 && tokens[estado][columna] != -1) {
            int token_id = tokens[estado][columna];

            // Identificador o palabra reservada
            if (token_id == 14) {
                return palabras_reservadas(auxiliar);
            }

            // Comentario (se descarta y vuelve a E0)
            if (token_id == 36) {
                estado = 0;
                auxiliar[0] = '\0';
                auxLen = 0;
                continue;
            }

            return token_id;
        }

        estado = siguiente_estado[estado][columna];
    }

    return 0;
}


// ------------------- PROGRAMA PRINCIPAL -------------------
int main(void) {
    int token;
    while ((token = yylex()) > 0) {
        printf("Token: %-4d | Lexema: %s\n", token, auxiliar);
    }
    return 0;
}
