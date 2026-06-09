#pragma once
#include "EstadoDebate.hpp"

class EstadoTreplica : public EstadoDebate {
public:
    void processar(GerenciadorDebate& gerenciador) override;
};