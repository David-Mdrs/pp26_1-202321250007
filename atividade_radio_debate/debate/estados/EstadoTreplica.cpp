#include "EstadoTreplica.hpp"
#include "../GerenciadorDebate.hpp"

void EstadoTreplica::processar(GerenciadorDebate& gerenciador) {
    gerenciador.registrarAcao("Estado: Treplica");

    std::cout << "Inquiridor " << gerenciador.getInquiridor()->getNome() << " - ";
    gerenciador.getInquiridor()->obterMicrofone().desligar();
    std::cout << "Inquirido " << gerenciador.getInquirido()->getNome() << " - ";
    gerenciador.getInquirido()->obterMicrofone().ligar();
    std::cout << std::endl;
    gerenciador.getCronometro().iniciar(gerenciador.getTempos()[3]);

    // Simulando candidato que pressiona o botão DR
    gerenciador.simularSolicitacoesDR();
}