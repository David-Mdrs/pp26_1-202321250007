#include "Cronometro.hpp"
#include <iostream>

Cronometro::Cronometro() {
    tempoAtual = 0;
}

void Cronometro::iniciar(int tempo) {
    tempoAtual = tempo;
    std::cout << "Duracao: " << tempoAtual << " segundo(s).\n\n";
}

void Cronometro::finalizarTempo() {
    std::cout << "Tempo encerrado.\n\n";
}