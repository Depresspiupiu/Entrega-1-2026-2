Juego de Cartas

Proyecto desarrollado en C++ utilizando programación orientada a objetos.

Clases

El proyecto contiene tres clases principales:

Carta
Jugador
Juego
Funcionamiento

El juego utiliza cartas de cuatro colores:

Rojo
Azul
Verde
Amarillo

Cada carta tiene un poder del 1 al 13.

En cada ronda, el jugador que comienza selecciona:

El color mayor.
El color menor.

Después cada jugador recibe una carta y se determina el ganador.

El ganador obtiene como puntaje el poder de su carta y será quien comience la siguiente ronda.

Guardar partida

El juego permite guardar la partida en:

partidas/partida.txt

Se guarda:

Nombre de los jugadores.
Puntaje.
Turno.
Color mayor.
Color menor.
Cartas restantes.

La partida puede cargarse posteriormente para continuar.

Compilar

Desde una terminal ubicada en la carpeta del proyecto:

g++ src/main.cpp src/Carta.cpp src/Jugador.cpp src/Juego.cpp -o juego
Ejecutar

En Linux o macOS:

./juego

En Windows:

juego.exe
Requisitos

Se necesita un compilador compatible con C++, por ejemplo:

g++

## Diagrama UML

![Diagrama UML del Juego de Cartas] <img width="1312" height="1199" alt="Diagrama UML" src="https://github.com/user-attachments/assets/bf970002-411b-40e3-8055-71ea8172694c" />

MinGW
Visual Studio
Code::Blocks
Visual Studio Code con un compilador C++

No utiliza librerías externas.
