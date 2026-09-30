# Spec — Diseño del lenguaje DUOTIPO

**Grupo:** E 

**Lenguaje de implementación:** C 

**Estado:**

---

## 1. Decisiones globales

| # | Decisión | Valor |
| --- | --- | --- |
| D1 | Tamaño de `entero` | 32 bits |
| D2 | Tamaño de `real` | 32 bits |
| D3 | Sintaxis de conversión explícita | Funciones `aReal(x)` y `aEntero(x)` |
| D4 | Comportamiento de `aEntero(x)` sobre un real | Truncamiento
| D5 | Rango de `entero` | `-2147483648 .. 2147483647` (complemento a 2, 32 bits) |
| D6 | Detección de real fuera de rango en `aEntero` | Error semántico en tiempo de compilación **solo si el real es una constante**, si es una variable el error será en tiempo de ejecución |
| D7 | Memoria | Estática global, variables locales de función también estáticas |  
| D8 | Recursión | **No permitida** |
| D9 | Declaración de variables y funciones | Las variables deben ser declaradas con su tipo antes de su primer uso
| D10 | Variables en funciones | Las variables podrán ser declaradas dentro de las funciones |
| D11 | Parámetros de función | No permitidos | 
| D12 | Valor de retorno de función | Obligatorio, de tipo declarado; no se permite retornar un tipo distinto sin conversión |
| D13 | Comparaciones | Las comparaciones deben ser entre tipos iguales |
| D13 | Comentarios | /* */ comentario de línea` |
| D14 | Bloque principal | El programa tiene un bloque `principal { ... }` que se ejecuta al final, después de declarar globales y funciones |

---

## 2. Alfabeto

| Clase | Caracteres | Descripción |
| --- | --- | --- |
| Letras | `a`-`z`, `A`-`Z` | Forman identificadores y palabras reservadas |
| Dígitos | `0`-`9` | Forman constantes numéricas (enteras y reales) e identificadores si están luego de una letra |
| Símbolos de operador | `+` `-` `*` `/` `=` `<` `>` `!` | Operadores aritméticos, de asignación y relacionales |
| Símbolos de puntuación | `(` `)` `{` `}` `;` `:` `.` | Delimitan expresiones, bloques, sentencias, etiquetas de `caso`/`defecto` y separan la parte entera de la decimal en números reales |
| Separadores | espacio, tabulación, salto de línea | Separan tokens entre sí |
| OTRO | cualquier carácter no incluido en las clases anteriores | Error léxico |

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
| 15 | TK_NUM_INT | constante entera | dígito |
| 16 | TK_NUM_REAL | constante real | dígito `.` dígito |
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
| 28 | TK_LPAREN | paréntesis izquierda | `(` |
| 29 | TK_RPAREN | paréntesis derecha | `)` |
| 30 | TK_LBRACE | llave izquierda | `{` |
| 31 | TK_RBRACE | llave derecha | `}` |
| 32 | TK_SEMI | fin de sentencia | `;` |
| 34 | TK_COLON | separador de etiqueta caso/defecto | `:` |
| 37 | TK_OTRO | carácter no reconocido | error léxico |

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

```
<programa>  →  <declaraciones_iniciales> "principal" "{" <bloque_principal> "}"
                            | "principal" "{" <bloque_principal> "}"

<declaraciones_iniciales>  → <decl_globales>
                                                | <decl_funciones>
                                                | <decl_globales> <decl_funciones>

<bloque_principal>  → <decl_locales> <sentencias> | <sentencias>

<decl_globales>   → <decl_globales> <decl_var> | <decl_var>

<decl_locales>   → <decl_locales> <decl_var> | <decl_var>

<decl_var>          → <tipo> identificador ";"

<tipo>  → "entero" | "real"

<decl_funciones> → <decl_funciones> <decl_funcion>
                                   | <decl_funcion>

<decl_funcion>  →  "funcion" <tipo> identificador "(" ")" "{" <bloque_funcion> "}"

<bloque_funcion> → <decl_locales> <sentencias>
                                  | <sentencias>

<sentencias> → <sentencias> <sentencia> | <sentencia>

<sentencia>   → <asignacion>
                            | <segun>
                            | <mientras>
                            | <retorno>
                            | <llamada_funcion> ";"

<asignacion>  → identificador "=" <expresion> ";"

<retorno>  → "retornar" <expresion> ";"

<llamada_funcion>   → identificador "(" ")"

<segun>  → "segun" "(" identificador ")" "{" <casos> <defecto> "}"
                    | "segun" "(" identificador ")" "{" <defecto> "}"

<casos>               → <casos> <caso>
                             | <caso>

<caso>                   → "caso" numero_entero ":" <sentencias>
<defecto>              → "defecto" ":" <sentencias>

<mientras> → "mientras" "(" <condicion> ")" "{" <sentencias> "}"

<condicion>  → <condicion> "o" <cond_y>
                          | <cond_y>

<cond_y>  → <cond_y> "y" <cond_prim>
                       | <cond_prim>

<cond_prim>   → "(" <condicion> ")"
                              | <comparacion>

<comparacion>  → <expresion> <op_rel> <expresion>

<op_rel> → "<" | ">" | "<=" | ">=" | "==" | "!="

<expresion> → <expresion> "+" <termino>
                          | <expresion> "-" <termino>
                          | <termino>

<termino>    → <termino> "*" <termino_n>
                          | <termino> "/" <termino_n>
                          | <termino_n>

<termino_n>  → "-" <termino_n>
                             | identificador
                             | numero_entero
                             | numero_real
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
| S8 | Una función no puede invocarse a sí misma, ni directa ni indirectamente — solo se exige detectar la directa |
| S9 | `aEntero(real)` sobre una constante real fuera del rango de `entero` es error semántico |

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
| S8 | Una función no puede invocarse a sí misma |
| S9 | `toInt(real)` sobre una constante real fuera del rango de `int` es error semántico |


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
entero cantidad;
real precioUnitario;
real total;

principal {
    cantidad = 4;
    precioUnitario = 250.5;
    total = aReal(cantidad) * precioUnitario;
}

```

```
entero baseCalculo;
real resultadoGlobal;

funcion real calcularImpuesto() {
    real tasa;
    real subtotal;

    tasa = 0.21;
    subtotal = aReal(baseCalculo);
    retornar subtotal * tasa;
}

principal {
    baseCalculo = 500;
    resultadoGlobal = calcularImpuesto();
}

```

## Automata

<img width="2789" height="1343" alt="AUTOMATA_COMPILADORES-compilador v 2 (1)" src="https://github.com/user-attachments/assets/dd5ee0b6-1da3-42bb-8378-fdd7ba8c5357" />

## Matrices

### Matriz de punteros a las funciones_

| Estado | Código | letra | digito | = | + | - | * | / | < | > | ! | ( | ) | { | } | : | . | _ | B/ tab |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| estado inicial | E0 | f1 | f2 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| palabra | E1 | f3 | f3 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f3 | f5 |
| id | E2 | f3 | f3 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | f3 | fn |
| id | E2bis | f3 | f3 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | f3 | fn |
| asigancion | E3 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| igualdad | E4 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| suma | E5 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| resta | E6 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| multiplicación | E7 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| división | E8 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| mayor | E9 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| mayor o igual | E10 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| menor | E11 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| menor o igual | E12 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| posible distinto | E13 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| distinto | E14 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| parentesis izq. | E15 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| parentesis der. | E16 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| llaves izq. | E17 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| llave der. | E18 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| fin sentencia | E19 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| separador | E21 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| posible fin de archivo | E22 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| comentario | E23 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| posible fin comentari | E24 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| entero | E25 | f5 | f4 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | fn | f4 |
| real | E26 | f5 | f4 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | fn | f5 |
| Estado Final | EF | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |

### Rutinas semánticas:

#### **f1: Cuando se recibe una letra en el estado E0**
* Iniciar un string con la letra
* Iniciar contador de tamaño máximo de identificadores

---

#### **f2: Cuando se recibe un dígito en el estado E0**
* Iniciar una constante con ese dígito
* Verificar tamaño de la constante

---

#### **f3: Cuando se recibe un caracter en el estado E1, E2, E2bis**
* Si los identificadores tienen un largo máximo iniciar contador:
  * Incrementar el contador Ó
  * Si se excedió el largo máximo:
    * Terminar
* Agregar el caracter al string

---

#### **f4: Cuando se recibe un digito ó punto en E25 o E26**
* Si las ctes. tienen un largo máximo:
  * Incrementar el contador Ó
  * Si se excedió el largo máximo: Terminar
* Agregar el caracter al string

---

#### **f5: Cuando no se recibe un dígito en el estado E25**
* Verificar si la constante ya está almacenada
* Si no está almacenada - Guardar la constante (numérica) *(Ídem identificador)*

---

#### **fn: Resto de los casos**
* No hacer nada

### Matriz de nuevos estados

| Estado | Código | letra | digito | = | + | - | * | / | < | > | ! | ( | ) | { | } | : | . | _ | B/ tab |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| estado inicial | E0 | E1 | E25 | E3 | E5 | E6 | E7 | E8 | E9 | E11 | E13 | E15 | E16 | E17 | E18 | E19 | E21 | -2 | -2 | -1 |
| palabra | E1 | E1 | E2 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | E2bis | -1 | -1 |
| id | E2 | E2 | E2 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | E2 | -1 | -1 |
| id | E2bis | E2bis | E2bis | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | E2bis | -1 | -1 |
| asigancion | E3 | -1 | -1 | E4 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | E3 |
| igualdad | E4 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| suma | E5 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| resta | E6 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| multiplicación | E7 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| división | E8 | -1 | -1 | -1 | -1 | -1 | E23 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | E8 |
| mayor | E9 | -1 | -1 | E10 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | E9 |
| mayor o igual | E10 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| menor | E11 | -1 | -1 | E12 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | E11 |
| menor o igual | E12 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| posible distinto | E13 | -2 | -2 | E14 | -2 | -2 | -2 | -2 | -2 | -2 | -2 | -2 | -2 | -2 | -2 | -2 | -2 | -2 | -2 | E13 |
| distinto | E14 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| parentesis izq. | E15 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| parentesis der. | E16 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| llaves izq. | E17 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| llave der. | E18 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| fin sentencia | E19 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| separador | E21 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| comentario | E23 | E23 | E23 | E23 | E23 | E23 | E24 | E23 | E23 | E23 | E23 | E23 | E23 | E23 | E23 | E23 | E23 | E23 | E23 | E23 |
| posible fin comentario | E24 | E23 | E23 | E23 | E23 | E23 | E23 | -1 | E23 | E23 | E23 | E23 | E23 | E23 | E23 | E23 | E23 | E23 | E23 | E23 | E23 |
| entero | E25 | -1 | E25 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | E26 | -1 |
| real | E26 | -1 | E26 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |

#### Aclaración 

* -1 estado final
* -2 error

### Matriz  de tokens

| Estado | Código | letra | digito | = | + | - | * | / | < | > | ! | ( | ) | { | } | : | . | _ | B/ tab |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| estado inicial | E0 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | 38 | 38 | -1 |
| palabra | E1 | -1 | -1 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 |
| id | E2 | -1 | -1 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | -1 | 14 | 14 |
| id | E2bis | -1 | -1 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | 14 | -1 | 14 | 14 |
| asigancion | E3 | 17 | 17 | -1 | 17 | 17 | 17 | 17 | 17 | 17 | 17 | 17 | 17 | 17 | 17 | 17 | 17 | 17 | 17 | -1 |
| igualdad | E4 | 26 | 26 | 26 | 26 | 26 | 26 | 26 | 26 | 26 | 26 | 26 | 26 | 26 | 26 | 26 | 26 | 26 | 26 | 26 |
| suma | E5 | 18 | 18 | 18 | 18 | 18 | 18 | 18 | 18 | 18 | 18 | 18 | 18 | 18 | 18 | 18 | 18 | 18 | 18 | 18 |
| resta | E6 | 19 | 19 | 19 | 19 | 19 | 19 | 19 | 19 | 19 | 19 | 19 | 19 | 19 | 19 | 19 | 19 | 19 | 19 | 19 |
| multiplicación | E7 | 20 | 20 | 20 | 20 | 20 | 20 | 20 | 20 | 20 | 20 | 20 | 20 | 20 | 20 | 20 | 20 | 20 | 20 | 20 |
| división | E8 | 21 | 21 | 21 | 21 | 21 | -1 | 21 | 21 | 21 | 21 | 21 | 21 | 21 | 21 | 21 | 21 | 21 | 21 | -1 |
| mayor | E9 | 22 | 22 | -1 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | -1 |
| mayor o igual | E10 | 24 | 24 | 24 | 24 | 24 | 24 | 24 | 24 | 24 | 24 | 24 | 24 | 24 | 24 | 24 | 24 | 24 | 24 | 24 |
| menor | E11 | 23 | 23 | -1 | 23 | 23 | 23 | 23 | 23 | 23 | 23 | 23 | 23 | 23 | 23 | 23 | 23 | 23 | 23 | -1 |
| menor o igual | E12 | 25 | 25 | 25 | 25 | 25 | 25 | 25 | 25 | 25 | 25 | 25 | 25 | 25 | 25 | 25 | 25 | 25 | 25 | 25 |
| posible distinto | E13 | 38 | 38 | -1 | 38 | 38 | 38 | 38 | 38 | 38 | 38 | 38 | 38 | 38 | 38 | 38 | 38 | 38 | 38 | -1 |
| distinto | E14 | 27 | 27 | 27 | 27 | 27 | 27 | 27 | 27 | 27 | 27 | 27 | 27 | 27 | 27 | 27 | 27 | 27 | 27 | 27 |
| parentesis izq. | E15 | 28 | 28 | 28 | 28 | 28 | 28 | 28 | 28 | 28 | 28 | 28 | 28 | 28 | 28 | 28 | 28 | 28 | 28 | 28 |
| parentesis der. | E16 | 29 | 29 | 29 | 29 | 29 | 29 | 29 | 29 | 29 | 29 | 29 | 29 | 29 | 29 | 29 | 29 | 29 | 29 | 29 |
| llaves izq. | E17 | 30 | 30 | 30 | 30 | 30 | 30 | 30 | 30 | 30 | 30 | 30 | 30 | 30 | 30 | 30 | 30 | 30 | 30 | 30 |
| llave der. | E18 | 31 | 31 | 31 | 31 | 31 | 31 | 31 | 31 | 31 | 31 | 31 | 31 | 31 | 31 | 31 | 31 | 31 | 31 | 31 |
| fin sentencia | E19 | 32 | 32 | 32 | 32 | 32 | 32 | 32 | 32 | 32 | 32 | 32 | 32 | 32 | 32 | 32 | 32 | 32 | 32 | 32 |
| separador | E21 | 34 | 34 | 34 | 34 | 34 | 34 | 34 | 34 | 34 | 34 | 34 | 34 | 34 | 34 | 34 | 34 | 34 | 34 | 34 |
| comentario | E23 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| posible fin comentario | E24 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| entero | E25 | 15 | -1 | 15 | 15 | 15 | 15 | 15 | 15 | 15 | 15 | 15 | 15 | 15 | 15 | 15 | 15 | 15 | -1 | 15 |
| real | E26 | 16 | -1 | 16 | 16 | 16 | 16 | 16 | 16 | 16 | 16 | 16 | 16 | 16 | 16 | 16 | 16 | 16 | 16 | -1 |

#### Aclaración 

* -1 no devuelve tokens

### Tabla de unreads

| Estado | Código | letra | digito | = | + | - | * | / | < | > | ! | ( | ) | { | } | : | . | _ | B/ tab |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| estado inicial | E0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| palabra | E1 | 0 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| id | E2 | 0 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| id | E2bis | 0 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| asigancion | E3 | 1 | 1 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 |
| igualdad | E4 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| suma | E5 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| resta | E6 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| multiplicación | E7 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| división | E8 | 1 | 1 | 1 | 1 | 1 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 |
| mayor | E9 | 1 | 1 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 |
| mayor o igual | E10 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| menor | E11 | 1 | 1 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 |
| menor o igual | E12 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| posible distinto | E13 | 1 | 1 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 |
| distinto | E14 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| parentesis izq. | E15 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| parentesis der. | E16 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| llaves izq. | E17 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| llave der. | E18 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| fin sentencia | E19 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| separador | E21 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
| comentario | E23 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| posible fin comentario | E24 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| entero | E25 | 1 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| real | E26 | 1 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
