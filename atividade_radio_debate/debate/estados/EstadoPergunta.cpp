#include "EstadoPergunta.hpp"
#include "../GerenciadorDebate.hpp"

void EstadoPergunta::processar(GerenciadorDebate& gerenciador) {
    gerenciador.getInquiridor()->obterMicrofone().ligar();
    gerenciador.getInquirido()->obterMicrofone().desligar();
    gerenciador.registrarAcao("Estado: Pergunta");

    // Simulando candidato que pressiona o botão DR
    gerenciador.simularSolicitacoesDR();
}