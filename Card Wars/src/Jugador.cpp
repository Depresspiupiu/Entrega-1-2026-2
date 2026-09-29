#include "Jugador.h"
#include <iostream>

Jugador::Jugador() {
    nombre = "";
    puntaje = 0;
}

Jugador::Jugador(const std::string& nombre) {
    this->nombre = nombre;
    puntaje = 0;
}

std::string Jugador::getNombre() const {
    return nombre;
}

int Jugador::getPuntaje() const {
    return puntaje;
}

void Jugador::sumarPuntos(int puntos) {
    puntaje += puntos;
}

void Jugador::establecerPuntaje(int puntos) {
    puntaje = puntos;
}

void Jugador::mostrarPuntaje() const {
    std::cout << nombre << ": "
              << puntaje << " puntos" << std::endl;
}

const std::vector<Carta>& Jugador::getCartas() const {
    return cartas;
}

void Jugador::recibirCarta(const Carta& carta) {
    cartas.push_back(carta);
}

Carta Jugador::jugarCarta(std::size_t indice) {
    Carta carta = cartas.at(indice);
    cartas.erase(cartas.begin() + indice);
    return carta;
}

void Jugador::limpiarCartas() {
    cartas.clear();
}