# Spec — 02-tabla-simbolos

## Objetivo

Almacenar, gestionar y persistir los identificadores y constantes literales reconocidos durante la compilación de nuestro lenguaje. 

## Alcance
- Almacenamiento secuencial persistente de variables globales, variables locales de funciones, identificadores de subrutinas _(aReal, aEntero, funciones)_ y constantes enteras o reales.
- Registro de nombre, alcance, valor y longitud.
- Inserción sin duplicación de identificadores en el mismo ámbito estático ni de constantes idénticas.
  
## Entradas / Salidas
- Constantes enteras o reales, identificadores con tipo de dato.
## Reglas y decisiones de diseño

Asignación estática de memoria para variables locales: en conformidad con el modelo de ejecución las variables locales se alojan en posiciones fijas de memoria estática.

Mapeo de atributos mínimos obligatorios:

- **nombre:** Cadena con el lexema original para globales y constantes, o nombre calificado para locales.
- **tipo:** Clasificación del símbolo _(ENTERO, REAL, CTE_ENTERA, CTE_REAL, FUNCION)_.
-**valor:** Cadena con el valor literal en caso de constantes numéricas, o - para variables y funciones.
- **longitud:** Cantidad de caracteres del nombre registrado _(strlen)_.

Las constantes literales numéricas se prefijan con un guion bajo (_) (ejemplo: _10, _3.14).

La función de inserción realiza una búsqueda previa, si un identificador ya existe dentro del mismo ámbito, se rechaza la duplicación; si una constante literal numérica ya fue registrada, se reutiliza la entrada existente.

La tabla se mantiene en memoria durante toda la corrida del compilador y se vuelca de manera independiente a ts.txt, garantizando que eventuales reportes de error en consola no corrompan su contenido.

## Criterios de aceptación

CA-01 (Cumplimiento de atributos mínimos): Cada fila del archivo ts.txt contiene de manera legible y tabulada los campos: nombre, tipo, valor y longitud.

CA-02 (Unicidad en el mismo ámbito): El módulo impide registrar dos veces el mismo identificador dentro de una misma función o dentro del ámbito global, y evita duplicar constantes con idéntico valor léxico.

CA-03 (Identificación unívoca de variables locales): Las variables locales declaradas dentro de funciones quedan diferenciadas unívocamente en la tabla respecto de variables de otras funciones o globales mediante su calificado estático.

CA-04 (Persistencia y exportación en archivo): La compilación genera el archivo ts.txt en el directorio de trabajo tanto si el análisis concluye exitosamente como si finaliza tras encontrar errores sintácticos o semánticos.

CA-05 (Integridad de datos registrados): La columna longitud refleja la cantidad exacta de caracteres del campo nombre, y el campo valor conserva la representación textual exacta de las constantes reconocidas.
