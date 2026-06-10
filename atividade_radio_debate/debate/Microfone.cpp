#include "Microfone.hpp"
#include <iostream>

Microfone::Microfone(int id) {
    this->id = id;
    ligado = false;
}

void Microfone::ligar() {
    ligado = true;
    std::cout << "Microfone Ligado.\n";
}

void Microfone::desligar() {
    ligado = false;
    std::cout << "Microfone Desligado.\n";
}

bool Microfone::estaLigado() const {
    return ligado;
}