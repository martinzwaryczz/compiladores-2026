# Bitácora — Analizador léxico de MINI

**Grupo:** ejemplo de cátedra · C
**Spec de referencia:** `specs/03-analizador-lexico/spec.md`
**Modelos usados:** Claude Opus 5, GPT-5.2

---

## Iteración 1 — Primer intento del reconocedor
**Fecha:** 05/09/2026 · Claude Opus 5

**Qué pedí:** Le pasé las secciones 3 a 7 de la spec (eventos, estados, las dos
matrices) y le pedí `yylex()` en C.

**Qué devolvió:** Un lexer con `strchr` y una cadena de `if` por tipo de token.
Funcionaba, pero no tocaba las matrices: las había leído como documentación y
resuelto el problema por su cuenta.

**Qué cambié y por qué:** Lo descartamos entero. El método de la materia es
recorrer el autómata con `proceso[estado][evento]` y `nuevo_estado[estado][evento]`.
Se lo volvimos a pedir pasándole el pseudocódigo del apunte y aclarando que las
matrices tienen que estar en el código como arreglos, no traducidas a
condicionales. La segunda respuesta sí las usó.

**Impacto en la spec:** ninguno.

---

## Iteración 2 — Palabras reservadas
**Fecha:** 05/09/2026 · Claude Opus 5

**Qué pedí:** Que agregara el reconocimiento de `si`, `sino`, `mientras`,
`mostrar`, `entero` y `principal`.

**Qué devolvió:** Estados nuevos en el autómata, uno por cada palabra reservada,
ramificando desde el estado 0 por la primera letra.

**Qué cambié y por qué:** Contradice L1. Las palabras reservadas se reconocen
como identificador y se resuelven al cerrar el lexema, buscando en una tabla.
Con estados propios el autómata crece con cada palabra que agreguemos y las
matrices se vuelven impracticables. Se lo pedimos de nuevo señalando L1 y quedó
resuelto dentro de A3.

**Impacto en la spec:** ninguno. L1 ya estaba, no la había respetado.

---

## Iteración 3 — El `!` solo
**Fecha:** 06/09/2026 · GPT-5.2

**Qué pedí:** Completar la fila del estado 4 de las dos matrices.

**Qué devolvió:** Nos preguntó qué hacer si después del `!` no viene un `=`.

**Qué cambié y por qué:** No lo sabíamos: el diseño define `!=` como token pero
nunca dice qué pasa con un `!` suelto. Lo definimos nosotros — error, se reporta
con la línea y se sigue leyendo — y lo agregamos como E8. También actualizamos
la sección 8 de `01-diseno`, que era donde faltaba.

**Impacto en la spec:** se agregó E8 en la sección 9 y las filas del estado 4 en
las tres tablas. Commit `f3a1c07`.

> Nota: fue el modelo el que encontró el agujero, no nosotros. La decisión de qué
> hacer la tomamos nosotros.

---

## Iteración 4 — El contador de líneas se quedaba en 1
**Fecha:** 08/09/2026 · Claude Opus 5

**Qué pedí:** Nada. Apareció probando `tests/correctos/suma.mini`: todos los
errores salían reportados en la línea 1.

**Qué devolvió:** —

**Qué cambié y por qué:** Al cerrar un identificador con un salto de línea, el
código consumía el `\n` sin devolverlo, y `A11` solo corre en el estado 0. La
tabla de unreads que le habíamos pasado tenía `NL` en **No** para los estados 1 y
2, igual que `BL`. El error era nuestro, estaba en la spec. Lo corregimos a
**Sí** para `NL` y lo dejamos en **No** para `BL`, porque el espacio sí se puede
descartar en el momento.

**Impacto en la spec:** tabla de unreads corregida y se agregó la decisión L6
para dejar explícito el criterio. Commit `9b2e440`.

---

## Iteración 5 — `12x+1` perdía el `+`
**Fecha:** 09/09/2026 · Claude Opus 5

**Qué pedí:** Que implementara el manejo de E2 según la spec.

**Qué devolvió:** Reportaba el error y volvía al estado 0 consumiendo la `x`.
Con `12x+1` eso deja `+1` bien, pero con `12xy+1` reconocía `y` como
identificador — un token fantasma que después le explota al sintáctico.

**Qué cambié y por qué:** Le faltaba el estado 7. Está en la spec (L4: se
descarta el lexema completo, no el carácter que falló) pero no se lo habíamos
pasado en el prompt, porque le mandamos solo las filas de las matrices que
creíamos relevantes. Le pasamos la spec completa y lo resolvió.

**Impacto en la spec:** ninguno. Error nuestro al recortar el contexto.

---

## Iteración 6 — Constante fuera de rango
**Fecha:** 09/09/2026 · GPT-5.2

**Qué pedí:** La validación de E3 dentro de la acción A4.

**Qué devolvió:** `atoi()` y comparación contra `INT_MAX`.

**Qué cambié y por qué:** `atoi` sobre `4294967296` ya desborda antes de que
podamos comparar: el valor que devuelve no sirve para decidir. Lo cambiamos por
`strtol` con chequeo de `errno == ERANGE`, que detecta el desborde en la
conversión. Es la misma discusión de overflow que vamos a tener después en el
generador de código.

**Impacto en la spec:** ninguno, pero anotamos el criterio en L3 para no repetir
la discusión en el GCA.

---

## Estado al cierre de la fase

Los 11 casos de prueba de la sección 11 de la spec pasan. Quedan dos cosas
anotadas para más adelante:

- La advertencia por identificador truncado (L2) todavía se imprime sin número de
  línea.
- No probamos un archivo que termine sin salto de línea final.