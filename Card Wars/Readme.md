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

Compilar en Windows

Instala MinGW-w64 con g++ y agregalo a `PATH`. Ejecuta `ejecutable.bat` o
compila desde esta carpeta con:

```bat
g++ -std=c++17 -O2 -static -static-libgcc -static-libstdc++ src\main.cpp src\Carta.cpp src\Jugador.cpp src\Juego.cpp -o juego.exe
```

El resultado es `juego.exe`, enlazado estaticamente para no depender de DLL de
MinGW. Se compila para Windows de 32 bits y tambien puede ejecutarse en Windows
de 64 bits. No puede ejecutarse directamente en Linux o macOS. El proyecto no
utiliza librerias externas.