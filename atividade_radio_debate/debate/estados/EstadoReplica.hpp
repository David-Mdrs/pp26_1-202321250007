#pragma once
#include "EstadoDebate.hpp"

class EstadoReplica : public EstadoDebate {
public:
    void processar(GerenciadorDebate& gerenciador) override;
};