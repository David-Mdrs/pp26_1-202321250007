#include "Cronometro.hpp"
#include <iostream>

Cronometro::Cronometro() {
    tempoAtual = 0;
}

#include <thread>
#include <chrono>

void Cronometro::iniciar(int tempo) {
    tempoAtual = tempo;
    std::cout << "Tempo iniciado: " << tempoAtual << " segundo(s).\n";
    std::cout << tempoAtual;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    for (int i = tempoAtual - 1; i > 0; i--) {
        std::cout << " - " << i;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "\nTempo encerrado.\n\n";
}

void Cronometro::finalizarTempo() {
    std::cout << "Tempo encerrado.\n\n";
}