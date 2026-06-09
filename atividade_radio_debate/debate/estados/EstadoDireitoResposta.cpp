#include "EstadoDireitoResposta.hpp"
#include "../GerenciadorDebate.hpp"

void EstadoDireitoResposta::processar(GerenciadorDebate& gerenciador) {
    for (Candidato* candidato : gerenciador.getFilaDR()) {
        candidato->obterMicrofone().ligar();
        candidato->notificar("Candidato " + candidato->getNome() + " em Direito de Resposta");
        candidato->obterMicrofone().desligar();
    }
    gerenciador.limparFilaDR();
    gerenciador.registrarAcao("Estado: Direito de Resposta");
}