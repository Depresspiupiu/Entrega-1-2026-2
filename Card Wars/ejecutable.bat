@echo off
setlocal
cd /d "%~dp0"

where g++ >nul 2>nul
if errorlevel 1 (
	set "COMPILADOR=%LOCALAPPDATA%\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin\g++.exe"
	if not exist "%COMPILADOR%" (
		echo No se encontro g++ en PATH ni WinLibs en WinGet.
		echo Instala MinGW-w64 o agrega g++ a PATH.
		pause
		exit /b 1
	)
) else (
	set "COMPILADOR=g++"
)

"%COMPILADOR%" -std=c++17 -O2 -static -static-libgcc -static-libstdc++ src\main.cpp src\Carta.cpp src\Jugador.cpp src\Juego.cpp -o juego.exe
if errorlevel 1 (
	echo Error al compilar el juego.
	pause
	exit /b 1
)

echo Compilacion terminada: juego.exe
pause
