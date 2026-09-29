#include "Juego.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <limits>
#include <filesystem>

using namespace std;

Juego::Juego(int cantidadJugadores) {
    nuevaPartida(cantidadJugadores);
}

void Juego::nuevaPartida(int cantidadJugadores) {
    cantidadJugadores = max(1, min(4, cantidadJugadores));
    jugadores.clear();
    for (int i = 0; i < cantidadJugadores; ++i) {
        jugadores.emplace_back("Jugador " + to_string(i + 1));
    }
    turno = 1;
    colorMayor = "";
    colorMenor = "";
    crearMazo();
    repartirCartas();
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
        for (int poder = 1; poder <= 10; poder++) {
            mazo.push_back(Carta(color, poder));
        }
    }

    mezclarMazo();

    const size_t cartasPorJugador = 4;
    const size_t totalCartas = jugadores.size() * cartasPorJugador;
    if (mazo.size() > totalCartas) {
        mazo.resize(totalCartas);
    }
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

    string jugadorQueElige = jugadores.at(turno - 1).getNombre();

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
    const vector<Carta>& cartas,
    bool buscarMayor
) const {
    if (cartas.empty()) {
        return -1;
    }
    int ganador = 0;
    bool empate = false;
    for (size_t i = 1; i < cartas.size(); ++i) {
        bool superaGanador = buscarMayor
            ? cartas[i].getPoder() > cartas[ganador].getPoder()
            : cartas[i].getPoder() < cartas[ganador].getPoder();
        if (superaGanador) {
            ganador = static_cast<int>(i);
            empate = false;
        } else if (cartas[i].getPoder() == cartas[ganador].getPoder()) {
            empate = true;
        }
    }
    return empate ? -1 : ganador;
}

void Juego::repartirCartas() {
    const size_t cartasPorJugador = 4;
    if (mazo.size() < jugadores.size() * cartasPorJugador) {
        crearMazo();
    }
    for (Jugador& jugador : jugadores) {
        jugador.limpiarCartas();
        for (size_t i = 0; i < cartasPorJugador; ++i) {
            jugador.recibirCarta(mazo.back());
            mazo.pop_back();
        }
    }
}

void Juego::jugarRonda() {

    if (jugadores.empty()) {
        return;
    }
    if (estaTerminada()) {
        cout << endl << "La partida ya termino." << endl;
        mostrarGanador();
        return;
    }

    cout << endl;
    cout << "========================================" << endl;
    cout << "              NUEVA RONDA" << endl;
    cout << "========================================" << endl;

    turno = ((turno - 1) % static_cast<int>(jugadores.size())) + 1;
    cout << "Jugador que comienza: "
         << jugadores[turno - 1].getNombre() << endl;
    cout << endl << "MANOS DISPONIBLES" << endl;
    for (const Jugador& jugador : jugadores) {
        cout << jugador.getNombre() << ":" << endl;
        const vector<Carta>& mano = jugador.getCartas();
        for (size_t i = 0; i < mano.size(); ++i) {
            cout << "  " << (i + 1) << ". ";
            mano[i].mostrar();
        }
    }

    string seleccion;
    do {
        cout << jugadores[turno - 1].getNombre()
             << ", escriba alta o baja para esta ronda: ";
        cin >> seleccion;
        if (seleccion != "alta" && seleccion != "baja") {
            cout << "Orden invalida. Escriba alta o baja." << endl;
        }
    } while (seleccion != "alta" && seleccion != "baja");

    vector<Carta> cartasJugadas(jugadores.size());
    for (size_t orden = 0; orden < jugadores.size(); ++orden) {
        size_t indiceJugador = (turno - 1 + orden) % jugadores.size();
        Jugador& jugador = jugadores[indiceJugador];
        size_t indiceCarta = 0;
        do {
            cout << jugador.getNombre() << ", elija una carta (1-"
                 << jugador.getCartas().size() << "): ";
            cin >> indiceCarta;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                indiceCarta = 0;
            }
            if (indiceCarta < 1 || indiceCarta > jugador.getCartas().size()) {
                cout << "Carta invalida." << endl;
            }
        } while (indiceCarta < 1 || indiceCarta > jugador.getCartas().size());

        cartasJugadas[indiceJugador] = jugador.jugarCarta(indiceCarta - 1);
        cout << jugador.getNombre() << " juega: ";
        cartasJugadas[indiceJugador].mostrar();
    }

    int ganador = determinarGanador(cartasJugadas, seleccion == "alta");
    int sumaRonda = 0;
    for (const Carta& carta : cartasJugadas) {
        sumaRonda += carta.getPoder();
    }

    cout << endl;
    cout << "----------------------------------------" << endl;

    if (ganador >= 0) {
        cout << "GANADOR: " << jugadores[ganador].getNombre() << endl;
        cout << "Puntos obtenidos: " << sumaRonda << endl;
        jugadores[ganador].sumarPuntos(sumaRonda);
        turno = (turno % static_cast<int>(jugadores.size())) + 1;
    } else {
        cout << "EMPATE." << endl;
        turno = (turno % static_cast<int>(jugadores.size())) + 1;
    }

    cout << "----------------------------------------"
         << endl;

    mostrarEstado();

    if (estaTerminada()) {
        mostrarGanador();
    }
}

bool Juego::estaTerminada() const {
    if (jugadores.empty()) {
        return true;
    }
    for (const Jugador& jugador : jugadores) {
        if (!jugador.getCartas().empty()) {
            return false;
        }
    }
    return true;
}

void Juego::mostrarEstado() const {

    cout << endl;
    cout << "========================================" << endl;
    cout << "           ESTADO DE PARTIDA" << endl;
    cout << "========================================" << endl;

    for (const Jugador& jugador : jugadores) {
        jugador.mostrarPuntaje();
        cout << "  Cartas en mano (" << jugador.getCartas().size() << "):" << endl;
        for (const Carta& carta : jugador.getCartas()) {
            cout << "    ";
            carta.mostrar();
        }
    }

    cout << endl;

    cout << "Turno actual, comienza: ";

    if (!jugadores.empty()) {
        cout << jugadores[(turno - 1) % jugadores.size()].getNombre() << endl;
    }

    cout << "Cartas restantes: "
         << mazo.size() << endl;

    cout << "========================================"
         << endl;
}

void Juego::guardarPartida(
    const string& nombreArchivo
) const {

    filesystem::path directorio = filesystem::path(nombreArchivo).parent_path();
    if (!directorio.empty()) {
        error_code error;
        filesystem::create_directories(directorio, error);
    }

    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {

        cout << endl;
        cout << "ERROR: No se pudo guardar "
             << "la partida." << endl;

        return;
    }

    archivo << "CARDWARS2" << endl;
    archivo << jugadores.size() << endl;
    archivo << turno << endl;
    archivo << colorMayor << endl;
    archivo << colorMenor << endl;
    archivo << mazo.size() << endl;
    for (const Carta& carta : mazo) {
        archivo << carta.getColor() << endl;
        archivo << carta.getPoder() << endl;
    }
    for (const Jugador& jugador : jugadores) {
        archivo << jugador.getNombre() << endl;
        archivo << jugador.getPuntaje() << endl;
        archivo << jugador.getCartas().size() << endl;
        for (const Carta& carta : jugador.getCartas()) {
            archivo << carta.getColor() << endl;
            archivo << carta.getPoder() << endl;
        }
    }

    archivo.close();

    cout << endl;
    cout << "========================================" << endl;
    cout << "Partida guardada correctamente." << endl;
    cout << "========================================" << endl;
}

bool Juego::cargarPartida(
    const string& nombreArchivo
) {

    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {

        cout << endl;
        cout << "No existe una partida guardada." << endl;
        return false;
    }

    string formato;
    getline(archivo, formato);
    if (formato != "CARDWARS2") {
        string nombre2;
        int puntaje1;
        int puntaje2;
        size_t cantidadCartasAntigua;
        getline(archivo, nombre2);
        archivo >> puntaje1 >> puntaje2 >> turno;
        archivo.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(archivo, colorMayor);
        getline(archivo, colorMenor);
        archivo >> cantidadCartasAntigua;
        archivo.ignore(numeric_limits<streamsize>::max(), '\n');
        mazo.clear();
        for (size_t i = 0; i < cantidadCartasAntigua; ++i) {
            string color;
            int poder;
            getline(archivo, color);
            archivo >> poder;
            archivo.ignore(numeric_limits<streamsize>::max(), '\n');
            mazo.emplace_back(color, poder);
        }
        jugadores.clear();
        jugadores.emplace_back(formato);
        jugadores.back().establecerPuntaje(puntaje1);
        jugadores.emplace_back(nombre2);
        jugadores.back().establecerPuntaje(puntaje2);
        repartirCartas();
        cout << endl << "Partida antigua cargada; se repartieron nuevas manos." << endl;
        mostrarEstado();
        return true;
    }
    size_t cantidadJugadores;
    size_t cantidadCartas;
    archivo >> cantidadJugadores >> turno;
    archivo.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(archivo, colorMayor);
    getline(archivo, colorMenor);
    archivo >> cantidadCartas;
    archivo.ignore(numeric_limits<streamsize>::max(), '\n');
    mazo.clear();
    for (size_t i = 0; i < cantidadCartas; ++i) {
        string color;
        int poder;
        getline(archivo, color);
        archivo >> poder;
        archivo.ignore(numeric_limits<streamsize>::max(), '\n');
        mazo.emplace_back(color, poder);
    }
    jugadores.clear();
    for (size_t i = 0; i < cantidadJugadores; ++i) {
        string nombre;
        int puntaje;
        size_t cantidadEnMano;
        getline(archivo, nombre);
        archivo >> puntaje >> cantidadEnMano;
        archivo.ignore(numeric_limits<streamsize>::max(), '\n');
        jugadores.emplace_back(nombre);
        jugadores.back().establecerPuntaje(puntaje);
        for (size_t j = 0; j < cantidadEnMano; ++j) {
            string color;
            int poder;
            getline(archivo, color);
            archivo >> poder;
            archivo.ignore(numeric_limits<streamsize>::max(), '\n');
            jugadores.back().recibirCarta(Carta(color, poder));
        }
    }

    archivo.close();

    cout << endl;
    cout << "========================================" << endl;
    cout << "Partida cargada correctamente." << endl;
    cout << "========================================" << endl;

    mostrarEstado();
    return true;
}

void Juego::mostrarGanador() const {

    cout << endl;
    cout << "========================================" << endl;
    cout << "             RESULTADO FINAL" << endl;
    cout << "========================================" << endl;

    for (const Jugador& jugador : jugadores) {
        jugador.mostrarPuntaje();
    }

    cout << endl;

    if (jugadores.empty()) {
        cout << "No hay jugadores." << endl;
        return;
    }
    if (!estaTerminada()) {
        cout << "La partida aun no termina." << endl;
        return;
    }
    int ganador = 0;
    bool empate = false;
    for (size_t i = 1; i < jugadores.size(); ++i) {
        if (jugadores[i].getPuntaje() > jugadores[ganador].getPuntaje()) {
            ganador = static_cast<int>(i);
            empate = false;
        } else if (jugadores[i].getPuntaje() == jugadores[ganador].getPuntaje()) {
            empate = true;
        }
    }
    if (empate) {
        cout << "LA PARTIDA TERMINO EN EMPATE." << endl;
    } else {
        cout << "GANADOR DE LA PARTIDA: "
             << jugadores[ganador].getNombre() << endl;
    }

    cout << "========================================" << endl;
}