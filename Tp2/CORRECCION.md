# Corrección re-entrega TP2

Hola Diego, te dejo la corrección de la re-entrega de tu TP2.

## Jugabilidad

- **Copilacion:** **Errores de declaración**

> En las lineas ***52*** y ***139*** de ***batalla.c*** no estas declarando correctamente los if/else, ya que al empezar un if con llaves y no utilizarlos en el else algunos compiladores lo toman como error de declaración. Ademas de ser inconsistente con el resto del código.

- **Pasa todas las pruebas:** ***OK***

- **Se puede jugar contra la maquina:** ***OK***

- **Se puede jugar contra otro jugador:** ***OK***

> **Observaciones:**
>
> - Faltaría indicar el código del personaje a posicionar.
>
> - Faltaría indicar el rango de filas y columnas en los que se puede posicionar el personaje seleccionado.

## Calidad del código

### Juego.c

- **Constantes:** Correcta declaración y uso de las mismas.

- **Indentacion:** En general esta bien indentado, a excepción del return.

- **Modularizacion:**

> Se podría mejorar agregando:
>
> - una función que realice las jugadas correspondientes.
> - otra que se encargue de la energía de los jugadores.
> - otra que diga si el juego termino o no.

- **Claridad:** El código esta bien pero a partir de las modularizaciones mencionadas podría ser mas claro.

> Podes generar números aleatorios en un rango determinado utilizando rand de la siguiente manera:

    int numero = (rand() % (MAX - MIN + 1)) + MIN;

### Batalla.h y Batalla.c

- **Constantes:** En general están bien declarados y utilizados a excepción de la función crear_personaje donde hay dos literales dando vueltas.

- **Post y pre condiciones:** Las funciones y procedimientos en el header también tienen que tener las pre y post condiciones, ya que si decido enviar solo el .h y el .o el usuario que utilice la biblioteca no tendría ninguna referencia de como utilizar la misma.

- **Indentacion:** El código esta bien indentado. A excepción de la función avanzar.

- **Modularizacion:** En general esta bien modularizado. Hay algunas partes que se podrían mejorar eliminando código repetido, como en la función avanzar.

- **Claridad:** Se podría mejorar utilizando variables auxiliares, como por ejemplo para las posiciones y los códigos de los personajes.

    - Antes:

            if ((*juego).terreno[personajes[posicion].fila][personajes[posicion].columna] == AMBOS){
                if (personajes[posicion].codigo == soldado) {...

    - Despues:

            char codigo = personajes[posicion].codigo;
            int fila = personajes[posicion].fila;
            int columna = personajes[posicion].columna;

            if(juego->terreno[fila][columna] == AMBOS){
                if(codigo == soldado){...

                            //o

            personaje_t personaje = personajes[posicion];

            if(juego->terreno[personaje.fila][personaje.columna] == AMBOS){
                if(personaje.codigo == soldado){...

> Observaciones:
>
> - Faltaría poner, ademas de las pre y post condiciones una breve descripción de lo que hace la función o procedimiento.
>
> - La función jugar no tiene pre ni post condiciones.
>
> - Se pueden evitar las comparaciones del tipo ***condición == false*** o ***condición == true*** simplemente dejando para el caso de la negación ***!condición*** y para el caso de la afirmación solo la ***condición***.

## Comentarios finales

**Bueno Diego, tu nota es un 7, Espero que mis correcciones te sirvan para tus próximas entregas, seguí mejorando. Saludos, John.**
