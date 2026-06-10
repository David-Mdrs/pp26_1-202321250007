#include "EstadoPergunta.hpp"
#include "../GerenciadorDebate.hpp"

void EstadoPergunta::processar(GerenciadorDebate& gerenciador) {
    std::cout << "Inquiridor " << gerenciador.getInquiridor()->getNome() << " - ";
    gerenciador.getInquiridor()->obterMicrofone().ligar();
    std::cout << "Inquirido " << gerenciador.getInquirido()->getNome() << " - ";
    gerenciador.getInquirido()->obterMicrofone().desligar();
    std::cout << std::endl;
    gerenciador.registrarAcao("Estado: Pergunta");

    // Simulando candidato que pressiona o botão DR
    gerenciador.simularSolicitacoesDR();
}