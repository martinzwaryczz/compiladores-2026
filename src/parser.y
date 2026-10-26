%{
#include <stdio.h>
#include <stdlib.h>

/* Prototipos externos para comunicar con lexer.c */
extern int yylex(void);
extern int yylineno;
extern FILE *inputFile;
extern int error;

void yyerror(const char *s);
%}

/* =============================================================
 * 1. Declaracion de Tokens con sus codigos numericos (301..334)
 * ============================================================= */

/* Palabras reservadas */
%token TK_INT            301   /* entero */
%token TK_REAL           302   /* real */
%token TK_FUNCTION       303   /* funcion */
%token TK_MAIN           304   /* principal */
%token TK_RETURN         305   /* retornar */
%token TK_SWITCH         306   /* segun */
%token TK_CASE           307   /* caso */
%token TK_DEFAULT        308   /* defecto */
%token TK_WHILE          309   /* mientras */
%token TK_TOINT          310   /* aEntero */
%token TK_TOREAL         311   /* aReal */
%token TK_AND            312   /* y */
%token TK_OR             313   /* o */

/* Identificadores y constantes */
%token TK_ID             314   /* identificador */
%token TK_NUM_INT        315   /* constante entera */
%token TK_NUM_REAL       316   /* constante real */

/* Operadores aritmeticos y asignacion */
%token TK_ASSIGN         317   /* = */
%token TK_PLUS           318   /* + */
%token TK_MINUS          319   /* - */
%token TK_MULT           320   /* * */
%token TK_DIV            321   /* / */

/* Operadores relacionales */
%token TK_LT             322   /* < */
%token TK_GT             323   /* > */
%token TK_LE             324   /* <= */
%token TK_GE             325   /* >= */
%token TK_EQ             326   /* == */
%token TK_NEQ            327   /* != */

/* Delimitadores */
%token TK_LPAREN         328   /* ( */
%token TK_RPAREN         329   /* ) */
%token TK_LBRACE         330   /* { */
%token TK_RBRACE         331   /* } */
%token TK_SEMI           332   /* ; */
%token TK_COLON          334   /* : */

/* Precedencia auxiliar para el operador menos unario */
%token UMINUS
%right UMINUS

/* Simbolo inicial de la gramatica */
%start programa

%%

/* =============================================================
 * 2. Gramatica formal DUOTIPO (Seccion 6 del Spec)
 * ============================================================= */

programa
    : declaraciones_iniciales TK_MAIN TK_LBRACE bloque_principal TK_RBRACE
    | TK_MAIN TK_LBRACE bloque_principal TK_RBRACE
    ;

declaraciones_iniciales
    : decl_globales
    | decl_funciones
    | decl_globales decl_funciones
    ;

bloque_principal
    : decl_locales sentencias
    | sentencias
    ;

decl_globales
    : decl_globales decl_var
    | decl_var
    ;

decl_locales
    : decl_locales decl_var
    | decl_var
    ;

decl_var
    : tipo TK_ID TK_SEMI
    ;

tipo
    : TK_INT
    | TK_REAL
    ;

decl_funciones
    : decl_funciones decl_funcion
    | decl_funcion
    ;

decl_funcion
    : TK_FUNCTION tipo TK_ID TK_LPAREN TK_RPAREN TK_LBRACE bloque_funcion TK_RBRACE
    ;

bloque_funcion
    : decl_locales sentencias
    | sentencias
    ;

sentencias
    : sentencias sentencia
    | sentencia
    ;

sentencia
    : asignacion
    | segun
    | mientras
    | retorno
    | llamada_funcion TK_SEMI
    ;

asignacion
    : TK_ID TK_ASSIGN expresion TK_SEMI
    ;

retorno
    : TK_RETURN expresion TK_SEMI
    ;

llamada_funcion
    : TK_ID TK_LPAREN TK_RPAREN
    ;

segun
    : TK_SWITCH TK_LPAREN TK_ID TK_RPAREN TK_LBRACE casos defecto TK_RBRACE
    | TK_SWITCH TK_LPAREN TK_ID TK_RPAREN TK_LBRACE defecto TK_RBRACE
    ;

casos
    : casos caso
    | caso
    ;

caso
    : TK_CASE TK_NUM_INT TK_COLON sentencias
    ;

defecto
    : TK_DEFAULT TK_COLON sentencias
    ;

mientras
    : TK_WHILE TK_LPAREN condicion TK_RPAREN TK_LBRACE sentencias TK_RBRACE
    ;

condicion
    : condicion TK_OR cond_y
    | cond_y
    ;

cond_y
    : cond_y TK_AND cond_prim
    | cond_prim
    ;

cond_prim
    : TK_LPAREN condicion TK_RPAREN
    | comparacion
    ;

comparacion
    : expresion op_rel expresion
    ;

op_rel
    : TK_LT
    | TK_GT
    | TK_LE
    | TK_GE
    | TK_EQ
    | TK_NEQ
    ;

expresion
    : expresion TK_PLUS termino
    | expresion TK_MINUS termino
    | termino
    ;

termino
    : termino TK_MULT termino_n
    | termino TK_DIV termino_n
    | termino_n
    ;

termino_n
    : TK_MINUS termino_n %prec UMINUS
    | TK_ID
    | TK_NUM_INT
    | TK_NUM_REAL
    | TK_TOINT TK_LPAREN expresion TK_RPAREN
    | TK_TOREAL TK_LPAREN expresion TK_RPAREN
    | TK_LPAREN expresion TK_RPAREN
    | llamada_funcion
    ;

%%

/* =============================================================
 * 3. Rutinas auxiliares en C (yyerror y main)
 * ============================================================= */

void yyerror(const char *s) {
    fprintf(stderr, "\nError sintactico (P01): %s en linea %d.\n", s, yylineno);
    error = 1;
}

int main(int argc, char *argv[]) {
    const char *nombre_archivo = "prueba.txt";

    if (argc > 1) {
        nombre_archivo = argv[1];
    }

    if ((inputFile = fopen(nombre_archivo, "r")) == NULL) {
        fprintf(stderr, "Error al abrir el archivo de entrada: %s\n", nombre_archivo);
        return 1;
    }

    /* Ejecuta el analisis sintactico invocando yylex() */
    int resultado = yyparse();

    fclose(inputFile);

    if (resultado == 0 && error == 0) {
        printf("\n- Analisis Sintactico y Lexico EXITOSO -\n");
        return 0;
    } else {
        printf("\n- Se encontraron ERRORES durante la compilacion -\n");
        return 1;
    }
}