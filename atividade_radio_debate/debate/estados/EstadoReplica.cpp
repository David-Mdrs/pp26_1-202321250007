#include "EstadoReplica.hpp"
#include "../GerenciadorDebate.hpp"

void EstadoReplica::processar(GerenciadorDebate& gerenciador) {
    gerenciador.registrarAcao("ESTADO INICIADO: Replica");

    std::cout << "Inquiridor " << gerenciador.getInquiridor()->getNome() << " - ";
    gerenciador.getInquiridor()->obterMicrofone().ligar();
    std::cout << "Inquirido " << gerenciador.getInquirido()->getNome() << " - ";
    gerenciador.getInquirido()->obterMicrofone().desligar();
    std::cout << std::endl;
    gerenciador.getCronometro().iniciar(gerenciador.getTempos()[2]);

    // Simulando candidato que pressiona o botão DR
    gerenciador.simularSolicitacoesDR();
}