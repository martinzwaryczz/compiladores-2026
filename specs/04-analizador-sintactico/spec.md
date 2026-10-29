# Spec — 04-analizador-sintactico

## Objetivo
Reconocer un lenguaje de entrada aplicando las reglas grámaticales correspondientes definidas en la [gramática](https://github.com/martinzwaryczz/compiladores-2026/blob/main/specs/01-diseno/spec.md#6-gram%C3%A1tica). El analizador lexico le brinda al analizador sintaxtico tokens con `yylex()`.

## Alcance
Si es lenguajes es reconocido por la GIC devolverá 1, sino 0. 

En caso de un error sintaxtico lo notificará `yyerror()`.

## Entradas

* **Tira de Tokens:** Secuencia bajo demanda devuelta por `yylex()` con códigos numéricos $\ge 301$ ($301 \dots 334$), finalizando con `0` para el fin de archivo (`EOF`).
* **Archivo fuente:** Código del lenguaje DUOTIPO abierto a través del descriptor `inputFile`.
* **Información de contexto léxico:** Variable `yylineno` para reportar la línea exacta ante eventuales fallas sintácticas.
  
## Salidas

* **Código de retorno del proceso:** Entero devuelto por la aplicación (`1` si el programa fuente es sintácticamente válido según la GIC, `0` si contiene errores sintácticos o léxicos).
* **Mensajes de diagnóstico:** En caso de discrepancia sintáctica, notificación estándar por `stderr` con formato:  
  `Error sintactico (P01): syntax error en linea <yylineno>.`
* **Lista de reducciones / reglas:** Derivación ascendente procesada internamente por el autómata de pila LALR(1) para habilitar las etapas posteriores del compilador.

## Reglas y decisiones de diseño

* **Generador de parser:** Empleo de GNU Bison operando en modo LALR(1) con salida en lenguaje C.
* **Coordinación de códigos de terminales:** Los identificadores de tokens en `%token` coinciden exactamente con los enteros asignados en la matriz de tokens del lexer, los mismos que estan en el [spec de diseño]([url](https://github.com/martinzwaryczz/compiladores-2026/blob/main/specs/01-diseno/spec.md)) inicial.
* El menos unario se declara en `termino_n` empleando **%prec UMINUS** para asociar por derecha.
## Criterios de aceptación

