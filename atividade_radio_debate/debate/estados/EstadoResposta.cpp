#include "EstadoResposta.hpp"
#include "../GerenciadorDebate.hpp"

void EstadoResposta::processar(GerenciadorDebate& gerenciador) {
    gerenciador.registrarAcao("ESTADO INICIADO: Resposta");

    std::cout << "Inquiridor " << gerenciador.getInquiridor()->getNome() << " - ";
    gerenciador.getInquiridor()->obterMicrofone().desligar();
    std::cout << "Inquirido " << gerenciador.getInquirido()->getNome() << " - ";
    gerenciador.getInquirido()->obterMicrofone().ligar();
    std::cout << std::endl;
    gerenciador.getCronometro().iniciar(gerenciador.getTempos()[1]);

    // Simulando candidato que pressiona o botão DR
    gerenciador.simularSolicitacoesDR();
}