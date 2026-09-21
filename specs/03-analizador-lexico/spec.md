# Spec — Analizador léxico de UNO

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

## 6. Matriz de Nuevos Estados

`nuevo_estado[estado][evento]`

---

## 7. Matriz de Transiciones

`proceso[estado][evento]`

---

## 8. Tabla de Unreads

`Sí` = el carácter leído no pertenece al token que se cerró y debe devolverse al
flujo (`unget`).

		letra	digito	 =	 +	 -	*	/	<	>	!	(	)	{	}	;	:	 _	.	B/ tab
estado inicial	E0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	1
palabra	E1	0	0	1	1	1	1	1	1	1	1	1	1	1	1	1	1	0	1	1
id	E2	0	0	1	1	1	1	1	1	1	1	1	1	1	1	1	1	0	1	1
id	E2bis	0	0	1	1	1	1	1	1	1	1	1	1	1	1	1	1	0	1	1
asigancion	E3	1	1	0	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	0
igualdad	E4	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
suma	E5	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
resta	E6	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
multiplicación	E7	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
división	E8	1	1	1	1	1	0	1	1	1	1	1	1	1	1	1	1	1	1	0
mayor	E9  	1	1	0	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	0
mayor o igual	E10  	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
menor	E11  	1	1	0	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	0
menor o igual	E12  	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
posible distinto	E13  	1	1	0	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	0
distinto	E14  	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
parentesis izq.	E15   	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
parentesis der.	E16    	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
llaves izq.	E17    	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
llave der.	E18      	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
fin sentencia	E19  	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
separador	E21   	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1
posible fin de archivo	E22  	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	0	1	1
comentario	E23	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
posible fin comentario	E24	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0
entero	E25  	1	0	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	0	1
real	E26  	1	0	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1


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
