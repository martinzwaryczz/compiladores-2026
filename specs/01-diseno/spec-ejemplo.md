# Spec — Diseño del lenguaje MINI

**Grupo:** ejemplo de cátedra · **Lenguaje de implementación:** C  
**Estado:** cerrada. Todo cambio acá impacta en las specs de las fases siguientes.

---

## 1. Decisiones globales

| # | Decisión | Valor |
|---|---|---|
| D1 | Tipo de datos | Un solo tipo: entero con signo, 32 bits |
| D2 | Rango | −2.147.483.648 a 2.147.483.647 |
| D3 | Declaración | Obligatoria, debe preceder al primer uso |
| D4 | Alcance | Único y global: no hay variables locales |
| D5 | Sensibilidad a mayúsculas | Sí. `Total` y `total` son variables distintas |
| D6 | Longitud máxima de identificador | 20 caracteres; más largo se trunca con advertencia |
| D7 | Comentarios | De línea, `//` hasta fin de línea |
| D8 | Resultado de una comparación | No es un valor. Solo aparece en condiciones |
| D9 | División por cero | Error en ejecución, con mensaje y cancelación |
| D10 | Plataforma destino | x86-64, NASM sobre Linux |

---

## 2. Alfabeto

| Clase | Caracteres |
|---|---|
| `L` | `a`–`z`, `A`–`Z` |
| `D` | `0`–`9` |
| `SIM` | `+ - * / ( ) { } ; , = < > !` |
| `BL` | espacio, tabulador, salto de línea |
| `OTRO` | cualquier otro carácter → error léxico |

---

## 3. Palabras reservadas

`principal` · `entero` · `si` · `sino` · `mientras` · `mostrar`

Se reconocen como identificadores y se resuelven por búsqueda en tabla, no con
estados propios del autómata.

---

## 4. Tabla de tokens

| Código | Token | Lexema |
|---|---|---|
| 256 | `ID` | identificador |
| 257 | `CTE` | constante entera |
| 258 | `PRINCIPAL` | `principal` |
| 259 | `ENTERO` | `entero` |
| 260 | `SI` | `si` |
| 261 | `SINO` | `sino` |
| 262 | `MIENTRAS` | `mientras` |
| 263 | `MOSTRAR` | `mostrar` |
| 264 | `ASIG` | `=` |
| 265 | `IGUAL` | `==` |
| 266 | `DISTINTO` | `!=` |
| 267 | `MENOR` | `<` |
| 268 | `MAYOR` | `>` |
| — | literales | `+ - * / ( ) { } ; ,` se devuelven como su propio carácter |

---

## 5. Estructura del programa

Un programa MINI es **una sola función**, de nombre reservado `principal`, sin
parámetros y sin valor de retorno. No hay otras funciones.

---

## 6. Gramática

```
<programa>      ::= PRINCIPAL '(' ')' <bloque>

<bloque>        ::= '{' <sentencias> '}'

<sentencias>    ::= <sentencias> <sentencia>
                  | <sentencia>

<sentencia>     ::= <declaracion>
                  | <asignacion>
                  | <seleccion>
                  | <iteracion>
                  | <salida>

<declaracion>   ::= ENTERO <lista_ids> ';'
<lista_ids>     ::= <lista_ids> ',' ID
                  | ID

<asignacion>    ::= ID ASIG <expresion> ';'

<seleccion>     ::= SI '(' <condicion> ')' <bloque>
                  | SI '(' <condicion> ')' <bloque> SINO <bloque>

<iteracion>     ::= MIENTRAS '(' <condicion> ')' <bloque>

<salida>        ::= MOSTRAR '(' <expresion> ')' ';'

<condicion>     ::= <expresion> <comparador> <expresion>
<comparador>    ::= IGUAL | DISTINTO | MENOR | MAYOR

<expresion>     ::= <expresion> '+' <termino>
                  | <expresion> '-' <termino>
                  | <termino>

<termino>       ::= <termino> '*' <factor>
                  | <termino> '/' <factor>
                  | <factor>

<factor>        ::= ID
                  | CTE
                  | '(' <expresion> ')'
```

**Notas sobre la gramática**

- Recursión a izquierda en `<expresion>`, `<termino>` y `<sentencias>`: es la
  forma que prefiere una herramienta YACC.
- La precedencia queda resuelta por la estructura en tres niveles
  (`expresion` → `termino` → `factor`), no por declaraciones de precedencia.
- El `sino` colgante no existe como problema: `<bloque>` siempre lleva llaves.
- No hay `and` ni `or`: una condición es una sola comparación.

---

## 7. Semántica

| Regla | Definición |
|---|---|
| R1 | Usar un `ID` no declarado es error semántico |
| R2 | Declarar dos veces el mismo `ID` es error semántico |
| R3 | Toda variable se inicializa en 0 antes de la primera sentencia |
| R4 | Las constantes se registran en la tabla de símbolos con nombre `_valor` |
| R5 | Una constante fuera del rango D2 es error semántico, con línea |
| R6 | `mostrar` imprime el valor seguido de un salto de línea |

---

## 8. Responsabilidad de cada error

| Código | Descripción | Fase que lo detecta |
|---|---|---|
| E1 | Carácter fuera del alfabeto | Léxico |
| E2 | Constante mal formada (`12x`) | Léxico |
| E3 | Constante fuera de rango (R5) | Léxico |
| E4 | Sentencia mal formada | Sintáctico |
| E5 | Variable no declarada (R1) | Sintáctico (sobre tabla de símbolos) |
| E6 | Variable redeclarada (R2) | Sintáctico (sobre tabla de símbolos) |
| E7 | División por cero (D9) | Ejecución (código emitido por GCA) |

Ninguno de E1 a E6 aborta la compilación: se registran y se sigue leyendo.

---

## 9. Programa de ejemplo

```
principal() {
    entero n, acum;      // suma de 1 a n
    n = 5;
    acum = 0;
    mientras (n > 0) {
        acum = acum + n;
        n = n - 1;
    }
    si (acum > 10) {
        mostrar(acum);
    } sino {
        mostrar(0);
    }
}
```

Salida esperada: `15`

---

## 10. Fuera de alcance

Se deja constancia de lo que MINI **no** tiene, para que ninguna fase lo asuma:

- Reales, caracteres, cadenas, booleanos, arreglos
- Funciones definidas por el usuario, parámetros, recursión
- Variables locales y anidamiento de alcances
- `and`, `or`, negación
- Entrada de datos: no hay sentencia de lectura