#pragma once
#include "EstadoDebate.hpp"

class EstadoResposta : public EstadoDebate {
public:
    void processar(GerenciadorDebate& gerenciador) override;
};