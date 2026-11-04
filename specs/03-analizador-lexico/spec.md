# Spec — Analizador léxico de DUOTIPO

## 1\. Alcance e interfaz

Función `yylex()` invocada por el analizador sintáctico. Devuelve **un token por llamada**, como entero asociado al número de token. No es una pasada previa que produzca la lista completa.

## 2\. Decisiones propias de esta fase

| \# | Decisión | Valor |
| :---- | :---- | :---- |
| **D1** | **Palabras reservadas** | Se reconocen a través del estado E1. Al cerrarse el lexema, la función de desambiguación compara la cadena con las palabras reservadas del lenguaje (`entero`, `real`, `funcion`, `principal`, `retornar`, `segun`, `caso`, `defecto`, `mientras`, `aEntero`, `aReal`, `y`, `o`, `escribir`). Si coincide, devuelve el token reservado correspondiente (301-313, 335); de lo contrario, devuelve `TK_ID` (314). |
| **D2** | **Límite de longitud de ID** | Longitud máxima de 20 caracteres (`TAM_MAX_ID`). Si el lexema supera los 20 caracteres, la acción `f2` trunca físicamente el identificador en memoria a 20 caracteres y emite una *Advertencia Léxica* (`L2`) por stderr indicando número de línea (`yylineno`), permitiendo continuar el análisis con el identificador truncado. |
| **D3** | **Constantes numéricas y rangos** | Las constantes enteras (`TK_NUM_INT`, 315\) se representan en complemento a dos de 32 bits (`-2147483648` a `2147483647`). Las constantes reales (`TK_NUM_REAL`, 316\) contienen punto decimal con dígitos obligatorios antes y después (formato `dígito.dígito`). Si una constante entera excede el rango de 32 bits o una real excede 38 dígitos enteros, la acción `f4` informa un *Error Léxico* (`L3`). La acumulación se realiza con `f3`. |
| **D4** | **Comentarios y blancos** | Los espacios (`' '`), tabuladores (`'\t'`), retornos de carro (`'\r'`), saltos de línea (`'\n'`) y comentarios multilínea de bloque `/* ... */` (estados E22 y E23) son consumidos y descartados por el autómata retornando al estado E0 sin emitir ningún token hacia el sintáctico. Cada `\n` incrementa el contador global de líneas `yylineno` mediante `f6`. |
| **D5** | **Retroceso de carácter (*Unread*)** | Se desacopla completamente de las *acciones semánticas* y se gobierna mediante la matriz `matriz_unreads[ESTADOS][COLUMNAS]`. Si `matriz_unreads[ultimo_estado][ultima_columna] == 1` y `c != EOF`, el analizador léxico ejecuta `ungetc(c, inputFile)` devolviendo el delimitador al flujo de entrada para no perder el carácter que delimitó el token actual. |
| **D6** | **Manejo de errores léxicos** | Ante fallos léxicos se emite un código identificador único: `L1` ante caracteres no pertenecientes al alfabeto; `L4` si se alcanza el fin de archivo (`EOF`) en un comentario multilínea no cerrado; `L5` si se lee un carácter `!` no seguido de `=`. |

---

## 3\. Eventos (columnas de las matrices)

`get_evento(c)` mapea el carácter leído a una de las 20 columnas (0 a 19):

* Si `dentro_comentario == 1`:

  * `'*'` $\rightarrow$ columna 5 (`*`)  
  * `'/'` $\rightarrow$ columna 6 (`/`)  
  * `'\n'`, `' '`, `'\t'`, `'\r'` $\rightarrow$ columna 17 (`BLANCO`)  
  * Cualquier otro carácter $\rightarrow$ columna 0 (`LETRA`)  
* En flujo normal:

| Col | Evento | Símbolo | Caracteres incluidos |
| :---: | :---- | :---: | :---- |
| **0** | Letra | `LETRA` | `a-z`, `A-Z` (`isalpha`) |
| **1** | Dígito | `DÍGITO` | `0-9` (`isdigit`) |
| **2** | Asignación / Igual | `=` | `=` |
| **3** | Suma | `+` | `+` |
| **4** | Resta | `-` | `-` |
| **5** | Multiplicación | `*` | `*` |
| **6** | Barra división | `/` | `/` |
| **7** | Menor | `<` | `<` |
| **8** | Mayor | `>` | `>` |
| **9** | Exclamación | `!` | `!` |
| **10** | Paréntesis izquierdo | `(` | `(` |
| **11** | Paréntesis derecho | `)` | `)` |
| **12** | Llave izquierda | `{` | `{` |
| **13** | Llave derecha | `}` | `}` |
| **14** | Punto y coma | `;` | `;` |
| **15** | Dos puntos | `:` | `:` |
| **16** | Punto decimal | `.` | `.` |
| **17** | Blanco / Separador | `BLANCO` | Espacio (`' '`), tabulación (`'\t'`), retorno (`'\r'`), salto de línea (`'\n'`) |
| **18** | Fin de archivo | `FDA` | Carácter `EOF` (`-1`) |
| **19** | No reconocido | `OTRO` | Cualquier otro carácter fuera del alfabeto de DUOTIPO |

---

## 4\. Estados y diagrama

<img width="2691" height="1493" alt="AUTOMATA_COMPILADORES-DuoTipo v 4 drawio" src="https://github.com/user-attachments/assets/c8984f60-dc39-49d6-b46b-d777bca5dc32" />

&nbsp;

| Estado | Significado |
| :---- | :---- |
| **E0** | Estado inicial; consume blancos o inicia el reconocimiento de tokens |
| **E1** | Reconociendo Identificador o Palabra Reservada |
| **E2** | Reconociendo Constante Entera |
| **E3** | Reconociendo Constante Real (tras leer parte entera y `.`) |
| **E4** | Tras leer `=`; puede ser asignación `=` o pasar a `==` |
| **E5** | Operador aritmético suma `+` |
| **E6** | Operador aritmético resta `-` |
| **E7** | Operador aritmético multiplicación `*` |
| **E8** | Tras leer `/`; puede ser división `/` o inicio de comentario `/*` |
| **E9** | Tras leer `<`; puede ser menor `<` o menor o igual `<=` |
| **E10** | Tras leer `>`; puede ser mayor `>` o mayor o igual `>=` |
| **E11** | Operador relacional menor o igual `<=` |
| **E12** | Operador relacional mayor o igual `>=` |
| **E13** | Operador relacional igualdad `==` |
| **E14** | Tras leer `!`; espera `=` para formar `!=` |
| **E15** | Operador relacional desigualdad `!=` |
| **E16** | Delimitador paréntesis izquierdo `(` |
| **E17** | Delimitador paréntesis derecho `)` |
| **E18** | Delimitador llave izquierda `{` |
| **E19** | Delimitador llave derecha `}` |
| **E20** | Delimitador fin de sentencia `;` |
| **E21** | Delimitador dos puntos `:` |
| **E22** | Dentro de cuerpo de comentario multilínea `/* ...&nbsp;` |
| **E23** | Posible fin de comentario (leyó `*` dentro de comentario, esperando `/`) |
| **EF (-1)** | Estado final; cierre de token y consulta a matriz de tokens |

---

## 5\. Acciones semánticas

| Acción | Nombre de función | Qué hace |
| :---: | :---: | :---- |
| **fn** | `fn` | **No operación / descarte**: No realiza ninguna acción sobre el buffer ni altera variables globales, se utiliza para transiciones que no modifican el estado semántico del token actual. |
| **fe** | `fe` | **Reporte de Error Léxico**: Emite un mensaje de error léxico con número de línea. Si proviene de `E14`, reporta que se esperaba `=` tras `!` (`L5`); ante fin de archivo en comentario (`E22`/`E23`), reporta comentario no cerrado en la línea inicial (`L4`); en cualquier otro caso, reporta carácter fuera del alfabeto (`L1`). |
| **f1** | `f1` | **Acumular Identificador**: Acumula letras o dígitos en `buffer` durante el reconocimiento de identificadores y palabras reservadas en `E0` y `E1`. |
| **f2** | `f2` | **Fin de Identificador**: Concluye la lectura del identificador en `E1` y verifica el límite de 20 caracteres (D2). Si lo excede, emite una advertencia léxica (`L2`) y trunca el lexema a 20 caracteres. |
| **f3** | `f3` | **Acumular Constante Numérica**: Acumula dígitos y punto decimal en `buffer` durante el reconocimiento de constantes enteras y reales (`E0`, `E2`, `E3`). |
| **f4** | `f4` | **Fin de Constante Numérica**: Concluye la constante en `E2` o `E3`. Si es entera (sin punto decimal), valida que no supere el rango de 32 bits con signo (`-2147483648` a `2147483647`). Si es real, valida que la parte entera no supere 38 dígitos. Si desborda, emite error léxico (`L3`). |
| **f5** | `f5` | **Acumular Operador**: Inicializa o concatena caracteres al buffer para operadores simples o compuestos (`=`, `==`, `+`, `-`, `*`, `/`, `<`, `>`, `<=`, `>=`, `!=`, etc.). |
| **f6** | `f6` | **Contador de líneas**: Si el carácter leído es `\n`, incrementa el contador global `yylineno`. |
| **f7** | `f7` | **Inicio de Comentario**: Registra la apertura del bloque de comentario multilínea `/*`, guarda la línea de inicio en `linea_comentario` y activa `dentro_comentario = 1`. |
| **f8** | `f8` | **Fin de Comentario**: Cierra el bloque de comentario multilínea `*/`, restablece la bandera `dentro_comentario = 0` y limpia el buffer. |

---

## 6\. Matriz de Acciones Semánticas (`matriz_funciones[24][20]`)

| Nombre de Estado | N° | LETRA (0) | DÍGITO (1) | \= (2) | \+ (3) | \- (4) | \* (5) | / (6) | \< (7) | \> (8) | \! (9) | ( (10) | ) (11) | { (12) | } (13) | ; (14) | : (15) | . (16) | BLANCO (17) | FDA (18) | OTRO (19) |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| `estado inicial` | **E0** | f1 | f3 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | fe | f6 | fn | fe |
| `palabra` | **E1** | f1 | f1 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 | f2 |
| `entero` | **E2** | f4 | f3 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f3 | f4 | f4 | f4 |
| `real` | **E3** | f4 | f3 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 | f4 |
| `asigancion (=)` | **E4** | fn | fn | f5 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| `suma (+)` | **E5** | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| `resta (-)` | **E6** | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| `multiplicación (*)` | **E7** | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| `división (/)` | **E8** | fn | fn | fn | fn | fn | f7 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| `menor (< )` | **E9** | fn | fn | f5 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| `mayor (>)` | **E10** | fn | fn | f5 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| `menor o igual (<=)` | **E11** | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| `mayor o igual (>=)` | **E12** | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| `igualdad (==)` | **E13** | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| `posible distinto` | **E14** | fe | fe | f5 | fe | fe | fe | fe | fe | fe | fe | fe | fe | fe | fe | fe | fe | fe | fe | fe | fe |
| `distinto ( !=)` | **E15** | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| `abre paréntesis` | **E16** | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| `cierra paréntesis` | **E17** | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| `llave apertura` | **E18** | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| `llave cierre` | **E19** | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| `fin sentencia (;)` | **E20** | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| `separador (:)` | **E21** | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn |
| `comentario (/* )` | **E22** | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | f6 | fe | fn |
| `posible fin comentario` | **E23** | fn | fn | fn | fn | fn | fn | f8 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | f6 | fe | fn |

---

## 7\. Matriz de Estados (`matriz_estados[24][20]`)

Valores: `0` a `23` para estados intermedios, `-1` para Estado Final de aceptación (`EF`).

| Nombre de Estado | N° | LETRA (0) | DÍGITO (1) | \= (2) | \+ (3) | \- (4) | \* (5) | / (6) | \< (7) | \> (8) | \! (9) | ( (10) | ) (11) | { (12) | } (13) | ; (14) | : (15) | . (16) | BLANCO (17) | FDA (18) | OTRO (19) |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| `Estado inicial` | **E0** | 1 | 2 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 14 | 16 | 17 | 18 | 19 | 20 | 21 | \-1 | 0 | \-1 | \-1 |
| `palabra` | **E1** | 1 | 1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `entero` | **E2** | \-1 | 2 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | 3 | \-1 | \-1 | \-1 |
| `real` | **E3** | \-1 | 3 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `asigancion (=)` | **E4** | \-1 | \-1 | 13 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `suma (+)` | **E5** | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `resta (-)` | **E6** | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `multiplicación (*)` | **E7** | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `división (/)` | **E8** | \-1 | \-1 | \-1 | \-1 | \-1 | 22 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `menor (< )` | **E9** | \-1 | \-1 | 11 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `mayor (>)` | **E10** | \-1 | \-1 | 12 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `menor o igual (<=)` | **E11** | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `mayor o igual (>=)` | **E12** | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `igualdad (==)` | **E13** | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `posible distinto` | **E14** | \-1 | \-1 | 15 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `distinto ( !=)` | **E15** | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `abre paréntesis` | **E16** | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `cierra paréntesis` | **E17** | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `llave apertura` | **E18** | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `llave cierre` | **E19** | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `fin sentencia (;)` | **E20** | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `separador (:)` | **E21** | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 |
| `comentario (/* )` | **E22** | 22 | 22 | 22 | 22 | 22 | 23 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | \-1 | 22 |
| `posible fin comentario` | **E23** | 22 | 22 | 22 | 22 | 22 | 23 | 0 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | \-1 | 22 |

---

## 8\. Tabla de Unreads (`matriz_unreads[24][20]`)

Un valor `1` indica que se debe reinsertar el carácter leído en el buffer de entrada con `ungetc(c, inputFile)`. Un valor `0` indica que el carácter pertenece al token o fue consumido normalmente.

| Nombre de Estado | N° | LETRA (0) | DÍGITO (1) | \= (2) | \+ (3) | \- (4) | \* (5) | / (6) | \< (7) | \> (8) | \! (9) | ( (10) | ) (11) | { (12) | } (13) | ; (14) | : (15) | . (16) | BLANCO (17) | FDA (18) | OTRO (19) |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| `estado inicial` | **E0** | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| `palabra` | **E1** | 0 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `entero` | **E2** | 1 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 | 0 | 1 |
| `real` | **E3** | 1 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `asigancion (=)` | **E4** | 1 | 1 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `suma (+)` | **E5** | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `resta (-)` | **E6** | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `multiplicación (*)` | **E7** | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `división (/)` | **E8** | 1 | 1 | 1 | 1 | 1 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `menor (< )` | **E9** | 1 | 1 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `mayor (>)` | **E10** | 1 | 1 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `menor o igual (<=)` | **E11** | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `mayor o igual (>=)` | **E12** | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `igualdad (==)` | **E13** | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `posible distinto` | **E14** | 1 | 1 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `distinto ( !=)` | **E15** | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `abre paréntesis` | **E16** | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `cierra paréntesis` | **E17** | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `llave apertura` | **E18** | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `llave cierre` | **E19** | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `fin sentencia (;)` | **E20** | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `separador (:)` | **E21** | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 0 | 1 |
| `comentario (/* )` | **E22** | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| `posible fin comentario` | **E23** | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

---

## 9\. Matriz de Tokens (`matriz_tokens[24][20]`)

- Un valor `-1` indica que en esa combinación no se produce cierre de token (es un estado intermedio que continúa en el autómata o un blanco consumido).  
- `TK_ID` (314): Si el identificador coincide con una palabra reservada, la función de desambiguación emitirá el token reservado correspondiente (`301` a `313`, `335`); de lo contrario emite `TK_ID` (314).  
- `0`: Representa el token `YYEOF` / Fin de Archivo (retorno 0 en `yylex()`).  
- `337`: Error léxico (carácter inválido en E0, comentario sin cerrar al fin de archivo o `!` incompleto).

| Nombre de Estado | N° | LETRA (0) | DÍGITO (1) | \= (2) | \+ (3) | \- (4) | \* (5) | / (6) | \< (7) | \> (8) | \! (9) | ( (10) | ) (11) | { (12) | } (13) | ; (14) | : (15) | . (16) | BLANCO (17) | FDA (18) | OTRO (19) |
| :---- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| `estado inicial` | **E0** | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | 337 | \-1 | 0 | 337 |
| `palabra` | **E1** | \-1 | \-1 | 314 | 314 | 314 | 314 | 314 | 314 | 314 | 314 | 314 | 314 | 314 | 314 | 314 | 314 | 314 | 314 | 314 | 314 |
| `entero` | **E2** | 315 | \-1 | 315 | 315 | 315 | 315 | 315 | 315 | 315 | 315 | 315 | 315 | 315 | 315 | 315 | 315 | \-1 | 315 | 315 | 315 |
| `real` | **E3** | 316 | \-1 | 316 | 316 | 316 | 316 | 316 | 316 | 316 | 316 | 316 | 316 | 316 | 316 | 316 | 316 | 316 | 316 | 316 | 316 |
| `asigancion (=)` | **E4** | 317 | 317 | \-1 | 317 | 317 | 317 | 317 | 317 | 317 | 317 | 317 | 317 | 317 | 317 | 317 | 317 | 317 | 317 | 317 | 317 |
| `suma (+)` | **E5** | 318 | 318 | 318 | 318 | 318 | 318 | 318 | 318 | 318 | 318 | 318 | 318 | 318 | 318 | 318 | 318 | 318 | 318 | 318 | 318 |
| `resta (-)` | **E6** | 319 | 319 | 319 | 319 | 319 | 319 | 319 | 319 | 319 | 319 | 319 | 319 | 319 | 319 | 319 | 319 | 319 | 319 | 319 | 319 |
| `multiplicación (*)` | **E7** | 320 | 320 | 320 | 320 | 320 | 320 | 320 | 320 | 320 | 320 | 320 | 320 | 320 | 320 | 320 | 320 | 320 | 320 | 320 | 320 |
| `división (/)` | **E8** | 321 | 321 | 321 | 321 | 321 | \-1 | 321 | 321 | 321 | 321 | 321 | 321 | 321 | 321 | 321 | 321 | 321 | 321 | 321 | 321 |
| `menor (< )` | **E9** | 322 | 322 | \-1 | 322 | 322 | 322 | 322 | 322 | 322 | 322 | 322 | 322 | 322 | 322 | 322 | 322 | 322 | 322 | 322 | 322 |
| `mayor (>)` | **E10** | 323 | 323 | \-1 | 323 | 323 | 323 | 323 | 323 | 323 | 323 | 323 | 323 | 323 | 323 | 323 | 323 | 323 | 323 | 323 | 323 |
| `menor o igual (<=)` | **E11** | 325 | 325 | 325 | 325 | 325 | 325 | 325 | 325 | 325 | 325 | 325 | 325 | 325 | 325 | 325 | 325 | 325 | 325 | 325 | 325 |
| `mayor o igual (>=)` | **E12** | 326 | 326 | 326 | 326 | 326 | 326 | 326 | 326 | 326 | 326 | 326 | 326 | 326 | 326 | 326 | 326 | 326 | 326 | 326 | 326 |
| `igualdad (==)` | **E13** | 327 | 327 | 327 | 327 | 327 | 327 | 327 | 327 | 327 | 327 | 327 | 327 | 327 | 327 | 327 | 327 | 327 | 327 | 327 | 327 |
| `posible distinto` | **E14** | 337 | 337 | \-1 | 337 | 337 | 337 | 337 | 337 | 337 | 337 | 337 | 337 | 337 | 337 | 337 | 337 | 337 | 337 | 337 | 337 |
| `distinto ( !=)` | **E15** | 324 | 324 | 324 | 324 | 324 | 324 | 324 | 324 | 324 | 324 | 324 | 324 | 324 | 324 | 324 | 324 | 324 | 324 | 324 | 324 |
| `abre paréntesis` | **E16** | 328 | 328 | 328 | 328 | 328 | 328 | 328 | 328 | 328 | 328 | 328 | 328 | 328 | 328 | 328 | 328 | 328 | 328 | 328 | 328 |
| `cierra paréntesis` | **E17** | 329 | 329 | 329 | 329 | 329 | 329 | 329 | 329 | 329 | 329 | 329 | 329 | 329 | 329 | 329 | 329 | 329 | 329 | 329 | 329 |
| `llave apertura` | **E18** | 330 | 330 | 330 | 330 | 330 | 330 | 330 | 330 | 330 | 330 | 330 | 330 | 330 | 330 | 330 | 330 | 330 | 330 | 330 | 330 |
| `llave cierre` | **E19** | 331 | 331 | 331 | 331 | 331 | 331 | 331 | 331 | 331 | 331 | 331 | 331 | 331 | 331 | 331 | 331 | 331 | 331 | 331 | 331 |
| `fin sentencia (;)` | **E20** | 332 | 332 | 332 | 332 | 332 | 332 | 332 | 332 | 332 | 332 | 332 | 332 | 332 | 332 | 332 | 332 | 332 | 332 | 332 | 332 |
| `separador (:)` | **E21** | 333 | 333 | 333 | 333 | 333 | 333 | 333 | 333 | 333 | 333 | 333 | 333 | 333 | 333 | 333 | 333 | 333 | 333 | 333 | 333 |
| `comentario (/* )` | **E22** | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | 337 | \-1 |
| `posible fin comentario` | **E23** | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | \-1 | 337 | \-1 |

---

## 10\. Errores y advertencias que emite esta fase

| Código | Condición | Mensaje emitido | Recuperación |
| :---: | :---- | :---- | :---- |
| **L1** | Carácter no perteneciente al alfabeto de DUOTIPO (`OTRO` o `.` aislado en E0). | `Error lexico (L1): Caracter '%c' no valido en el lenguaje en linea %d.` | Se descarta el carácter no válido y el autómata vuelve al estado E0. |
| **L2** | Identificador que excede el límite de 20 caracteres. | `Advertencia lexica (L2): Identificador '%s' supera el limite de 20 caracteres. Se truncara en linea %d.` | El identificador se trunca físicamente a 20 caracteres en memoria y se continúa la compilación. |
| **L3** | Constante numérica fuera de rango (entera de 32 bits o real de más de 38 dígitos enteros). | `Error lexico (L3): Constante entera fuera de rango (-2147483648 a 2147483647) en linea %d.`<br>`Error lexico (L3): Constante real excede el maximo de 38 digitos enteros en linea %d.` | Se vacía el buffer y se continúa el análisis. |
| **L4** | Fin de archivo inesperado (`EOF`) dentro de un comentario multilínea `/* ...`. | `Error lexico (L4): Fin de archivo inesperado. Comentario sin cerrar en linea %d.` | Se interrumpe la ejecución del analizador léxico reportando error en la línea inicial. |
| **L5** | Operador `!` seguido de un carácter distinto de `=`. | `Error lexico (L5): Caracter '!' inesperado. Se esperaba '=' para formar '!=' en linea %d.` | Se aplica unread sobre el delimitador, se reporta el error y vuelve a E0. |

---

## 11\. Traza de verificación

##### Traza 1: Reconocimiento de identificador y operador `+` (`contador + 5`)

| Paso | N° | Estado | Carácter leído | Evento | Acción | Nuevo estado | Unread | Token devuelto |
| :---: | :---: | :---- | :---: | :---: | :---: | :---: | :---: | :---: |
| 1 | E0 | `estado inicial` | `'c'` | `letra` (0) | `f1` (acumular ID) | 1 (`palabra`) | 0 | — |
| 2 | E1 | `palabra` | `'o'` | `letra` (0) | `f1` (acumular ID) | 1 (`palabra`) | 0 | — |
| ... | E1 | `palabra` | `'r'` | `letra` (0) | `f1` (acumular ID) | 1 (`palabra`) | 0 | — |
| 3 | E1 | `palabra` | `' '` | `BL` (17) | `f2` (validar longitud) | \-1 (EF) | 1 | `TK_ID` ("contador") via matriz |
| 4 | E0 | `estado inicial` | `' '` | `BL` (17) | `f6` (contar/blanco) | 0 (`estado inicial`) | 0 | — |
| 5 | E0 | `estado inicial` | `'+'` | `+` (3) | `f5` (acumular op) | 5 (`suma (+)`) | 0 | — |
| 6 | E5 | `suma (+)` | `' '` | `BL` (17) | `fn` | \-1 (EF) | 1 | `TK_PLUS` (`+`) via matriz |

Traza 2: Consumo silencioso de comentario multilínea (`/* comentario */`)

| Paso | N° | Estado | Carácter leído | Evento | Acción | Nuevo estado | Unread | Token devuelto |
| :---: | :---: | :---- | :---: | :---: | :---: | :---: | :---: | :---: |
| 1 | E0 | `estado inicial` | `'/'` | `/` (6) | `f5` (acumular op) | 8 (`división (/)`) | 0 | — |
| 2 | E8 | `división (/)` | `'*'` | `*` (5) | `f7` (inicio comentario) | 22 (`comentario (/* )`) | 0 | — |
| 3 | E22 | `comentario (/* )` | `'c'` | `letra` (0) | `fn` | 22 (`comentario (/* )`) | 0 | — |
| 4 | E22 | `comentario (/* )` | `'*'` | `*` (5) | `fn` | 23 (`posible fin comentario`) | 0 | — |
| 5 | E23 | `posible fin comentario` | `'/'` | `/` (6) | `f8` (fin comentario) | 0 (`estado inicial`) | 0 | — (sigue en E0) |

---

## 12\. Casos de prueba de esta fase

| Entrada | Salida esperada | Qué verifica |
| :---- | :---- | :---- |
| `identificadordemasiadolargoparaellenguaje = 10;` | *Advertencia léxica en línea 1* (`L2`, truncado a 20 caracteres) \+ `TK_ID("identificador_demas")`, `TK_ASSIGN`, `TK_NUM_INT(10)`, `TK_SEMI` | Límite máximo de longitud de identificadores truncado físicamente (D2). |
| `a <= b y c != d;` | `TK_ID("a")`, `TK_LE`, `TK_ID("b")`, `TK_AND`, `TK_ID("c")`, `TK_NEQ`, `TK_ID("d")`, `TK_SEMI` | Operadores relacionales compuestos y conectores lógicos reservados. |
| `/* bloque sin cerrar` | *Error léxico: Fin de archivo inesperado. Comentario sin cerrar en línea 1* (`L4`) | Manejo correcto de EOF dentro de comentarios sin pasar al parser sintáctico. |
| `!a` | *Error léxico en línea 1: Carácter '\!' inesperado* (`L5`) \+ `TK_ID("a")` | Manejo de exclamación no seguida de igual. |

&nbsp;


