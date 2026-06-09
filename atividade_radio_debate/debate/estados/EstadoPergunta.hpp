#pragma once
#include "EstadoDebate.hpp"

class EstadoPergunta : public EstadoDebate {
public:
    void processar(GerenciadorDebate& gerenciador) override;
};