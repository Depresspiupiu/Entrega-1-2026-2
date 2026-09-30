# Card Wars

Proyecto de juego de cartas desarrollado en C++ con programación orientada a objetos.

## Descripción general

El juego usa un mazo con 4 colores:

- Rojo
- Azul
- Verde
- Amarillo

Cada carta tiene:

- un color
- un poder del 1 al 10

La partida está pensada para 1 a 4 jugadores.

## Estructura del proyecto

Las clases principales son:

- `Carta`: representa cada carta individual, con su color y poder.
- `Jugador`: guarda el nombre, puntaje y la mano del jugador.
- `Juego`: administra el mazo, los jugadores, el turno, las rondas, la validación del ganador y el guardado/carga de partida.

## Cómo funciona el juego

### Menú principal

Al iniciar, se muestran estas opciones:

1. Comenzar
2. Reanudar
3. Estadísticas
4. Salir

### Nueva partida

Cuando se elige comenzar, se solicita la cantidad de jugadores (1 a 4). Luego:

- se crea el mazo,
- se mezcla,
- y se reparte exactamente 4 cartas a cada jugador.

No quedan cartas sobrantes en el mazo cuando termina el reparto inicial.

### Ronda

En cada ronda:

1. El turno indica quién comienza.
2. El jugador del turno escribe `alta` o `baja`.
3. Cada jugador elige una carta de su mano.
4. Se comparan los poderes de las cartas jugadas.
5. Si la ronda es `alta`, gana la carta con mayor poder.
6. Si la ronda es `baja`, gana la carta con menor poder.
7. El ganador recibe la suma de los poderes de todas las cartas jugadas.
8. Si hay empate, no suma puntos.
9. El siguiente jugador inicia la siguiente ronda.

La partida termina cuando todos los jugadores quedan sin cartas en la mano. Entonces se muestra el puntaje final y el ganador o empate.

## Guardado y carga de partida

El proyecto guarda la partida en:

`partidas/partida.txt`

Se almacena:

- cantidad de jugadores
- turno actual
- color mayor/menor si corresponde a la lógica del juego
- mazo restante
- puntaje de cada jugador
- cartas que tiene cada jugador en la mano

La opción de reanudar permite cargar ese archivo y continuar desde el estado guardado.

## Compilación en Windows

Se recomienda compilar desde la carpeta principal con el script:

```bat
ejecutable.bat
```

Este archivo genera `juego.exe` usando `g++` disponible en PATH o en una instalación portable de WinLibs.

También se puede compilar manualmente con:

```bat
g++ -std=c++17 -O2 -static -static-libgcc -static-libstdc++ src\main.cpp src\Carta.cpp src\Jugador.cpp src\Juego.cpp -o juego.exe
```

## Nota importante

Este proyecto está pensado para Windows y su flujo de compilación está orientado a `ejecutable.bat` y `juego.exe`. No está preparado como proyecto nativo para Linux o macOS.

## Requisitos

- Compilador C++ compatible con C++17
- Windows 10 o superior
- `g++` en PATH o instalación de WinLibs

<img width="1312" height="1199" alt="Diagrama UML" src="https://github.com/user-attachments/assets/db4069bd-6817-4521-812e-6156c24020f7" />
