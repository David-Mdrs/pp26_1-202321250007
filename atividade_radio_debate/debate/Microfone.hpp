#pragma once

class Microfone {
private:
    int id;
    bool ligado;

public:
    Microfone(int id = 0);

    void ligar();
    void desligar();

    bool estaLigado() const;
};