%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex(void);
extern FILE *inputFile;
extern int yylineno;
extern char buffer[];

void yyerror(const char *s);
%}

/* Habilita tablas de depuracion nativas de Bison */
%debug

/* Declaracion oficial de Tokens segun spec.md de DuoTipo */
%token TK_ENTERO        301
%token TK_REAL          302
%token TK_FUNCION       303
%token TK_PRINCIPAL     304
%token TK_RETORNAR      305
%token TK_SEGUN         306
%token TK_CASO          307
%token TK_DEFECTO       308
%token TK_MIENTRAS      309
%token TK_AENTERO       310
%token TK_AREAL         311
%token TK_AND           312
%token TK_OR            313
%token TK_ID            314
%token TK_NUM_INT       315
%token TK_NUM_REAL      316
%token TK_ASSIGN        317
%token TK_PLUS          318
%token TK_MINUS         319
%token TK_MULT          320
%token TK_DIV           321
%token TK_LT            322
%token TK_GT            323
%token TK_NEQ           324
%token TK_LE            325
%token TK_GE            326
%token TK_EQ            327
%token TK_LPAREN        328
%token TK_RPAREN        329
%token TK_LBRACE        330
%token TK_RBRACE        331
%token TK_SEMI          332
%token TK_COLON         333
%token TK_DOT           334
%token TK_ESCRIBIR      335
%token TK_ERROR         337

/* Precedencia y asociatividad de operadores */
%right TK_ASSIGN
%left TK_OR
%left TK_AND
%left TK_EQ TK_NEQ
%left TK_LT TK_LE TK_GT TK_GE
%left TK_PLUS TK_MINUS
%left TK_MULT TK_DIV
%right UMINUS

%start programa

%%

/* --- Estructura Global del Programa --- */

programa:
      declaraciones_globales funciones principal
    | funciones principal
    | declaraciones_globales principal
    | principal
    ;

declaraciones_globales:
      declaracion TK_SEMI
    | declaraciones_globales declaracion TK_SEMI
    ;

declaracion:
      tipo TK_ID
    ;

tipo:
      TK_ENTERO
    | TK_REAL
    ;

/* --- Definicion de Funciones --- */

funciones:
      funcion
    | funciones funcion
    ;

funcion:
      TK_FUNCION tipo TK_ID TK_LPAREN TK_RPAREN TK_LBRACE cuerpo TK_RBRACE
    ;

principal:
      TK_PRINCIPAL TK_LBRACE cuerpo TK_RBRACE
    | TK_PRINCIPAL TK_LPAREN TK_RPAREN TK_LBRACE cuerpo TK_RBRACE
    ;

cuerpo:
      decl_locales sentencias
    | decl_locales
    | sentencias
    | 
    ;

decl_locales:
      declaracion TK_SEMI
    | decl_locales declaracion TK_SEMI
    ;

/* --- Sentencias de Control y Ejecucion --- */

sentencias:
      sentencia
    | sentencias sentencia
    ;

sentencia:
      TK_ID TK_ASSIGN expresion TK_SEMI
    | TK_ESCRIBIR TK_LPAREN expresion TK_RPAREN TK_SEMI
    | TK_RETORNAR expresion TK_SEMI
    | TK_MIENTRAS TK_LPAREN expresion TK_RPAREN TK_LBRACE sentencias TK_RBRACE
    | bloque_segun
    | llamada_funcion TK_SEMI
    ;

llamada_funcion:
      TK_ID TK_LPAREN TK_RPAREN
    ;

bloque_segun:
      TK_SEGUN TK_LPAREN TK_ID TK_RPAREN TK_LBRACE lista_casos caso_defecto TK_RBRACE
    | TK_SEGUN TK_LPAREN TK_ID TK_RPAREN TK_LBRACE lista_casos TK_RBRACE
    ;

lista_casos:
      caso
    | lista_casos caso
    ;

caso:
      TK_CASO TK_NUM_INT TK_COLON sentencias
    ;

caso_defecto:
      TK_DEFECTO TK_COLON sentencias
    ;

/* --- Expresiones --- */

expresion:
      expresion TK_PLUS expresion
    | expresion TK_MINUS expresion
    | expresion TK_MULT expresion
    | expresion TK_DIV expresion
    | expresion TK_LT expresion
    | expresion TK_GT expresion
    | expresion TK_LE expresion
    | expresion TK_GE expresion
    | expresion TK_EQ expresion
    | expresion TK_NEQ expresion
    | expresion TK_ASSIGN expresion
    | expresion TK_AND expresion
    | expresion TK_OR expresion
    | TK_MINUS expresion %prec UMINUS
    | TK_LPAREN expresion TK_RPAREN
    | TK_AENTERO TK_LPAREN expresion TK_RPAREN
    | TK_AREAL TK_LPAREN expresion TK_RPAREN
    | llamada_funcion
    | TK_ID
    | TK_NUM_INT
    | TK_NUM_REAL
    ;

%%

/* 
 * Sobrescritura limpia de macros de depuracion de Bison:
 * Se ubican aqui abajo para ejecutarse DESPUES de las definiciones por defecto de Bison
 * y evitar warnings de redefinicion.
 */
#ifdef YY_REDUCE_PRINT
#undef YY_REDUCE_PRINT
#endif
#define YY_REDUCE_PRINT(Rule) do {                                                  \
    fprintf(stderr, "\n>>> [REDUCCION]: Regla %d aplicada (linea %d)\n", Rule, yylineno); \
} while (0)

#ifdef YY_STACK_PRINT
#undef YY_STACK_PRINT
#endif
#define YY_STACK_PRINT(Bottom, Top) do {                                            \
    fprintf(stderr, "    [PILA DE ESTADOS]:");                                      \
    for (const yy_state_t *p = Bottom; p <= Top; p++) {                             \
        fprintf(stderr, " %d", (int)*p);                                            \
    }                                                                               \
    fprintf(stderr, "\n");                                                          \
} while (0)

#ifdef YY_SYMBOL_PRINT
#undef YY_SYMBOL_PRINT
#endif
#define YY_SYMBOL_PRINT(Title, Kind, Value, Location) do {                          \
    const char *t = Title;                                                          \
    if (strcmp(t, "Reading a token") == 0) t = "Leyendo token";                     \
    else if (strcmp(t, "Next token is") == 0) t = "Proximo token";                  \
    else if (strcmp(t, "Shifting") == 0) t = "Desplazando";                         \
    fprintf(stderr, "    [ACCION/SIMBOLO]: %s (Token ID: %d)\n", t, Kind);          \
} while (0)

void yyerror(const char *s) {
    fprintf(stderr, "\n[ERROR SINTACTICO] %s en linea %d.\n", s, yylineno);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        inputFile = fopen(argv[1], "r");
        if (!inputFile) {
            fprintf(stderr, "No se pudo abrir el archivo %s\n", argv[1]);
            return 1;
        }
    } else {
        fprintf(stderr, "Uso: ./compilador.exe <archivo_fuente>\n");
        return 1;
    }

    printf("====================================================\n");
    printf("   INICIO DEL ANALISIS SINTACTICO (DEBUG BISON)     \n");
    printf("====================================================\n\n");

    /* Activa la salida de las macros */
    yydebug = 1;

    int resultado = yyparse();
    fclose(inputFile);

    printf("\n====================================================\n");
    if (resultado == 0) {
        printf("   RESULTADO: COMPILACION EXITOSA                   \n");
        printf("====================================================\n");
        return 0;
    } else {
        printf("   RESULTADO: COMPILACION NO EXITOSA                \n");
        printf("====================================================\n");
        return 1;
    }
}