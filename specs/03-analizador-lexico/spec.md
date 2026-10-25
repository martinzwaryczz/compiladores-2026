# Spec — Analizador léxico de DUOTIPO

**Grupo:** ejemplo de cátedra · **Lenguaje de implementación:** C
**Depende de:** `specs/01-diseno/spec.md`
**Produce:** `src/lexico/` · escribe en la tabla de símbolos definida en `specs/02-tabla-simbolos/spec.md`

---

## 1. Alcance e interfaz

Función `yylex()` invocada por el analizador sintáctico. Devuelve **un token por
llamada**, como entero asociado al número de token. No es una pasada previa que
produzca la lista completa.

## 2. Decisiones propias de esta fase

| # | Decisión | Valor |
|---|---|---|

---

## 3. Eventos (columnas de las matrices)

`get_evento(c)` mapea el carácter leído a una columna:

| Col | Evento | Caracteres |
|---|---|---|

---

## 4. Estados y Diagrama

<img width="2691" height="1493" alt="AUTOMATA_COMPILADORES-DuoTipo v 4 drawio" src="https://github.com/user-attachments/assets/c8984f60-dc39-49d6-b46b-d777bca5dc32" />

---
<center>
  
| Estado | Significado |
|---|---|
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
| **E22** | Dentro de cuerpo de comentario multilínea `/* ...` |
| **E23** | Posible fin de comentario (leyó `*` dentro de comentario, esperando `/`) |
| **EF (-1)** | Estado final; cierre de token y consulta a matriz de tokens |
  
</center>
---

## 5. Acciones semánticas

| Acción | Qué hace |
|---|---|
| `fn` | No hace nada (descarta el carácter o avanza sin almacenar) |
| `f0` | Deslee el carácter actual con `ungetc(caracter, inputFile)` devolviéndolo al flujo |
| `f1` | Inicia el buffer (`bufLen = 0`) con la primera letra de un identificador |
| `f2` | Inicia el buffer (`bufLen = 0`) con el primer dígito de una constante numérica |
| `f3` | Agrega letras o dígitos subsiguientes al buffer del identificador |
| `f4` | Agrega dígitos subsiguientes o el punto decimal al buffer de la constante numérica |
| `f5` | Cierre de constante numérica: deslee delimitador (`f0`) y valida rango de 32 bits si es entero |
| `f6` | Cierre de identificador: deslee delimitador (`f0`) y valida longitud máxima de 20 caracteres |
| `f7` | Inicia y almacena en el buffer un token simple de un solo carácter desde E0 |
| `f8` | Concatena el segundo carácter para conformar operadores compuestos (`==`, `<=`, `>=`, `!=`) |
| `f9` | Blanco consumido por el autómata; si es `\n` incrementa el contador de líneas `yylineno` |
| `f10` | Operador `!` incompleto: deslee el delimitador e informa error léxico (se esperaba `!=`) |
| `f11` | Fin de archivo dentro de un comentario sin cerrar: informa error léxico en la línea de inicio |
| `f12` | Inicio de comentario (`/*`): activa bandera de comentario y registra la línea actual |
| `f13` | Fin de comentario (`*/`): desactiva bandera de comentario y regresa el flujo a E0 |
| `fe` | Carácter no válido en E0 (punto decimal suelto o carácter fuera del alfabeto) |

---

## 6. Matriz de Nuevos Estados

`nuevo_estado[estado][evento]`

| Estado | Let | Dig | = | + | - | * | / | < | > | ! | ( | ) | { | } | ; | : | . | Blanco | FDA |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| **E0** | 1 | 2 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 14 | 16 | 17 | 18 | 19 | 20 | 21 | -1 | 0 | -1 |
| **E1** | 1 | 1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E2** | -1 | 2 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | 3 | -1 | -1 |
| **E3** | -1 | 3 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E4** | -1 | -1 | 13 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E5** | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E6** | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E7** | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E8** | -1 | -1 | -1 | -1 | -1 | 22 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E9** | -1 | -1 | 11 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E10** | -1 | -1 | 12 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E11** | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1|
| **E12** | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E13** | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E14** | -1 | -1 | 15 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E15** | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E16** | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E17** | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E18** | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E19** | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E20** | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E21** | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |
| **E22** | 22 | 22 | 22 | 22 | 22 | 23 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | -1 |
| **E23** | 22 | 22 | 22 | 22 | 22 | 23 | 0 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | 22 | -1 |

---

## 7. Matriz de Transiciones

`proceso[estado][evento]`

| Estado | Let | Dig | = | + | - | * | / | < | > | ! | ( | ) | { | } | ; | : | . | Blanco | FDA |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| **E0** | f1 | f2 | f7 | f7 | f7 | f7 | f7 | f7 | f7 | f7 | f7 | f7 | f7 | f7 | f7 | f7 | fe | f9 | fn |
| **E1** | f3 | f3 | f6 | f6 | f6 | f6 | f6 | f6 | f6 | f6 | f6 | f6 | f6 | f6 | f6 | f6 | f6 | f6 | f6 |
| **E2** | f5 | f4 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f4 | f5 | f5 |
| **E3** | f5 | f4 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 | f5 |
| **E4** | f0 | f0 | f8 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 |
| **E5** | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 |
| **E6** | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 |
| **E7** | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 |
| **E8** | f0 | f0 | f0 | f0 | f0 | f12 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0|
| **E9** | f0 | f0 | f8 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 |
| **E10** | f0 | f0 | f8 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 |
| **E11** | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 |
| **E12** | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 |
| **E13** | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 |
| **E14** | f10 | f10 | f8 | f10 | f10 | f10 | f10 | f10 | f10 | f10 | f10 | f10 | f10 | f10 | f10 | f10 | f10 | f10 | f10 |
| **E15** | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 |
| **E16** | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 |
| **E17** | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 |
| **E18** | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 |
| **E19** | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 |
| **E20** | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 |
| **E21** | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 | f0 |
| **E22** | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | f9 | f11 |
| **E23** | fn | fn | fn | fn | fn | fn | f13 | fn | fn | fn | fn | fn | fn | fn | fn | fn | fn | f9 | f11 |
---


---

## 9. Errores que emite esta fase

| Código | Condición | Mensaje |
|---|---|---|

---

## 10. Traza de verificación

Entrada ``, con el estado inicial 0:

| Estado | Lee | Evento | Acción | Nuevo estado | Unread | Retorna |
|---|---|---|---|---|---|---|


---

## 11. Casos de prueba de esta fase

| Entrada | Salida esperada | Qué verifica |
|---|---|---|



