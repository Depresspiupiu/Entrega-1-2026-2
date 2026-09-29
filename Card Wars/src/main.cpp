#include "Juego.h"

#include <iostream>
#include <limits>

using namespace std;

namespace {
const string archivoPartida = "partidas/partida.txt";

int leerOpcion(const string& mensaje, int minimo, int maximo) {
    int opcion = 0;
    do {
        cout << mensaje;
        cin >> opcion;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = 0;
        }
    } while (opcion < minimo || opcion > maximo);
    return opcion;
}

bool jugarPartida(Juego& juego) {
    while (true) {
        cout << endl;
        cout << "========================================" << endl;
        cout << "             PARTIDA ACTIVA" << endl;
        cout << "========================================" << endl;
        cout << "1. Jugar turno" << endl;
        cout << "2. Ver estado" << endl;
        cout << "3. Guardar partida" << endl;
        cout << "4. Guardar y volver al titulo" << endl;
        cout << "5. Guardar y salir" << endl;
        int opcion = leerOpcion("Seleccione una opcion: ", 1, 5);

        if (opcion == 1) {
            juego.jugarRonda();
            if (juego.estaTerminada()) {
                juego.guardarPartida(archivoPartida);
                return false;
            }
        } else if (opcion == 2) {
            juego.mostrarEstado();
        } else if (opcion == 3) {
            juego.guardarPartida(archivoPartida);
        } else if (opcion == 4) {
            juego.guardarPartida(archivoPartida);
            return false;
        } else {
            juego.guardarPartida(archivoPartida);
            return true;
        }
    }
}
}

int main() {
    bool salir = false;
    while (!salir) {
        cout << endl;
        cout << "========================================" << endl;
        cout << "              CARD WARS" << endl;
        cout << "========================================" << endl;
        cout << "1. Comenzar" << endl;
        cout << "2. Reanudar" << endl;
        cout << "3. Estadisticas" << endl;
        cout << "4. Salir" << endl;
        int opcion = leerOpcion("Seleccione una opcion: ", 1, 4);

        if (opcion == 1) {
            int cantidadJugadores = leerOpcion(
                "Cantidad de jugadores (1-4): ", 1, 4);
            Juego juego(cantidadJugadores);
            salir = jugarPartida(juego);
        } else if (opcion == 2) {
            Juego juego;
            if (juego.cargarPartida(archivoPartida)) {
                salir = jugarPartida(juego);
            }
        } else if (opcion == 3) {
            Juego estado;
            if (estado.cargarPartida(archivoPartida)) {
                estado.mostrarGanador();
            }
        } else {
            salir = true;
        }
    }

    cout << "Gracias por jugar." << endl;
    return 0;
}