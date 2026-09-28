#ifndef CARTA_H
#define CARTA_H

#include <string>

class Carta {
private:
    std::string color;
    int poder;

public:
    Carta();
    Carta(const std::string& color, int poder);

    std::string getColor() const;
    int getPoder() const;

    void mostrar() const;
};

#endif