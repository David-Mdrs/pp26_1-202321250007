#pragma once
#include "EstadoDebate.hpp"

class EstadoDireitoResposta : public EstadoDebate {
public:
    void processar(GerenciadorDebate& gerenciador) override;
};