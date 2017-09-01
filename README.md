# Coral2MIDI
Genera un archivo MIDI a partir de cuatro líneas musicales


Este programa lee desde entrada estándar cuatro series de notas musicales y elabora un archivo midi cuyo nombre es fijado por el parámetro que se pase al programa (si no hay parámetro, se guarda en `salida.mid`) que presenta las cuatro voces con el banco MIDI número 53 (52 si se empieza a contar por el 0), conocido como *Coro Aahs*. El programa está orientado a ser usado para generar archivos MIDI de corales a 4 voces.

Compilación: basta usar `make`. Se compilará un archivo con el nombre `coral`.

Uso: cada vez que el programa pida una voz, el usuario deberá introducir las notas de la misma, separando las voces con un salto de línea (tecla Intro). Si alguna línea es incorrecta, el programa pedirá la misma voz anterior (aunque esto tal vez no sea adecuado para el uso del programa usando pipelines).

El formato de cada nota es `[nombre][#/b][altura][b/n/c/s]`, donde `[nombre]` es el nombre de la nota (do, re, mi, fa, sol, la, si), `[#/b]` es el caracter `#` para indicar sostenido, `b` para indicar bemol, o nada para indicar que ni es sostenido ni es bemol; `[altura]` es el número que acompaña a la nota en el [índice acústico científico](http://es.wikipedia.org/wiki/%C3%8Dndice_ac%C3%BAstico_cient%C3%ADfico), y `[b/n/c/s]` es `b` si la figura es una blanca, `n` si es una negra, `c` si es una corchea o `s` si es una semicorchea. Las notas pueden ir separadas por un número arbitrario de espacios (puede ser 0). Por ejemplo, `do4c do#4c re4c mib4c mi4c fa4c` sería una escala cromática de 6 notas a partir del do central, usando corcheas. Tanto el nombre como la altura de la nota pueden sustituirse por una rayabaja `_` para indicar que se trata de una ligadura de la nota anterior. Pueden añadirse puntillos (incluso más de uno) a las notas y las ligaduras: son equivalentes `fa4r _b _n _c`, `fa4r. _n.`, `fa4r...`.

Se adjuntan tres archivos para una prueba rápida del funcionamiento del programa. Puede redirigirse el contenido de los archivos al programa usando `[nombre del ejecutable] < ex[número]` (en Linux será necesario anteponer `./` al ejecutable). También puede pedirse al makefile que haga esto él mismo y que nos ejecute la prueba con el ejemplo 1 usando `make test`. `ex1` es un prototipo de fragmento de coral que podría presentar errores metodológicos (o no). Los otros dos ejemplos no son corales, sino melodías de otro estilo. Reto a quien quiera probar el programa a tratar de identificarlas.

Para reproducir un archivo MIDI en una distribución de Linux, el usuario posiblemente necesite instalar un banco de sonidos (*soundfont*). Por ejemplo, puede instalarse *fluid-GM* usando `sudo apt-get install fluid-soundfont-gm`. Hecho esto, el usuario podrá reproducir archivos MIDI. En Windows hay un sintetizador MIDI con un banco de sonidos por defecto, pero ambos dejan bastante que desear (probablemente son los responsables de que la gente piense que los archivos MIDI suenan como un juguete) por lo que, aunque no es necesario para probar este programa, recomiendo sustituirlos.

El programa está en desarrollo. Puede añadirse muchas funcionalidades y atajos para agilizar la entrada.
