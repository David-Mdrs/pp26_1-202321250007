#include "EstadoResposta.hpp"
#include "../GerenciadorDebate.hpp"

void EstadoResposta::processar(GerenciadorDebate& gerenciador) {
    gerenciador.getInquirido()->obterMicrofone().ligar();
    gerenciador.getInquiridor()->obterMicrofone().desligar();
    gerenciador.registrarAcao("Estado: Resposta");

    // Simulando candidato que pressiona o botão DR
    gerenciador.simularSolicitacoesDR();
}