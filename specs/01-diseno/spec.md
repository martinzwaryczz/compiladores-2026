# Spec — Diseño del lenguaje DUOTIPO

**Grupo:** E · **Lenguaje de implementación:** C (a confirmar por el grupo)
**Estado:** en revisión — primera versión completa a partir de la consigna.

---

## 1. Decisiones globales

| # | Decisión | Valor |
| --- | --- | --- |
| D1 | Tamaño de `int` | 32 bits, con signo |
| D2 | Tamaño de `real` | 64 bits |
| D3 | Sintaxis de conversión explícita | Funciones `toReal(x)` y `toInt(x)` (no se usa cast con paréntesis de tipo) |
| D4 | Comportamiento de `toInt(x)` sobre un real | **Truncamiento** hacia cero (se descarta la parte decimal, no se redondea) |
| D5 | Rango de `int` | `-2147483648 .. 2147483647` (complemento a 2, 32 bits) |
| D6 | Detección de real fuera de rango en `toInt` | Error semántico en tiempo de compilación **solo** si el real es una constante; si es una variable, error en tiempo de ejecución (se documenta igual como caso de `toInt`) |
| D7 | Memoria | Estática global; variables locales de función también estáticas |
| D8 | Recursión | **No permitida** (llamada recursiva directa es error semántico) |
| D9 | Parámetros de función | No existen; comunicación exclusivamente por variables globales |
| D10 | Valor de retorno de función | Obligatorio, de tipo declarado; no se permite retornar un tipo distinto sin conversión |
| D11 | Comentarios | `// comentario de línea` (no se pide en la consigna, pero se recomienda para legibilidad de los programas de prueba) |
| D12 | Bloque principal | El programa tiene un bloque `main { ... }` que se ejecuta al final, después de declarar globales y funciones |

---

## 2. Alfabeto

| Clase | Caracteres | Descripción |
| --- | --- | --- |
| Letras | `a`-`z`, `A`-`Z` | Forman identificadores y palabras reservadas |
| Dígitos | `0`-`9` | Forman constantes numéricas (enteras y reales) e identificadores a partir del segundo carácter |
| Identificador | letra seguida de letras, dígitos o `_` | Nombre de variable o función definido por el programador |
| Símbolos de operador | `+` `-` `*` `/` `=` `<` `>` `!` | Operadores aritméticos, de asignación y relacionales (algunos se combinan en pares, ej. `<=`, `==`, `!=`) |
| Símbolos de puntuación | `(` `)` `{` `}` `;` `,` `:` | Delimitan expresiones, bloques, sentencias y etiquetas de `case`/`default` |
| Separadores | espacio, tabulación, salto de línea | No significativos, solo separan tokens entre sí |
| Comentario | `//` hasta fin de línea | Ignorado por el analizador léxico, no genera token |
| OTRO | cualquier carácter no incluido en las clases anteriores | No reconocido: el analizador léxico lo reporta como error léxico con el número de línea |

No se admiten caracteres fuera de este alfabeto dentro de identificadores, números u operadores; su aparición es un error léxico con número de línea (clase `OTRO`).

---

## 3. Palabras reservadas

```
int  real  function  main  return
switch  case  default  while
toInt  toReal
and  or
```
---

## 4. Tabla de tokens

| Código | Nombre | Token | Lexema |
| --- | --- | --- | --- |
| 1 | TK_INT | tipo entero | `int` |
| 2 | TK_REAL | tipo real | `real` |
| 3 | TK_FUNCTION | declaración de función | `function` |
| 4 | TK_MAIN | bloque principal | `main` |
| 5 | TK_RETURN | retorno | `return` |
| 6 | TK_SWITCH | switch | `switch` |
| 7 | TK_CASE | case | `case` |
| 8 | TK_DEFAULT | default | `default` |
| 9 | TK_WHILE | while | `while` |
| 10 | TK_TOINT | conversión a entero | `toInt` |
| 11 | TK_TOREAL | conversión a real | `toReal` |
| 12 | TK_AND | conector lógico | `and` |
| 13 | TK_OR | conector lógico | `or` |
| 14 | TK_ID | identificador | letra (letra\|dígito\|`_`)* |
| 15 | TK_NUM_INT | constante entera | dígito+ |
| 16 | TK_NUM_REAL | constante real | dígito+ `.` dígito+ |
| 17 | TK_ASSIGN | asignación | `=` |
| 18 | TK_PLUS | suma | `+` |
| 19 | TK_MINUS | resta | `-` |
| 20 | TK_MULT | multiplicación | `*` |
| 21 | TK_DIV | división | `/` |
| 22 | TK_LT | menor | `<` |
| 23 | TK_GT | mayor | `>` |
| 24 | TK_LE | menor o igual | `<=` |
| 25 | TK_GE | mayor o igual | `>=` |
| 26 | TK_EQ | igual | `==` |
| 27 | TK_NEQ | distinto | `!=` |
| 28 | TK_LPAREN | paréntesis izq. | `(` |
| 29 | TK_RPAREN | paréntesis der. | `)` |
| 30 | TK_LBRACE | llave izq. | `{` |
| 31 | TK_RBRACE | llave der. | `}` |
| 32 | TK_SEMI | fin de sentencia | `;` |
| 33 | TK_COMMA | separador | `,` |
| 34 | TK_COLON | separador de etiqueta case/default | `:` |
| 35 | TK_EOF | fin de archivo | — |
| 36 | TK_OTRO | carácter no reconocido | error léxico |

---

## 5. Estructura del programa

```
<declaraciones globales>     // int/real a nivel global, antes de todo uso
<declaraciones de funciones> // cero o más, sin parámetros, retorno tipado
main {
    <declaraciones locales>
    <sentencias>
}
```

---

## 6. Gramática

```
<programa>            ::= <decl_globales> <decl_funciones> "main" "{" <decl_locales> <sentencias> "}"

<decl_globales>        ::= <decl_var> <decl_globales> | ε
<decl_locales>          ::= <decl_var> <decl_locales> | ε
<decl_var>              ::= <tipo> id ";"
<tipo>                   ::= "int" | "real"

<decl_funciones>        ::= <decl_funcion> <decl_funciones> | ε
<decl_funcion>           ::= "function" <tipo> id "(" ")" "{" <decl_locales> <sentencias> "}"

<sentencias>             ::= <sentencia> <sentencias> | ε
<sentencia>              ::= <asignacion>
                            | <switch>
                            | <while>
                            | <retorno>
                            | <llamada_funcion> ";"

<asignacion>             ::= id "=" <expresion> ";"

<retorno>                ::= "return" <expresion> ";"

<llamada_funcion>        ::= id "(" ")"

<switch>                 ::= "switch" "(" id ")" "{" <lista_case> <default> "}"
<lista_case>              ::= <case> <lista_case> | ε
<case>                    ::= "case" num_int ":" <sentencias>
<default>                 ::= "default" ":" <sentencias>

<while>                   ::= "while" "(" <condicion> ")" "{" <sentencias> "}"

<condicion>               ::= <condicion> "and" <cond_and>
                             | <cond_and>
<cond_and>                ::= <cond_and> "or" <cond_prim>
                             | <cond_prim>
<cond_prim>                ::= "(" <condicion> ")" | <comparacion>
<comparacion>               ::= <expresion> <op_rel> <expresion>
<op_rel>                    ::= "<" | ">" | "<=" | ">=" | "==" | "!="

<expresion>               ::= <expresion> "+" <termino>
                             | <expresion> "-" <termino>
                             | <termino>
<termino>                  ::= <termino> "*" <factor>
                             | <termino> "/" <factor>
                             | <factor>
<factor>                   ::= id
                             | num_int
                             | num_real
                             | "toInt" "(" <expresion> ")"
                             | "toReal" "(" <expresion> ")"
                             | "(" <expresion> ")"
                             | <llamada_funcion>
```


## 7. Semántica

**Tabla de compatibilidad de tipos** (operaciones aritméticas, asignación y comparación):

| Operando A | Operando B | ¿Válido sin conversión? |
| --- | --- | --- |
| `int` | `int` | Sí |
| `real` | `real` | Sí |
| `int` | `real` | No — requiere `toReal(int)` o `toInt(real)` explícito |
| `real` | `int` | No — requiere `toReal(int)` o `toInt(real)` explícito |


| S1 | Toda variable usada debe haber sido declarada antes, en el alcance global o en el alcance local de la función/`main` donde se usa |
| S2 | Una asignación `id = expresion` exige `tipo(id) == expresion.tipo`; en caso contrario, error semántico |
| S3 | Una operación aritmética entre operandos de distinto tipo (`int` y `real` sin `toInt`/`toReal`) es error semántico |
| S4 | Una comparación entre operandos de distinto tipo es error semántico |
| S5 | El selector de un `switch` debe ser de tipo `int` |
| S6 | Las etiquetas de `case` deben ser constantes enteras, sin repetirse dentro del mismo `switch` |
| S7 | `return expresion` debe coincidir con el tipo declarado de la función; retornar `real` en una función `int` (o viceversa) sin conversión explícita es error semántico |
| S8 | Una función no puede invocarse a sí misma, ni directa ni (fuera de alcance, ver §10) indirectamente — solo se exige detectar la directa |
| S9 | `toInt(real)` sobre una constante real fuera del rango de `int` (§1, decisión 5) es error semántico |


---

## 8. Responsabilidad de cada error

| Código | Descripción | Fase que lo detecta |
| --- | --- | --- |
| L01 | Carácter fuera del alfabeto / token mal formado | Léxico |
| P01 | Token inesperado / estructura sintáctica inválida | Sintáctico |
| E01 | Mezcla de `int` y `real` en operación aritmética o asignación sin conversión explícita | Semántico |
| E02 | Comparación entre operandos de distinto tipo sin conversión explícita | Semántico |
| E03 | Selector de `switch` no es de tipo `int` | Semántico |
| E04 | Etiquetas de `case` repetidas dentro del mismo `switch` | Semántico |
| E05 | Uso de variable no declarada, o uso antes de su declaración | Semántico |
| E06 | Tipo de retorno de la función no coincide con el declarado | Semántico |
| E07 | Llamada recursiva directa de una función | Semántico |
| E08 | `toInt` sobre constante real fuera del rango de `int` | Semántico |


## 9. Programa de ejemplo

```
int contador;
real total;

function real promedio() {
    real resultado;
    resultado = total / toReal(contador);
    return resultado;
}

main {
    int i;
    real acumulado;

    contador = 0;
    total = 0.0;
    i = 0;

    while (i < 5) {
        contador = contador + 1;
        total = total + toReal(contador);
        i = i + 1;
    }

    switch (contador) {
        case 5:
            acumulado = promedio();
        default:
            acumulado = 0.0;
    }
}
```


---

## 10. Fuera de alcance

- FALTA
