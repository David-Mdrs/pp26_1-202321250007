#pragma once

#include "../Microfone.hpp"

class GerenciadorDebate;

class EstadoDebate {
public:
    virtual void processar(GerenciadorDebate& gerenciador) = 0;
    virtual ~EstadoDebate() = default;
};