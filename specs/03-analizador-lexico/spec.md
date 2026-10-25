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

| Estado | Significado |
|---|---|

---

## 5. Acciones semánticas

| Acción | Qué hace |
|---|---|

---

## 6. Tabla de Nuevos Estados

`nuevo_estado[estado][evento]`

| Nombre                  | Estado | letra | dígito | = | + | - | * | / | < | > | ! | ( | ) | { | } | ; | : | _ | . | B/tab |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---

---

## 7. Matriz de Transiciones

`proceso[estado][evento]`

---

## 8. Tabla de Unreads

`Sí` = el carácter leído no pertenece al token que se cerró y debe devolverse al
flujo (`unget`).

| Nombre                  | Estado | letra | dígito | = | + | - | * | / | < | > | ! | ( | ) | { | } | ; | : | _ | . | B/tab |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---


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

## 12. Autómata finito

<img width="2691" height="1493" alt="AUTOMATA_COMPILADORES-DuoTipo v 4 drawio" src="https://github.com/user-attachments/assets/c8984f60-dc39-49d6-b46b-d777bca5dc32" />
