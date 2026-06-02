#pragma once

class Mediador;

class Colaborador {
protected:
    Mediador* mediador;

public:
    Colaborador();
    void setMediador(Mediador* mediador);
};