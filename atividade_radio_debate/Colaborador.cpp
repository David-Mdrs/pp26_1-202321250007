#include "Colaborador.hpp"

Colaborador::Colaborador() {
    mediador = nullptr;
}

void Colaborador::setMediador(Mediador* mediador) {
    this->mediador = mediador;
}