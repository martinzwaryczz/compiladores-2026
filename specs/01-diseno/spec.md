# Spec — Diseño del lenguaje DUOTIPO

**Grupo:** E · **Lenguaje de implementación:** C 
**Estado:** en revisión — primera versión completa a partir de la consigna.

---

## 1. Decisiones globales

| # | Decisión | Valor |
| --- | --- | --- |
| D1 | Tamaño de `int` | 32 bits |
| D2 | Tamaño de `real` | 64 bits |
| D3 | Sintaxis de conversión explícita | Funciones `aReal(x)` y `aEntero(x)` |
| D4 | Comportamiento de `aEntero(x)` sobre un real |
| D5 | Rango de `int` | `-2147483648 .. 2147483647` (complemento a 2, 32 bits) |
| D6 | Detección de real fuera de rango en `aEntero` | Error semántico en tiempo de compilación **solo** si el real es una constante; si es una variable, error en tiempo de ejecución |
| D7 | Memoria | Estática global; variables locales de función también estáticas |  
| D8 | Recursión | **No permitida** (ERROR SEMANTICO) |
| D9 | Parámetros de función | No permitidos | 
| D10 | Valor de retorno de función | Obligatorio, de tipo declarado; no se permite retornar un tipo distinto sin conversión |
| D11 | Comentarios | /* */ comentario de línea` (no pedido realmente) |
| D12 | Bloque principal | El programa tiene un bloque `principal { ... }` que se ejecuta al final, después de declarar globales y funciones |

---

## 2. Alfabeto

| Clase | Caracteres | Descripción |
| --- | --- | --- |
| Letras | `a`-`z`, `A`-`Z` | Forman identificadores y palabras reservadas |
| Dígitos | `0`-`9` | Forman constantes numéricas (enteras y reales) e identificadores a partir del segundo carácter |
| Identificador | letra seguida de letras, dígitos o `_` | Nombre de variable o función definido por el programador |
| Símbolos de operador | `+` `-` `*` `/` `=` `<` `>` `!` | Operadores aritméticos, de asignación y relacionales (algunos se combinan en pares, ej. `<=`, `==`, `!=`) |
| Símbolos de puntuación | `(` `)` `{` `}` `;` `,` `:` | Delimitan expresiones, bloques, sentencias y etiquetas de `caso`/`defecto` |
| Separadores | espacio, tabulación, salto de línea | No significativos, solo separan tokens entre sí |
| Comentario | `/* */` hasta fin de línea | Ignorado por el analizador léxico, no genera token |
| OTRO | cualquier carácter no incluido en las clases anteriores | No reconocido: el analizador léxico lo reporta como error léxico con el número de línea |

No se admiten caracteres fuera de este alfabeto dentro de identificadores, números u operadores; su aparición es un error léxico con número de línea (clase **`OTRO`**).

---

## 3. Palabras reservadas

```
entero  real  funcion  principal  retornar
segun  caso  defecto  mientras
aEntero  aReal
y  o
```
---

## 4. Tabla de tokens

| Código | Nombre | Token | Lexema |
| --- | --- | --- | --- |
| 1 | TK_INT | tipo entero | `entero` |
| 2 | TK_REAL | tipo real | `real` |
| 3 | TK_FUNCTION | declaración de función | `funcion` |
| 4 | TK_MAIN | bloque principal | `principal` |
| 5 | TK_RETURN | retorno | `retornar` |
| 6 | TK_SWITCH | segun | `segun` |
| 7 | TK_CASE | caso | `caso` |
| 8 | TK_DEFAULT | defecto | `defecto` |
| 9 | TK_WHILE | mientras | `mientras` |
| 10 | TK_TOINT | conversión a entero | `aEntero` |
| 11 | TK_TOREAL | conversión a real | `aReal` |
| 12 | TK_AND | conector lógico | `y` |
| 13 | TK_OR | conector lógico | `o` |
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
| 34 | TK_COLON | separador de etiqueta caso/defecto | `:` |
| 35 | TK_EOF | fin de archivo | — |
| 36 | TK_OTRO | carácter no reconocido | error léxico |

---

## 5. Estructura del programa

```
<declaraciones globales>     
<declaraciones de funciones> 
principal {
    <declaraciones locales>
    <sentencias>
}
```

---

## 6. Gramática

**2/9/2026: Gramatica hecha con Claude, revisar y re-hacer.**
```
<programa>            ::= <decl_globales> <decl_funciones> "principal" "{" <decl_locales> <sentencias> "}"

<decl_globales>        ::= <decl_var> <decl_globales> | λ
<decl_locales>          ::= <decl_var> <decl_locales> | λ
<decl_var>              ::= <tipo> id ";"
<tipo>                   ::= "entero" | "real"

<decl_funciones>        ::= <decl_funcion> <decl_funciones> | λ
<decl_funcion>           ::= "funcion" <tipo> id "(" ")" "{" <decl_locales> <sentencias> "}"

<sentencias>             ::= <sentencia> <sentencias> | λ
<sentencia>              ::= <asignacion>
                            | <segun>
                            | <mientras>
                            | <retorno>
                            | <llamada_funcion> ";"

<asignacion>             ::= id "=" <expresion> ";"

<retorno>                ::= "retornar" <expresion> ";"

<llamada_funcion>        ::= id "(" ")"

<segun>                   ::= "segun" "(" id ")" "{" <lista_caso> <defecto> "}"
<lista_caso>               ::= <caso> <lista_caso> | λ
<caso>                     ::= "caso" num_int ":" <sentencias>
<defecto>                  ::= "defecto" ":" <sentencias>

<mientras>                ::= "mientras" "(" <condicion> ")" "{" <sentencias> "}"

<condicion>               ::= <condicion> "y" <cond_y>
                             | <cond_y>
<cond_y>                  ::= <cond_y> "o" <cond_prim>
                             | <cond_prim>
<cond_prim>                ::= "(" <condicion> ")" | <comparacion>
<comparacion>               ::= <expresion> <op_rel> <expresion>
<op_rel>                    ::= "<" | ">" | "<=" | ">=" | "==" | "!="

<expresion>               ::= <expresion> "+" <termino>
                             | <expresion> "-" <termino>
                             | <termino>
<termino>                  ::= <termino> "*" <termino_n>
                             | <termino> "/" <termino_n>
                             | <atomo>
<termino_n>                     ::= id
                             | num_int
                             | num_real
                             | "aEntero" "(" <expresion> ")"
                             | "aReal" "(" <expresion> ")"
                             | "(" <expresion> ")"
                             | <llamada_funcion>
```


## 7. Semántica

**Tabla de compatibilidad de tipos** (operaciones aritméticas, asignación y comparación):

**Tabla de compatibilidad de tipos** (operaciones aritméticas, asignación y comparación):

| Operando A | Operando B | ¿Válido sin conversión? |
| --- | --- | --- |
| `entero` | `entero` | Sí |
| `real` | `real` | Sí |
| `entero` | `real` | No — requiere `aReal(entero)` o `aEntero(real)` explícito |
| `real` | `entero` | No — requiere `aReal(entero)` o `aEntero(real)` explícito |

| Regla | Definición |
| --- | --- |
| S1 | Toda variable usada debe haber sido declarada antes, en el alcance global o en el alcance local de la función/`principal` donde se usa |
| S2 | Una asignación `id = expresion` exige `tipo(id) == expresion.tipo`; en caso contrario, error semántico |
| S3 | Una operación aritmética entre operandos de distinto tipo (`entero` y `real` sin `aEntero`/`aReal`) es error semántico |
| S4 | Una comparación entre operandos de distinto tipo es error semántico |
| S5 | El selector de un `segun` debe ser de tipo `entero` |
| S6 | Las etiquetas de `caso` deben ser constantes enteras, sin repetirse dentro del mismo `segun` |
| S7 | `retornar expresion` debe coincidir con el tipo declarado de la función; retornar `real` en una función `entero` (o viceversa) sin conversión explícita es error semántico |
| S8 | Una función no puede invocarse a sí misma, ni directa ni (fuera de alcance, ver §10) indirectamente — solo se exige detectar la directa |
| S9 | `aEntero(real)` sobre una constante real fuera del rango de `entero` (§1, decisión D5) es error semántico |

---


| Regla | Definición |
| --- | --- |
| S1 | Toda variable usada debe haber sido declarada antes, en el alcance global o en el alcance local de la función/`principal` donde se usa |
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
| E01 | Mezcla de `entero` y `real` en operación aritmética o asignación sin conversión explícita | Semántico |
| E02 | Comparación entre operandos de distinto tipo sin conversión explícita | Semántico |
| E03 | Selector de `segun` no es de tipo `entero` | Semántico |
| E04 | Etiquetas de `caso` repetidas dentro del mismo `segun` | Semántico |
| E05 | Uso de variable no declarada, o uso antes de su declaración | Semántico |
| E06 | Tipo de retorno de la función no coincide con el declarado | Semántico |
| E07 | Llamada recursiva directa de una función | Semántico |
| E08 | `aEntero` sobre constante real fuera del rango de `entero` | Semántico |


## 9. Programas de ejemplo

```
entero contador;
entero suma;

principal {
    contador = 1;
    suma = 0;

    mientras (contador <= 5) {
        suma = suma + contador;
        contador = contador + 1;
    }
}
```


```
entero diaSemana;
entero esFinDeSemana;

principal {
    diaSemana = 6;

    segun (diaSemana) {
        caso 6:
            esFinDeSemana = 1;
        caso 7:
            esFinDeSemana = 1;
        defecto:
            esFinDeSemana = 0;
    }
}
```

```
entero cantidad;
real precioUnitario;
real total;

principal {
    cantidad = 4;
    precioUnitario = 250.5;
    total = aReal(cantidad) * precioUnitario;
}
```
