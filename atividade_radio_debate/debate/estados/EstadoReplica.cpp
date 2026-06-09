#include "EstadoReplica.hpp"
#include "../GerenciadorDebate.hpp"

void EstadoReplica::processar(GerenciadorDebate& gerenciador) {
    gerenciador.getInquiridor()->obterMicrofone().ligar();
    gerenciador.getInquirido()->obterMicrofone().desligar();
    gerenciador.registrarAcao("Estado: Replica");

    // Simulando candidato que pressiona o botão DR
    gerenciador.simularSolicitacoesDR();
}