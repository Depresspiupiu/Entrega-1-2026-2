#ifndef JUEGO_H
#define JUEGO_H

#include "Carta.h"
#include "Jugador.h"
#include <vector>
#include <string>

class Juego {
private:
    std::vector<Jugador> jugadores;

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
        const std::vector<Carta>& cartas,
        bool buscarMayor
    ) const;
    void repartirCartas();

public:
    explicit Juego(int cantidadJugadores = 2);
    void nuevaPartida(int cantidadJugadores);

    void jugarRonda();
    void mostrarEstado() const;
    bool estaTerminada() const;

    void guardarPartida(
        const std::string& nombreArchivo
    ) const;

    bool cargarPartida(
        const std::string& nombreArchivo
    );

    void mostrarGanador() const;
};

#endif