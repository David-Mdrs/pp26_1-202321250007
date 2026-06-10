#include "EstadoDireitoResposta.hpp"
#include "../GerenciadorDebate.hpp"

void EstadoDireitoResposta::processar(GerenciadorDebate& gerenciador) {
    gerenciador.registrarAcao("Estado: Direito de Resposta");
    for (Candidato* candidato : gerenciador.getFilaDR()) {

        // Desliga microfone de todos antes de cada defesa
        for (Candidato* c : gerenciador.getCandidatos()) {
            if (c != candidato) {
                std::cout << c->getNome() << " - ";
                c->obterMicrofone().desligar();
            }
        }

        std::cout << candidato->getNome() << " - ";
        candidato->obterMicrofone().ligar();
        candidato->notificar("Candidato " + candidato->getNome() + " em Direito de Resposta\n");
        gerenciador.getCronometro().iniciar(gerenciador.getTempos()[4]);
        std::cout << candidato->getNome() << " - ";
        candidato->obterMicrofone().desligar();
    }
}