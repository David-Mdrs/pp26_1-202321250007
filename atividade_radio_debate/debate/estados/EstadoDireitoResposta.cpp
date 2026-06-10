#include "EstadoDireitoResposta.hpp"
#include "../GerenciadorDebate.hpp"

void EstadoDireitoResposta::processar(GerenciadorDebate& gerenciador) {
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
        candidato->notificar("Candidato " + candidato->getNome() + " em Direito de Resposta");
        std::cout << candidato->getNome() << " - ";
        candidato->obterMicrofone().desligar();
    }
    gerenciador.limparFilaDR();
    gerenciador.registrarAcao("Estado: Direito de Resposta");
}