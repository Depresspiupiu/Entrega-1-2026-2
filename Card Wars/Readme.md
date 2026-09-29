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

Cada carta tiene un poder aleatorio del 1 al 10. La pantalla de titulo ofrece
Comenzar, Reanudar, Estado y Salir. Al comenzar, se elige de 1 a 4 jugadores y
cada uno recibe cinco cartas aleatorias.

En cada ronda, el jugador que tiene el turno escribe `alta` o `baja`. Luego,
todos los jugadores juegan una carta de su mano y se comparan sus poderes. La
carta mas alta o mas baja, segun la eleccion de la ronda, gana y su jugador
recibe como puntos la suma de todas las cartas jugadas. Un empate no suma
puntos. La eleccion pasa al siguiente jugador. La partida termina cuando se
agotan las manos y gana quien tenga mas puntos.

Guardar partida

El juego permite guardar la partida en:

partidas/partida.txt

Se guarda el número de jugadores, el turno y:

Nombre de los jugadores.
Puntaje.
Puntaje de cada jugador.
Cartas restantes y cartas en la mano de cada jugador.

Al reanudar se restaura el turno, el mazo y las manos. El estado permite
consultar las cartas restantes y quien comienza. La opcion Estadisticas del
menu muestra el ganador y su puntaje. La partida se guarda al terminar o al
elegir Guardar y volver al titulo o Guardar y salir.

Compilar en Windows

Ejecuta `ejecutable.bat` para compilar y generar `juego.exe`. El script busca
`g++` en `PATH` y tambien en la instalacion portable de WinLibs de WinGet. Para
compilar manualmente desde esta carpeta:

```bat
g++ -std=c++17 -O2 -static -static-libgcc -static-libstdc++ src\main.cpp src\Carta.cpp src\Jugador.cpp src\Juego.cpp -o juego.exe
```

El resultado es `juego.exe`, enlazado estaticamente para no depender de DLL de
MinGW. Se compila para Windows de 32 bits y tambien puede ejecutarse en Windows
de 64 bits. No puede ejecutarse directamente en Linux o macOS. El proyecto no
utiliza librerias externas.