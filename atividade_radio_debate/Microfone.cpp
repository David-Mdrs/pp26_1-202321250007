#include "Microfone.hpp"
#include <iostream>

Microfone::Microfone(int id) {
    this->id = id;
    ligado = false;
}

void Microfone::ligar() {
    ligado = true;
    std::cout << "Ligado.\n";
}

void Microfone::desligar() {
    ligado = false;
    std::cout << "Desligado.\n";
}

bool Microfone::estaLigado() const {
    return ligado;
}