#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_MAX_ID 20 /* Tamaño maximo identificadores */

/* Matrices en archivo externo */
#include "matriz_estados.h"
#include "matriz_tokens.h"
#include "matriz_funciones.h"

FILE *inputFile = NULL;
int error = 0;
int yylineno = 1;

char buffer[128];
int bufLen = 0;
int c;
int ultimo_estado = 0;
int ultima_columna = 0;
int dentro_comentario = 0; /* 1 mientras el automata esta dentro de un comentario (lo maneja f12/f13) */
int linea_comentario = 0;  /* linea donde empezo el comentario en curso */

/* Notifica un error lexico ocurrido en el archivo. */

int error_lexico(const char *s) {
    fprintf(stderr, "\nError lexico (L01): %s en linea %d.\n", s, yylineno);
    error = 1;
    return -1;
}


/* Desambigua si una secuencia de letras corresponde a una palabra */
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
    return 314;
}

/* Comprueba que el valor numerico no desborde un entero de 32 bits con signo, es una comodidad para no escribir mucho codigo junto luego, retorna 1 si el rango es valido */
int validar_rango_entero(const char *s) {
    int len = (int)strlen(s);
    if (len > 10) return 0;
    if (len == 10 && strcmp(s, "2147483647") > 0) return 0;
    return 1;
}

/* Caracter no valido en E0 ('.' suelto o caracter fuera del alfabeto) */

int fe(char caracter) {
    char msg[64];
    snprintf(msg, sizeof(msg), "Caracter invalido '%c'", caracter);
    error_lexico(msg);
    buffer[0] = '\0';
    return -1;
}

/* No hace nada*/
int fn(char caracter) {
    (void)caracter;
    return 0;
}

/* Deslectura */
int f0(char caracter) {
    ungetc(caracter, inputFile);
    return 0;
}

/* Inicializa el buffer con la primera letra de un identificador desde E0. */
int f1(char caracter) {
    bufLen = 0;
    buffer[bufLen++] = caracter;
    buffer[bufLen] = '\0';
    return 0;
}

/* Inicializa el buffer con el primer digito de una constante numerica desde E0. */
int f2(char caracter) {
    bufLen = 0;
    buffer[bufLen++] = caracter;
    buffer[bufLen] = '\0';
    return 0;
}

/* Agrega caracteres subsiguientes (letras o digitos) al buffer del identificador. */
int f3(char caracter) {
    if (bufLen < 120) {
        buffer[bufLen++] = caracter;
        buffer[bufLen] = '\0';
    }
    return 0;
}

/* Agrega digitos subsiguientes o el punto decimal a una constante numerica. */
int f4(char caracter) {
    if (bufLen < 120) {
        buffer[bufLen++] = caracter;
        buffer[bufLen] = '\0';
    }
    return 0;
}

/* Cierre de constante numerica. Deslee el delimitador y valida el rango si es entero  */
int f5(char caracter) {
    f0(caracter);

    if (strchr(buffer, '.') == NULL) {
        if (validar_rango_entero(buffer) == 0) {
            error_lexico("Constante entera fuera de rango (-2147483648 a 2147483647)");
            buffer[0] = '\0';
        }
    }
    return 0;
}

/* Cierre de identificador. Deslee el delimitador y comprueba la longitud maxima. */
int f6(char caracter) {
    f0(caracter);

    if (strlen(buffer) > TAM_MAX_ID) {
        error_lexico("Identificador excede el largo maximo permitido (20 caracteres)");
        buffer[0] = '\0';
    }
    return 0;
}

/* Inicializa y almacena un token simple de un solo caracter (operador o delimitador) desde E0. */
int f7(char caracter) {
    bufLen = 0;
    buffer[bufLen++] = caracter;
    buffer[bufLen] = '\0';
    return 0;
}

/* Concatena el segundo caracter a operadores compuestos (==, <=, >=, !=)*/
int f8(char caracter) {
    buffer[bufLen++] = caracter;
    buffer[bufLen] = '\0';
    return 0;
}

/* Blanco consumido por el automata (en E0 o dentro de un comentario): solo cuenta saltos de linea. */
int f9(char caracter) {
    if (caracter == '\n') {
        yylineno++;
    }
    return 0;
}

/* '!' que no forma '!=': deslee el caracter siguiente e informa el error. */
int f10(char caracter) {
    f0(caracter);
    error_lexico("Operador '!' incompleto (se esperaba '!=')");
    buffer[0] = '\0';
    return 0;
}

/* Fin de archivo dentro de un comentario que nunca se cerro. */
int f11(char caracter) {
    int linea_actual = yylineno;
    (void)caracter;
    yylineno = linea_comentario;           /* se informa la linea donde empezo el comentario */
    error_lexico("Comentario sin cerrar");
    yylineno = linea_actual;
    buffer[0] = '\0';
    dentro_comentario = 0;
    return 0;
}

/* Inicio de comentario (E8 con '*', hacia E22): desde aca cualquier caracter es valido. */
int f12(char caracter) {
    (void)caracter;
    dentro_comentario = 1;
    linea_comentario = yylineno;
    return 0;
}

/* Fin de comentario (E23 con '/', hacia E0). */
int f13(char caracter) {
    (void)caracter;
    dentro_comentario = 0;
    return 0;
}

/* Devuelve la columna del caracter. Si no pertenece al alfabeto lo informa (una sola vez)
   y lo reemplaza por un blanco, asi el automata lo trata como delimitador. */
int get_evento(int caracter) {
    if (caracter == EOF) return COL_FDA; /* 18 EN MATRIZ ESTADOS  */
    if (isalpha(caracter)) return 0;
    if (isdigit(caracter)) return 1;
    if (caracter == '=') return 2;
    if (caracter == '+') return 3;
    if (caracter == '-') return 4;
    if (caracter == '*') return 5;
    if (caracter == '/') return 6;
    if (caracter == '<') return 7;
    if (caracter == '>') return 8;
    if (caracter == '!') return 9;
    if (caracter == '(') return 10;
    if (caracter == ')') return 11;
    if (caracter == '{') return 12;
    if (caracter == '}') return 13;
    if (caracter == ';') return 14;
    if (caracter == ':') return 15;
    if (caracter == '.') return 16;
    /* espacio, tabulacion, salto de linea, retorno de carro */
    if (isspace(caracter)) return COL_BLANCO; /* MATRIZ_ESTADOS 17, UTILIZADO PARA ESPACIOS, TABULACION O SALTO DE LINEAS  */
    /* dentro de un comentario cualquier caracter es valido */
    if (dentro_comentario) return COL_LETRA; /* 0 EN MATRIZ_ESTADOS */

    char msg[64];
    snprintf(msg, sizeof(msg), "Caracter fuera del alfabeto '%c'", (char)caracter);
    error_lexico(msg);
    c = ' ';
    return COL_BLANCO;
}

/* yylex */

int yylex(void) {
    static int primer_llamado = 1;
    int estado = 0;
    int estado_final = -1;
    int columna;
    int tipotoken; /* Codigo numerico del tipo reconocido */

    /* Carga el primer caracter del archivo si es la primera invocacion */
    if (primer_llamado) {
        c = fgetc(inputFile);
        primer_llamado = 0;
    }

    bufLen = 0;
    buffer[0] = '\0';

    /* Bucle del analizador: los blancos y comentarios los consume el propio automata */
    while (estado != estado_final) {
        /* Notifica fin de archivo a Bison cuando no hay un token en proceso */
        if (c == EOF && estado == 0) {
            return 0;
        }

        columna = get_evento(c); /* obtener la columna de la matriz */

        matriz_funciones[estado][columna]((char)c); /* Ejecuta la accion semantica asociada al estado */

        /* Guarda donde quedo*/
        ultimo_estado = estado;
        ultima_columna = columna;

        estado = matriz_estados[estado][columna];

        c = fgetc(inputFile);
    }

    tipotoken = matriz_tokens[ultimo_estado][ultima_columna];

    if (tipotoken == 314) {
        return palabras_reservadas(buffer);
    }

    return tipotoken;
}

/* main */

/*

int main(int argc, char *argv[]) {
    int token;
    const char *nombre_archivo = "prueba.txt";

    if (argc > 1) {
        nombre_archivo = argv[1];
    }

    if ((inputFile = fopen(nombre_archivo, "r")) == NULL) {
        printf("Error: no se pudo abrir el archivo %s\n", nombre_archivo);
        return 1;
    }

    printf("TOKEN | LEXEMA\n");
    printf("-------------------\n");

    c = fgetc(inputFile);

    while (feof(inputFile) == 0 && c != EOF) {
        token = yylex(); // Llama al lexer 

        if (token > 0 && buffer[0] != '\0') {
            printf("%d | %s\n", token, buffer);
        }
    }

    if (fclose(inputFile) != 0) {
        printf("Error al cerrar el archivo.\n");
    }

    if (error == 0) {
        printf("\n - Compilacion AL EXITOSA - \n");
    } else {
        printf("\n - Analisis Lexico completo con ERRORES - \n");
    }

    return error;
}

*/

/* LEXER DE ANTES, LOS CAMBIOS FUERON PARA QUE ANDE BISON */

/* int yylex(void) {
� � int estado = 0;
� � int estado_final = -1;
� � int columna;
� � int tipotoken; // Codigo numerico del tipo reconocido 

� � bufLen = 0;
� � buffer[0] = '\0';

� � // Bucle del analizador: los blancos y comentarios los consume el propio automata 
� � while (estado != estado_final) {
� � � � columna = get_evento(c); // obtener la columna de la matriz /

� � � � matriz_funciones[estado][columna]((char)c); // Ejecuta la accion semantica asociada al estado  

� � � � // Guarda donde quedo
� � � � ultimo_estado = estado;
� � � � ultima_columna = columna;

� � � � estado = matriz_estados[estado][columna];

� � � � c = fgetc(inputFile);
� � }

� � tipotoken = matriz_tokens[ultimo_estado][ultima_columna];

� � if (tipotoken == 314) {
� � � � return palabras_reservadas(buffer);
� � }

� � return tipotoken;
}
*/
