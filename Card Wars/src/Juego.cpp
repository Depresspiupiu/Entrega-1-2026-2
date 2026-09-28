#include "Juego.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <limits>

using namespace std;

Juego::Juego() {

    jugador1 = Jugador("Jugador 1");
    jugador2 = Jugador("Jugador 2");

    turno = 1;

    colorMayor = "";
    colorMenor = "";

    crearMazo();
}

void Juego::crearMazo() {

    mazo.clear();

    vector<string> colores = {
        "Rojo",
        "Azul",
        "Verde",
        "Amarillo"
    };

    for (const string& color : colores) {

        for (int poder = 1; poder <= 13; poder++) {

            mazo.push_back(
                Carta(color, poder)
            );
        }
    }

    mezclarMazo();
}

void Juego::mezclarMazo() {

    random_device rd;
    mt19937 generador(rd());

    shuffle(
        mazo.begin(),
        mazo.end(),
        generador
    );
}

void Juego::mostrarColores() const {

    cout << "1. Rojo" << endl;
    cout << "2. Azul" << endl;
    cout << "3. Verde" << endl;
    cout << "4. Amarillo" << endl;
}

string Juego::obtenerColor(int opcion) const {

    switch (opcion) {

        case 1:
            return "Rojo";

        case 2:
            return "Azul";

        case 3:
            return "Verde";

        case 4:
            return "Amarillo";

        default:
            return "";
    }
}

void Juego::elegirColores() {

    string jugadorQueElige;

    if (turno == 1) {
        jugadorQueElige = jugador1.getNombre();
    } else {
        jugadorQueElige = jugador2.getNombre();
    }

    cout << endl;
    cout << "========================================" << endl;
    cout << "          ELECCION DE COLORES" << endl;
    cout << "========================================" << endl;

    cout << jugadorQueElige
         << " debe elegir los colores." << endl;

    int opcionMayor;

    do {

        cout << endl;
        cout << "Seleccione el COLOR MAYOR:" << endl;

        mostrarColores();

        cout << "Opcion: ";
        cin >> opcionMayor;

        if (opcionMayor < 1 || opcionMayor > 4) {
            cout << "Opcion invalida." << endl;
        }

    } while (opcionMayor < 1 || opcionMayor > 4);

    colorMayor = obtenerColor(opcionMayor);

    int opcionMenor;

    do {

        cout << endl;
        cout << "Seleccione el COLOR MENOR:" << endl;

        mostrarColores();

        cout << "Opcion: ";
        cin >> opcionMenor;

        if (opcionMenor < 1 || opcionMenor > 4) {

            cout << "Opcion invalida." << endl;

        } else if (opcionMenor == opcionMayor) {

            cout << "El color menor debe ser diferente "
                 << "al color mayor." << endl;
        }

    } while (
        opcionMenor < 1 ||
        opcionMenor > 4 ||
        opcionMenor == opcionMayor
    );

    colorMenor = obtenerColor(opcionMenor);

    cout << endl;
    cout << "Color MAYOR: " << colorMayor << endl;
    cout << "Color MENOR: " << colorMenor << endl;
}

int Juego::determinarGanador(
    const Carta& carta1,
    const Carta& carta2
) const {

    // Si tienen el mismo color,
    // gana la carta con mayor poder.

    if (carta1.getColor() == carta2.getColor()) {

        if (carta1.getPoder() > carta2.getPoder()) {
            return 1;
        }

        if (carta2.getPoder() > carta1.getPoder()) {
            return 2;
        }

        return 0;
    }

    // El color mayor tiene prioridad.

    if (carta1.getColor() == colorMayor) {
        return 1;
    }

    if (carta2.getColor() == colorMayor) {
        return 2;
    }

    // Si ninguno tiene el color mayor,
    // gana la carta con mayor poder.

    if (carta1.getPoder() > carta2.getPoder()) {
        return 1;
    }

    if (carta2.getPoder() > carta1.getPoder()) {
        return 2;
    }

    return 0;
}

void Juego::jugarRonda() {

    if (mazo.size() < 2) {

        cout << endl;
        cout << "No quedan suficientes cartas." << endl;
        cout << "Creando un nuevo mazo..." << endl;

        crearMazo();
    }

    cout << endl;
    cout << "========================================" << endl;
    cout << "              NUEVA RONDA" << endl;
    cout << "========================================" << endl;

    cout << "Jugador que comienza: ";

    if (turno == 1) {
        cout << jugador1.getNombre() << endl;
    } else {
        cout << jugador2.getNombre() << endl;
    }

    elegirColores();

    Carta carta1 = mazo.back();
    mazo.pop_back();

    Carta carta2 = mazo.back();
    mazo.pop_back();

    cout << endl;

    cout << jugador1.getNombre() << " recibe:" << endl;
    carta1.mostrar();

    cout << endl;

    cout << jugador2.getNombre() << " recibe:" << endl;
    carta2.mostrar();

    int ganador = determinarGanador(
        carta1,
        carta2
    );

    cout << endl;
    cout << "----------------------------------------" << endl;

    if (ganador == 1) {

        cout << "GANADOR: "
             << jugador1.getNombre() << endl;

        jugador1.sumarPuntos(
            carta1.getPoder()
        );

        turno = 1;
    }

    else if (ganador == 2) {

        cout << "GANADOR: "
             << jugador2.getNombre() << endl;

        jugador2.sumarPuntos(
            carta2.getPoder()
        );

        turno = 2;
    }

    else {

        cout << "EMPATE." << endl;
    }

    cout << "----------------------------------------"
         << endl;

    mostrarEstado();
}

void Juego::mostrarEstado() const {

    cout << endl;
    cout << "========================================" << endl;
    cout << "           ESTADO DE PARTIDA" << endl;
    cout << "========================================" << endl;

    jugador1.mostrarPuntaje();
    jugador2.mostrarPuntaje();

    cout << endl;

    cout << "Color mayor: ";

    if (colorMayor.empty()) {
        cout << "No seleccionado" << endl;
    } else {
        cout << colorMayor << endl;
    }

    cout << "Color menor: ";

    if (colorMenor.empty()) {
        cout << "No seleccionado" << endl;
    } else {
        cout << colorMenor << endl;
    }

    cout << endl;

    cout << "Proximo jugador que comienza: ";

    if (turno == 1) {
        cout << jugador1.getNombre() << endl;
    } else {
        cout << jugador2.getNombre() << endl;
    }

    cout << "Cartas restantes: "
         << mazo.size() << endl;

    cout << "========================================"
         << endl;
}

void Juego::guardarPartida(
    const string& nombreArchivo
) const {

    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {

        cout << endl;
        cout << "ERROR: No se pudo guardar "
             << "la partida." << endl;

        return;
    }

    archivo << jugador1.getNombre() << endl;
    archivo << jugador2.getNombre() << endl;

    archivo << jugador1.getPuntaje() << endl;
    archivo << jugador2.getPuntaje() << endl;

    archivo << turno << endl;

    archivo << colorMayor << endl;
    archivo << colorMenor << endl;

    archivo << mazo.size() << endl;

    for (const Carta& carta : mazo) {

        archivo << carta.getColor() << endl;
        archivo << carta.getPoder() << endl;
    }

    archivo.close();

    cout << endl;
    cout << "========================================" << endl;
    cout << "Partida guardada correctamente." << endl;
    cout << "========================================" << endl;
}

void Juego::cargarPartida(
    const string& nombreArchivo
) {

    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {

        cout << endl;
        cout << "No existe una partida guardada." << endl;

        return;
    }

    string nombre1;
    string nombre2;

    int puntaje1;
    int puntaje2;

    int cantidadCartas;

    getline(archivo, nombre1);
    getline(archivo, nombre2);

    archivo >> puntaje1;
    archivo >> puntaje2;

    archivo >> turno;

    archivo.ignore(
        numeric_limits<streamsize>::max(),
        '\n'
    );

    getline(archivo, colorMayor);
    getline(archivo, colorMenor);

    archivo >> cantidadCartas;

    archivo.ignore(
        numeric_limits<streamsize>::max(),
        '\n'
    );

    jugador1 = Jugador(nombre1);
    jugador2 = Jugador(nombre2);

    jugador1.establecerPuntaje(puntaje1);
    jugador2.establecerPuntaje(puntaje2);

    mazo.clear();

    for (int i = 0; i < cantidadCartas; i++) {

        string color;
        int poder;

        getline(archivo, color);

        archivo >> poder;

        archivo.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        mazo.push_back(
            Carta(color, poder)
        );
    }

    archivo.close();

    cout << endl;
    cout << "========================================" << endl;
    cout << "Partida cargada correctamente." << endl;
    cout << "========================================" << endl;

    mostrarEstado();
}

void Juego::mostrarGanador() const {

    cout << endl;
    cout << "========================================" << endl;
    cout << "             RESULTADO FINAL" << endl;
    cout << "========================================" << endl;

    jugador1.mostrarPuntaje();
    jugador2.mostrarPuntaje();

    cout << endl;

    if (jugador1.getPuntaje() >
        jugador2.getPuntaje()) {

        cout << "GANADOR DE LA PARTIDA: "
             << jugador1.getNombre() << endl;
    }

    else if (jugador2.getPuntaje() >
             jugador1.getPuntaje()) {

        cout << "GANADOR DE LA PARTIDA: "
             << jugador2.getNombre() << endl;
    }

    else {

        cout << "LA PARTIDA TERMINO EN EMPATE." << endl;
    }

    cout << "========================================" << endl;
}