#include "Carta.h"
#include <iostream>

Carta::Carta() {
    color = "";
    poder = 0;
}

Carta::Carta(const std::string& color, int poder) {
    this->color = color;
    this->poder = poder;
}

std::string Carta::getColor() const {
    return color;
}

int Carta::getPoder() const {
    return poder;
}

void Carta::mostrar() const {
    std::cout << "Color: " << color
              << " | Poder: " << poder << std::endl;
}