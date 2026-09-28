#ifndef JUEGO_H
#define JUEGO_H

#include "Carta.h"
#include "Jugador.h"
#include <vector>
#include <string>

class Juego {
private:
    Jugador jugador1;
    Jugador jugador2;

    std::vector<Carta> mazo;

    int turno;

    std::string colorMayor;
    std::string colorMenor;

    void crearMazo();
    void mezclarMazo();
    void mostrarColores() const;
    std::string obtenerColor(int opcion) const;
    void elegirColores();

    int determinarGanador(
        const Carta& carta1,
        const Carta& carta2
    ) const;

public:
    Juego();

    void jugarRonda();
    void mostrarEstado() const;

    void guardarPartida(
        const std::string& nombreArchivo
    ) const;

    void cargarPartida(
        const std::string& nombreArchivo
    );

    void mostrarGanador() const;
};

#endif