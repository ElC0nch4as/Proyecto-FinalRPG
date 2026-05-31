# \# La gran aventura del HEROE \& PIMPI

# 

# \## Descripcion

# \*\*La gran aventura del HEROE \& PIMPI\*\* es un videojuego de aventura de texto desarrollado en \*\*C++\*\* con un estilo inspirado en los juegos de exploracion y narrativa por consola.  

# El jugador controla al \*\*HEROE\*\*, quien junto a su companiero \*\*PIMPI\*\* emprende un viaje para derrotar a los tres generales demoniacos y finalmente al \*\*Rey Demonio, Abyssandros\*\*.

# 

# El juego mezcla:

# \- narrativa por texto

# \- combates por turnos

# \- sistema de inventario

# \- tienda con compra de objetos

# \- armas y armaduras equipables

# \- experiencia y niveles

# \- musica en escenas importantes

# \- finales multiples

# 

# \---

# 

# \## Sinopsis

# Hace mucho tiempo, un reino pacifico fue invadido por demonios surgidos de las profundidades.  

# Ante la desesperacion de la humanidad y la derrota de incontables heroes, un autoproclamado HEROE aparece con la promesa de acabar con el Rey Demonio y restaurar la paz.

# 

# Acompanado por PIMPI, una criatura tan ridicula como importante, el HEROE debera abrirse paso entre fortalezas, generales demonios y un conflicto que poco a poco revela que la guerra no era tan simple como parecia.

# 

# \---

# 

# \## Caracteristicas principales

# \- Sistema de combate por turnos

# \- Inventario funcional con uso, equipamiento, informacion y descarte de objetos

# \- Sistema de tienda con oro y stock limitado

# \- Espadas y armaduras equipables

# \- Poushons con efectos ofensivos, defensivos y especiales

# \- Sistema de experiencia y subida de nivel

# \- Integracion de musica y texto progresivo

# \- Diferentes finales, incluyendo un final oculto

# \- Interacciones especiales entre PIMPI y distintos objetos

# 

# \---

# 

# \## Clases principales del proyecto

# El proyecto esta construido con \*\*Programacion Orientada a Objetos\*\*, usando clases con responsabilidades claras. Entre las principales se encuentran:

# 

# \- `Item`  

# &#x20; Representa los objetos del juego, como poushons, espadas, armaduras y objetos especiales.

# 

# \- `Personaje`  

# &#x20; Clase base que contiene atributos comunes como nombre, vida, vida maxima y danio.

# 

# \- `Heroe`  

# &#x20; Clase del jugador. Gestiona estadisticas, inventario, oro, nivel, experiencia, uso de PIMPI y equipamiento.

# 

# \- `Enemigo`  

# &#x20; Representa a los enemigos y jefes del juego, incluyendo sus estadisticas y estados alterados.

# 

# \- `Tienda`  

# &#x20; Maneja la compra de equipo y poushons.

# 

# \- `Juego`  

# &#x20; Coordina el flujo general del sistema: combate, inventario, tienda, descanso, narrativa y finales.

# 

# \---

# 

# \## Personajes principales

# 

# \### HEROE

# Protagonista de la aventura. Es el personaje controlado por el jugador y quien toma todas las decisiones durante el viaje.

# 

# \### PIMPI

# Companiero del HEROE. Puede ayudar en combate, ser consumido, alterado por poushons o influir directamente en uno de los finales del juego.

# 

# \### Venedictuz Decimuz

# Primer general demonio. Es grotesco, arrogante, burlon e imponente.

# 

# \### Karg' Aalh

# Segundo general demonio. Guerrero poderoso, disciplinado y entusiasmado por enfrentarse a rivales fuertes.

# 

# \### Zhimingde

# Tercera general demonio. Elegante, refinada, letal y completamente leal a su rey.

# 

# \### Abyssandros

# Rey Demonio y jefe final del juego. Es un soberano oscuro que considera sus acciones como la unica forma de proteger a su pueblo.

# 

# \---

# 

# \## Sistema de juego

# El bucle general del juego funciona de esta forma:

# 

# 1\. Se presenta parte de la historia.

# 2\. El jugador entra a combate contra un jefe.

# 3\. Si gana, recibe experiencia.

# 4\. El jugador entra a una zona de descanso.

# 5\. En la zona de descanso puede:

# &#x20;  - ver su estado

# &#x20;  - abrir inventario

# &#x20;  - comprar en tienda

# &#x20;  - descansar

# &#x20;  - buffarse

# 6\. Luego continua la historia hasta el siguiente enfrentamiento.

# 

# \---

# 

# \## Opciones y controles del jugador

# El juego funciona completamente por consola mediante menus numericos.

# 

# \### Durante combate

# \- `1. Atacar`

# \- `2. Inventario`

# 

# \### En el inventario

# Dependiendo del contexto, el jugador puede:

# \- usar objeto

# \- equipar objeto

# \- ver informacion de objeto

# \- descartar objeto

# \- salir

# 

# \### En la tienda

# \- comprar equipo

# \- comprar poushons

# \- salir

# 

# \### En la zona de descanso

# \- tienda

# \- estado del HEROE

# \- inventario

# \- descansar

# \- buffarse

# \- continuar

# 

# \---

# 

# \## Sistema de combate

# El combate es por turnos.  

# En cada ronda, el jugador puede atacar o usar objetos del inventario. Los enemigos pueden ser afectados por estados alterados como:

# \- veneno

# \- congelamiento

# 

# El HEROE tambien puede mejorar temporalmente sus estadisticas con poushons, equipamiento y apoyo de PIMPI.

# 

# \---

# 

# \## Sistema de inventario

# El inventario permite:

# \- almacenar objetos

# \- usar poushons dentro y fuera de combate

# \- equipar espadas y armaduras

# \- consultar informacion detallada de cada objeto

# \- descartar objetos

# 

# Ademas, algunos objetos especiales pueden aparecer dependiendo de las interacciones con PIMPI.

# 

# \---

# 

# \## Sistema economico

# El jugador inicia con oro y puede gastar ese recurso dentro de la tienda para comprar:

# \- espadas

# \- armaduras

# \- poushons

# \- objetos especiales

# 

# Cada compra valida:

# \- stock disponible

# \- cantidad deseada

# \- oro suficiente

# 

# \-----------------------------------------------------------------------------------------------------------------------------------------------

# 

# \## Requisitos para compilar y ejecutar

# \- \*\*Sistema operativo:\*\* Windows

# \- \*\*Compilador / IDE recomendado:\*\* Visual Studio

# \- \*\*Lenguaje:\*\* C++

# \- \*\*Librerias utilizadas:\*\* `iostream`, `string`, `vector`, `limits`, `conio.h`, `thread`, `windows.h`, `mmsystem.h`

# 

# \---

# 

# \## Instrucciones para compilar y ejecutar

# 1\. Clonar o descargar este repositorio completo.

# 2\. Verificar que la carpeta de audio se encuentre incluida dentro del proyecto.

# 3\. Abrir la solucion del proyecto en \*\*Visual Studio\*\*.

# 4\. Compilar en modo `Debug` o `Release`.

# 5\. Ejecutar el proyecto desde Visual Studio.

# 

# \---

# 

# \## Importante sobre la musica

# Este proyecto utiliza archivos de audio en formato `.wav` para reproducir musica y efectos durante la partida.  

# 

# \### Estructura esperada

# Ejemplo:

# 

# Proyecto/

# ├── Source.cpp

# ├── Assets/Audio

# │   ├── Campamento.wav

# │   ├── Bloody Tears.wav

# │   ├── Derrota.wav

# │   ├── Gang-Plank Galleon.wav

# │   ├── Out of Tartarus.wav

# │   ├── Grimm.wav

# │   ├── Victoria del FINAL.wav

# │   ├── ...

# 

# \### Nota

# Es necesario mover manualmente los archivos de audio/musica a `x64/Debug` donde se encuentra el ejecutable (.exe)

# 

# Si los archivos de audio no estan presentes en el ejecutable, el juego seguira ejecutandose, pero no reproducira musica y en vez de eso se escuchara un sonido de advertencia.

# 

# \---

# 

# \## Narrativa y finales

# El juego cuenta con:

# \- una introduccion

# \- desarrollo con varios jefes

# \- un final malo

# \- un final bueno

# \- un final oculto

# 

# Esto cumple con el requisito de incluir una historia base con desarrollo y multiples desenlaces.

# 

# \---

# 

# \## Autor

# \*\*Maximo Andre Marin Jabalera\*\*

# 

# \---

# 

# \## Version

# \*\*Version actual y final:\*\* 1.0 (y se chingo)

