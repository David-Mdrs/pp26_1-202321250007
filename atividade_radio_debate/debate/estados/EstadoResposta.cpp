#include "EstadoResposta.hpp"
#include "../GerenciadorDebate.hpp"

void EstadoResposta::processar(GerenciadorDebate& gerenciador) {
    std::cout << "Inquiridor " << gerenciador.getInquiridor()->getNome() << " - ";
    gerenciador.getInquiridor()->obterMicrofone().desligar();
    std::cout << "Inquirido " << gerenciador.getInquirido()->getNome() << " - ";
    gerenciador.getInquirido()->obterMicrofone().ligar();
    std::cout << std::endl;
    gerenciador.registrarAcao("Estado: Resposta");

    // Simulando candidato que pressiona o botão DR
    gerenciador.simularSolicitacoesDR();
}