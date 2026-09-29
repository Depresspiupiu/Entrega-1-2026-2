@echo off
setlocal
cd /d "%~dp0"

where g++ >nul 2>nul
if errorlevel 1 (
	echo No se encontro g++ en PATH.
	echo Para generar juego.exe, instala MinGW-w64 y agrega g++ a PATH.
	pause
	exit /b 1
)

g++ -std=c++17 -O2 -static -static-libgcc -static-libstdc++ src\main.cpp src\Carta.cpp src\Jugador.cpp src\Juego.cpp -o juego.exe
if errorlevel 1 (
	echo Error al compilar el juego.
	pause
	exit /b 1
)

echo Compilacion terminada: juego.exe
pause
