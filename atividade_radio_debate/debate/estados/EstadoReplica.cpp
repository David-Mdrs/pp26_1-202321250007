#include "EstadoReplica.hpp"
#include "../GerenciadorDebate.hpp"

void EstadoReplica::processar(GerenciadorDebate& gerenciador) {
    std::cout << "Inquiridor " << gerenciador.getInquiridor()->getNome() << " - ";
    gerenciador.getInquiridor()->obterMicrofone().ligar();
    std::cout << "Inquirido " << gerenciador.getInquirido()->getNome() << " - ";
    gerenciador.getInquirido()->obterMicrofone().desligar();
    std::cout << std::endl;
    gerenciador.registrarAcao("Estado: Replica");

    // Simulando candidato que pressiona o botão DR
    gerenciador.simularSolicitacoesDR();
}