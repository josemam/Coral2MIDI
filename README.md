# Coral2MIDI
Genera un archivo MIDI a partir de cuatro líneas musicales


Este programa lee desde entrada estándar cuatro series de notas musicales y elabora un archivo midi `salida.mid` que presenta las cuatro voces con el banco MIDI número 53 (52 si se empieza a contar por el 0), conocido como *Coro Aahs*. El programa está orientado a ser usado para generar archivos MIDI de corales a 4 voces.

Compilación: basta compilar `coral.cpp` con el compilador favorito del usuario, dado que este código llama a `voice.cpp`. Por ejemplo, en Ubuntu basta con usar `g++ -o [nombre del ejecutable] coral.cpp`.

Uso: cada vez que el programa pida una voz, el usuario deberá introducir las notas de la misma. El formato de cada nota es `[nombre][#/b][altura][b/n/c/s]`, donde `[nombre]` es el nombre de la nota (do, re, mi, fa, sol, la, si), `[#/b]` es el caracter `#` para indicar sostenido, `b` para indicar bemol, o nada para indicar que ni es sostenido ni es bemol; `[altura]` es el número que acompaña a la nota en el [índice acústico científico] (http://es.wikipedia.org/wiki/%C3%8Dndice_ac%C3%BAstico_cient%C3%ADfico), y `[b/n/c/s]` es `b` si la figura es una blanca, `n` si es una negra, `c` si es una corchea o `s` si es una semicorchea. Las notas pueden ir separadas por un número arbitrario de espacios (puede ser 0). Por ejemplo, `do4c do#4c re4c mib4c mi4c fa4c` sería una escala cromática de 6 notas a partir del do central, usando corcheas. Las voces van separadas por un salto de línea (tecla Intro).

Se adjuntan tres archivos para una prueba rápida del funcionamiento del programa. En Ubuntu puede redirigirse el contenido de los archivos al programa usando `cat ex[número] | ./[nombre del ejecutable]`. `ex1` es un prototipo de fragmento de coral que podría presentar errores metodológicos (o no). Los otros dos ejemplos no son corales, sino melodías de otro estilo. Reto a quien quiera probar el programa a tratar de identificarlas.

Para reproducir en Ubuntu un archivo MIDI, el usuario posiblemente necesite instalar un banco de sonidos (*soundfont*). Por ejemplo, puede instalarse *fluid-GM* usando `sudo apt-get install fluid-soundfont-gm`. Hecho esto, el usuario podrá reproducir archivos MIDI.

El programa está en desarrollo. Puede añadirse muchas funcionalidades y hay varios errores pendientes de corrección. También puede separarse en varios trozos para añadir mayor versatilidad al código.
