#include "EstadoTreplica.hpp"
#include "../GerenciadorDebate.hpp"

void EstadoTreplica::processar(GerenciadorDebate& gerenciador) {
    gerenciador.getInquirido()->obterMicrofone().ligar();
    gerenciador.getInquiridor()->obterMicrofone().desligar();
    gerenciador.registrarAcao("Estado: Treplica");

    // Simulando candidato que pressiona o botão DR
    gerenciador.simularSolicitacoesDR();
}