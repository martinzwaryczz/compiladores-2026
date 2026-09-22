/* =====================================================================
 * lexico.c — Analizador léxico de DUOTIPO (Grupo E)
 *
 * Traduce el diseño de tablas (nuevo_estado, tokens, unreads, proceso)
 * en el loop de lectura carácter a carácter descripto en el apunte de
 * cátedra, adaptado al alfabeto y a los 27+1 estados de DUOTIPO.
 *
 * Falta completar (marcado con TODO):
 *   - Contenido real de f1..f5 (tabla de símbolos, lista de strings,
 *     armado de constantes numéricas).
 *   - Distinción entre id y palabra reservada (función
 *     palabras_reservadas()).
 *   - Contador de línea para los mensajes de error.
 * ===================================================================== */

#include <stdio.h>
#include <ctype.h>
#include "tablas_lexico.h"

static int linea_actual = 1;

/* ---------------------------------------------------------------------
 * Traduce un caracter leido en un "evento" (columna de las tablas).
 * Ajustar aca si agregan/sacan simbolos del alfabeto.
 * ------------------------------------------------------------------- */
int geteven(int c)
{
    if (isalpha(c))              return EV_LETRA;
    if (isdigit(c))               return EV_DIGITO;
    switch (c) {
        case '=':  return EV_IGUAL;
        case '+':  return EV_MAS;
        case '-':  return EV_MENOS;
        case '*':  return EV_ASTERISCO;
        case '/':  return EV_BARRA;
        case '<':  return EV_MENOR;
        case '>':  return EV_MAYOR;
        case '!':  return EV_EXCLAMACION;
        case '(':  return EV_PAR_IZQ;
        case ')':  return EV_PAR_DER;
        case '{':  return EV_LLAVE_IZQ;
        case '}':  return EV_LLAVE_DER;
        case ';':  return EV_PUNTO_COMA;
        case ':':  return EV_DOS_PUNTOS;
        case '_':  return EV_GUION_BAJO;
        case '.':  return EV_PUNTO;
        case ' ':
        case '\t':
        case '\r':
            return EV_BLANCO_TAB;
        case '\n':
            linea_actual++;
            return EV_BLANCO_TAB;
        default:
            /* Caracter fuera del alfabeto: lo tratamos como si fuera
             * un "." suelto -> desde cualquier estado activo termina
             * en EF con token de error (38). Si el generador de
             * eventos no lo reconoce en absoluto, agregarlo aca. */
            return EV_PUNTO;
    }
}

/* ---------------------------------------------------------------------
 * Rutinas semanticas (esqueleto — completar segun tabla de simbolos
 * / lista de strings que definan).
 * ------------------------------------------------------------------- */
static char buffer_lexema[256];
static int  pos_buffer = 0;

void f1(char c) /* letra en E0: arranca un identificador/palabra */
{
    pos_buffer = 0;
    buffer_lexema[pos_buffer++] = c;
}

void f2(char c) /* digito en E0: arranca una constante */
{
    pos_buffer = 0;
    buffer_lexema[pos_buffer++] = c;
}

void f3(char c) /* sigue acumulando letras/digitos/'_' de un id */
{
    if (pos_buffer < (int)sizeof(buffer_lexema) - 1)
        buffer_lexema[pos_buffer++] = c;
}

void f4(char c) /* cierra el string acumulado (id o cte) */
{
    buffer_lexema[pos_buffer] = '\0';
    /* TODO: buscar/insertar buffer_lexema en tabla de simbolos o
     * lista de strings segun corresponda */
}

void f5(char c) /* sigue acumulando digitos/'.' de una constante numerica */
{
    if (pos_buffer < (int)sizeof(buffer_lexema) - 1)
        buffer_lexema[pos_buffer++] = c;
}

void fn(char c) /* resto de los casos: no hacer nada */
{
    (void)c;
}

/* ---------------------------------------------------------------------
 * Analizador lexico: devuelve el codigo de token siguiente.
 * ------------------------------------------------------------------- */
int analizador_lexico(void)
{
    int anterior = E0;

    for (;;) {
        int leido = getchar();

        if (leido == EOF) {
            /* fin de archivo fisico (no el "__" del lenguaje) */
            return 37; /* token EOF */
        }

        int evento = geteven(leido);
        int estado = nuevo_estado[anterior][evento];

        proceso[anterior][evento]((char)leido);

        if (unreads[anterior][evento] == 1) {
            ungetc(leido, stdin);
        }

        if (estado == EF) {
            int token = tokens[anterior][evento];

            if (token == -1) {
                /* Transicion "silenciosa" (comentario cerrado,
                 * separador ':', etc.): no se emite token, se
                 * arranca de nuevo desde E0 */
                anterior = E0;
                continue;
            }

            if (token == 14) {
                /* TODO: distinguir identificador de palabra
                 * reservada buscando buffer_lexema en la tabla de
                 * palabras reservadas (entero, real, funcion,
                 * principal, retornar, segun, caso, defecto,
                 * mientras, aEntero, aReal, y, o) */
            }

            if (token == 38) {
                fprintf(stderr,
                        "Error lexico en linea %d: caracter '%c' inesperado\n",
                        linea_actual, leido);
                /* recuperacion: no cortar la compilacion, seguir
                 * buscando el proximo token */
                anterior = E0;
                continue;
            }

            return token;
        }

        anterior = estado;
    }
}
