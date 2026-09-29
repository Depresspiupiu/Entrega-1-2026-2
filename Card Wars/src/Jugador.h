#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <cstddef>
#include <vector>
#include "Carta.h"

class Jugador {
private:
    std::string nombre;
    int puntaje;
    std::vector<Carta> cartas;

public:
    Jugador();
    Jugador(const std::string& nombre);

    std::string getNombre() const;
    int getPuntaje() const;

    void sumarPuntos(int puntos);
    void establecerPuntaje(int puntos);
    void mostrarPuntaje() const;
    const std::vector<Carta>& getCartas() const;
    void recibirCarta(const Carta& carta);
    Carta jugarCarta(std::size_t indice);
    void limpiarCartas();
};

#endif