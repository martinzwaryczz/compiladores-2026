# Spec — 04-analizador-sintactico

## Objetivo
Reconocer un lenguaje de entrada aplicando las reglas grámaticales correspondientes definidas en la [gramática](https://github.com/martinzwaryczz/compiladores-2026/blob/main/specs/01-diseno/spec.md#6-gram%C3%A1tica). El analizador lexico le brinda al analizador sintaxtico tokens con `yylex()`.

## Alcance

* Análisis sintáctico completo de un programa del lenguaje DUOTIPO según la GIC, implementado en `parser.y` (GNU Bison, LALR(1), salida en C).
* Reconocimiento de: estructura del programa (declaraciones globales, funciones y bloque `principal`), declaraciones de variables, sentencias (asignación, `escribir`, `retornar`, `mientras`, `segun`, llamada a función) y expresiones aritméticas, relacionales y lógicas.
* Notificación de errores sintácticos mediante `yyerror()`, con el número de línea.
* Traza de depuración de Bison (`%debug`), activada desde el `main` con `yydebug = 1`.
* Un `main` que abre el archivo fuente, invoca `yyparse()` y reporta el resultado.

## Entradas

* **Tira de Tokens:** Secuencia bajo demanda devuelta por `yylex()` con números entero 301-333, 335 337, finalizando con `0` para el fin de archivo (`EOF`).
* **Archivo fuente:** Código del lenguaje DUOTIPO abierto a través de `inputFile` (definido en el lexer, declarado como `extern` en el parser). Se recibe como primer argumento de línea de comandos: `./compilador.exe <archivo_fuente>`.
* **Información de contexto léxico:** Variable `yylineno` (definida en el lexer) para reportar la línea exacta ante fallas sintácticas.

## Salidas

* **Código de retorno del proceso:** `0` si el programa fuente es sintácticamente válido según la GIC; `1` si contiene errores sintácticos o léxicos, si no se pasa archivo o si el archivo no puede abrirse.
* **Mensajes por consola:**
  * Un encabezado de inicio (`INICIO DEL ANALISIS SINTACTICO (DEBUG BISON)`) y, al terminar, `RESULTADO: COMPILACION EXITOSA` o `RESULTADO: COMPILACION NO EXITOSA`.
  * Error sintáctico: `[ERROR SINTACTICO] syntax error en linea <yylineno>.`
  * Sin argumentos: `Uso: ./compilador.exe <archivo_fuente>`
  * Archivo inexistente: `No se pudo abrir el archivo <nombre>`
  * Traza de depuración: reducciones aplicadas (con número de regla y línea), pila de estados y tokens leídos/desplazados.  

* **Lista de reducciones / reglas:** Derivación ascendente procesada internamente por el autómata de pila LALR(1) para habilitar las etapas posteriores del compilador. LEE | APILA | APLICA DE SER POSIBLE UNA REDUCCIÓN.

## Reglas y decisiones de diseño

* **Generador de parser:** Empleo de GNU Bison operando en modo LALR(1) con salida en lenguaje C.
* **Coordinación de códigos de terminales:** Los identificadores de tokens en `%token` coinciden con los enteros asignados en la matriz de tokens del lexer.
* **Estructura del programa:** `programa → [declaraciones_globales] [funciones] principal`. El orden es fijo: primero las variables globales, luego las funciones y al final el bloque `principal`. Cada parte, salvo `principal`, es opcional.
* **Declaraciones:** `declaracion → tipo TK_ID` seguida de `;`, con `tipo entero o tipo real}`, se permite una variable por declaración.
* **Funciones:** `funcion tipo TK_ID ( ) { cuerpo }`. No admiten parámetros.
* **Bloque principal:** `principal { cuerpo }` o `principal ( ) { cuerpo }`.
* **Cuerpo (de función y de `principal`):** declaraciones locales opcionales seguidas de sentencias opcionales; el cuerpo vacío es válido. Las declaraciones locales deben ir antes de las sentencias.
* **Sentencias:**
  * Asignación: `TK_ID = expresion ;`
  * Salida: `escribir ( expresion ) ;`
  * Retorno: `retornar expresion ;`
  * Repetición: `mientras ( expresion ) { sentencias }` (_la condición es una expresión cualquiera_ y el cuerpo requiere al menos una sentencia).
  * Selección: `segun ( TK_ID ) { lista_casos [caso_defecto] }`, con al menos un `caso`; el `defecto` es opcional y, si está, va al final. Cada `caso` es `caso TK_NUM_INT : sentencias` y `defecto` es `defecto : sentencias`.
  * Llamada a función: `TK_ID ( ) ;`. Las llamadas no llevan argumentos y pueden usarse como operando dentro de una expresión.

* **Manejo de errores:** `yyerror(const char *s)` imprime por `[ERROR SINTACTICO] %s en linea %d.` (con `s = "syntax error"` y `yylineno`). No hay recuperación: `yyparse()` devuelve distinto de 0 y `main` informa **compilación no exitosa**.

* **Depuración:** `%debug` habilita las tablas de depuración de Bison y `main` fija `yydebug = 1`.

| Grupo | Tokens (código) |
|---|---|
| Palabras reservadas | `TK_ENTERO` 301, `TK_REAL` 302, `TK_FUNCION` 303, `TK_PRINCIPAL` 304, `TK_RETORNAR` 305, `TK_SEGUN` 306, `TK_CASO` 307, `TK_DEFECTO` 308, `TK_MIENTRAS` 309, `TK_AENTERO` 310, `TK_AREAL` 311, `TK_AND` 312 `TK_OR` 313, `TK_ESCRIBIR` 335 |
| Identificador y constantes | `TK_ID` 314, `TK_NUM_INT` 315, `TK_NUM_REAL` 316 |
| Operadores | `TK_ASSIGN` 317, `TK_PLUS` 318, `TK_MINUS` 319, `TK_MULT` 320, `TK_DIV` 321, `TK_LT` 322, `TK_GT` 323, `TK_NEQ` 324, `TK_LE` 325, `TK_GE` 326, `TK_EQ` 327 |
| Delimitadores y control | `TK_LPAREN` 328, `TK_RPAREN` 329, `TK_LBRACE` 330, `TK_RBRACE` 331, `TK_SEMI` 332, `TK_COLON` 333, `TK_DOT` 334, `TK_ERROR` 337 |


## Criterios de aceptación

- `bison -d parser.y` genera el parser sin errores y sin conflictos _shift/reduce ni reduce/reduce_.
- Un programa mínimo `principal { }` (cuerpo vacío) y su variante `principal ( ) { }` son aceptados: se informa `COMPILACION EXITOSA` y el proceso devuelve `0`.
- Un programa con declaraciones globales, una o más funciones y bloque `principal` con declaraciones locales y sentencias es aceptado.
- Se acepta `mientras` con condiciones que combinan `o`, `y`, comparaciones y paréntesis.
- Se aceptan `segun` con uno o más `caso` con y sin `defecto`.
- Se aceptan `aEntero(expresion)` y `aReal(expresion)` con una expresión como argumento.
- Se rechaza `segun` sin ningún `caso`.
- Se rechaza un programa con una declaración global después de una función, o con declaraciones locales después de una sentencia.
- Se rechaza (on `COMPILACION NO EXITOSA` y retorno `1` cada uno de los siguientes: falta de `;`, falta de `principal`, llamada con argumentos, función con parámetros, llave sin cerrar, `mientras` con cuerpo vacío.
- Ante un error sintáctico se emite `[ERROR SINTACTICO] syntax error en linea N.`, con `N` igual a la línea del token que causó el error.
- Sin argumentos se imprime el mensaje de uso y se devuelve `1`; con un archivo inexistente se imprime `No se pudo abrir el archivo <nombre>` y se devuelve `1`.
