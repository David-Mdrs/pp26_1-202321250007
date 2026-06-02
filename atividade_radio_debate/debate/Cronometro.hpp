#pragma once

class Cronometro {
private:
    int tempoAtual;

public:
    Cronometro();

    void iniciar(int tempo);
    void finalizarTempo();
};