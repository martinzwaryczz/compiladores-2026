# Spec — 04-analizador-sintactico

## Objetivo
Reconocer un lenguaje de entrada aplicando las reglas grámaticales correspondientes definidas en la [gramática](https://github.com/martinzwaryczz/compiladores-2026/blob/main/specs/01-diseno/spec.md#6-gram%C3%A1tica). El analizador sintactico le brinda al analizador sintaxtico tokens con `yylex()`.

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

* **CA-01 (Aceptación de programa válido):** Un archivo con funciones, bloque `principal`, declaraciones iniciales, estructuras de control (`mientras`, `segun`) y asignaciones válidas finaliza con éxito retornando `1`.
* **CA-02 (Rechazo por falta de delimitador):** Una sentencia que omita el punto y coma final (`;`) es rechazada, emitiendo el mensaje de error sintáctico con la línea correspondiente y retornando `0`.
* **CA-03 (Rechazo por orden de declaraciones):** Cualquier declaración de variable ubicada con posterioridad a una sentencia ejecutable dentro de un mismo bloque es rechazada gramaticalmente retornando `0`.
* **CA-04 (Rechazo de sintaxis en `segun`):** Una estructura `segun` sin la rama `defecto:` es rechazada por no cumplir la regla gramatical establecida.
* **CA-05 (Balanceo de delimitadores):** Expresiones aritméticas o condiciones lógicas con paréntesis desbalanceados disparan inmediatamente `yyerror()` y detienen el análisis con retorno `0`.
* **CA-06 (Integración limpia con el lexer):** El parser consume los tokens sin inconsistencias de símbolos terminales y reconoce adecuadamente el token `0` como cierre de entrada.
