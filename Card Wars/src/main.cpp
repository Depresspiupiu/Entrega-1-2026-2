#include "Juego.h"

#include <iostream>
#include <limits>

using namespace std;

int main() {

    Juego juego;

    int opcion;

    do {

        cout << endl;
        cout << "========================================" << endl;
        cout << "          JUEGO DE CARTAS" << endl;
        cout << "========================================" << endl;

        cout << "1. Jugar ronda" << endl;
        cout << "2. Mostrar estado" << endl;
        cout << "3. Guardar partida" << endl;
        cout << "4. Cargar partida" << endl;
        cout << "5. Ver ganador final" << endl;
        cout << "6. Salir" << endl;

        cout << endl;
        cout << "Seleccione una opcion: ";

        cin >> opcion;

        if (cin.fail()) {

            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            cout << "Entrada invalida." << endl;

            continue;
        }

        switch (opcion) {

            case 1:

                juego.jugarRonda();

                break;

            case 2:

                juego.mostrarEstado();

                break;

            case 3:

                juego.guardarPartida(
                    "partidas/partida.txt"
                );

                break;

            case 4:

                juego.cargarPartida(
                    "partidas/partida.txt"
                );

                break;

            case 5:

                juego.mostrarGanador();

                break;

            case 6:

                cout << endl;
                cout << "Gracias por jugar." << endl;

                break;

            default:

                cout << endl;
                cout << "Opcion invalida." << endl;
        }

    } while (opcion != 6);

    return 0;
}