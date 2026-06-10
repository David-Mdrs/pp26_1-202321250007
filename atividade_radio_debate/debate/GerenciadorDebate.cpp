#include "GerenciadorDebate.hpp"
#include "Microfone.hpp"
#include "estados/EstadoPergunta.hpp"
#include "estados/EstadoResposta.hpp"
#include "estados/EstadoReplica.hpp"
#include "estados/EstadoTreplica.hpp"
#include "estados/EstadoDireitoResposta.hpp"
#include "../participantes/candidato/CandidatoConcreto.hpp"
#include <chrono>

GerenciadorDebate::GerenciadorDebate()
    : inquiridor(nullptr),
      inquirido(nullptr),
      tempos(4, 0),
      encerrado(false),
      estadoAtual(nullptr) {
}

Candidato* GerenciadorDebate::buscarCandidatoPorId(int id) const {
    for (auto* c : candidatos) {
        if (c && c->getId() == id) {
            return c;
        }
    }
    return nullptr;
}

void GerenciadorDebate::configurarDebate(const std::vector<Candidato*>& novosCandidatos,
                                         const std::vector<int>& novosTempos) {
    candidatos = novosCandidatos;
    tempos = novosTempos;

    if (tempos.size() < 4) {
        tempos.resize(4, 0);
    }

    std::string logTempos = "TEMPO CONFIGURADO: ";
    for (int i = 0; i < (int)tempos.size(); i++) {
        logTempos += std::to_string(tempos[i]) + "s";
        if (i < (int)tempos.size() - 1) logTempos += ", ";
    }
    logger.registrar(logTempos);
}

void GerenciadorDebate::sortearInquiridor() {
    std::vector<Candidato*> disponiveis;

    for (auto* c : candidatos) {
        if (c && !c->getJaPerguntou()) {
            disponiveis.push_back(c);
        }
    }

    if (disponiveis.empty()) {
        logger.registrar("TODOS OS CANDIDATOS JA FORAM INQUIRIDORES.");
        inquiridor = nullptr;
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(disponiveis.size()) - 1);

    inquiridor = disponiveis[dist(gen)];
    inquiridor->marcarComoInquiridor();

    logger.registrar("INQUIRIDOR: " + inquiridor->getNome());

    // Redefinir inquirido automaticamente
    inquirido = nullptr;
    for (auto* c : candidatos) {
        if (c && c != inquiridor) {
            inquirido = c;
            logger.registrar("INQUIRIDO: " + c->getNome());
            break;
        }
    }
}

void GerenciadorDebate::definirInquirido(int id) {
    for (auto* c : candidatos) {
        if (c && c->getId() == id && c != inquiridor) {
            inquirido = c;
            logger.registrar("INQUIRIDO: " + c->getNome());
            return;
        }
    }
    logger.registrar("Candidato invalido");
}

void GerenciadorDebate::registrarAcao(const std::string& acao) {
    logger.registrar(acao);
}

void GerenciadorDebate::iniciarDebate() {
    logger.registrar("DEBATE INICIADO");
    sortearInquiridor();

    if (!inquiridor) {
        finalizarDebate();
    }
}

void GerenciadorDebate::proximaAcao() {
    cronometro.finalizarTempo();

    if (dynamic_cast<EstadoPergunta*>(estadoAtual)) {
        setEstado(new EstadoResposta());
        processarEstado();
        cronometro.iniciar(tempos[1]);
    }
    else if (dynamic_cast<EstadoResposta*>(estadoAtual)) {
        setEstado(new EstadoReplica());
        processarEstado();
        cronometro.iniciar(tempos[2]);
    }
    else if (dynamic_cast<EstadoReplica*>(estadoAtual)) {
        setEstado(new EstadoTreplica());
        processarEstado();
        cronometro.iniciar(tempos[3]);
    }
    else if (dynamic_cast<EstadoTreplica*>(estadoAtual)) {
        registrarAcao("RODADA FINALIZADA");
    }
}

void GerenciadorDebate::finalizarDebate() {
    if (inquiridor) {
        inquiridor->obterMicrofone().desligar();
    }
    if (inquirido) {
        inquirido->obterMicrofone().desligar();
    }

    if (!encerrado) {
        logger.registrar("DEBATE FINALIZADO.");
    }

    encerrado = true;
}

bool GerenciadorDebate::estaEncerrado() const {
    return encerrado;
}

void GerenciadorDebate::gerarRelatorio() const {
    logger.gerarRelatorio();
}

// Métodos do padrão State
void GerenciadorDebate::setEstado(EstadoDebate* estado) {
    delete estadoAtual;
    estadoAtual = estado;
}

void GerenciadorDebate::processarEstado() {
    if (estadoAtual) {
        estadoAtual->processar(*this);
    }
}

// Métodos para implementação da DR
void GerenciadorDebate::registrarSolicitacaoDR(Candidato* candidato) {
    for (Candidato* c : filaDR) {
        if (c->getId() == candidato->getId()) {
            return;
        }
    }
    filaDR.push_back(candidato);
    registrarAcao("DR SOLICITADA: " + candidato->getNome());
}

void GerenciadorDebate::analisarSolicitacoesDR() {
    if (filaDR.empty()) {
        registrarAcao("DRs ANALISADAS: Sem DRs");
        std::cout << "Nenhuma solicitacao de DR.\n";
        return;
    }
    for (Candidato* c : filaDR) {
        std::cout << "[" << c->getId() << "] " << c->getNome() << "\n";
    }
    registrarAcao("DRs ANALISADAS: " + std::to_string(filaDR.size()) + " DRs");
}

void GerenciadorDebate::concederDR(Candidato* candidato) {
    registrarAcao("DR CONCEDIDA: [" + std::to_string(candidato->getId()) + "] " + candidato->getNome());
    for (auto it = filaDR.begin(); it != filaDR.end(); ++it) {
        if ((*it)->getId() == candidato->getId()) {
            setEstado(new EstadoDireitoResposta());
            processarEstado();
            filaDR.erase(it);
            return;
        }
    }
    std::cout << "Candidato nao encontrado na fila de DR.\n";
}

void GerenciadorDebate::simularSolicitacoesDR() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    for (Candidato* c : candidatos) {
        if (c == inquiridor || c == inquirido) continue;

        CandidatoConcreto* concreto = dynamic_cast<CandidatoConcreto*>(c);
        if (concreto && concreto->solicitarDireitoResposta()) {
            registrarSolicitacaoDR(c);
            std::cout << c->getNome() << " solicitou Direito de Resposta.\n\n";
        }
    }
}

// Métodos get
Candidato* GerenciadorDebate::getInquiridor() const {
    return inquiridor;
}

Candidato* GerenciadorDebate::getInquirido() const {
    return inquirido;
}

const std::vector<Candidato*>& GerenciadorDebate::getCandidatos() const {
    return candidatos;
}

std::vector<Candidato*>& GerenciadorDebate::getFilaDR() {
    return filaDR;
}

const std::vector<int>& GerenciadorDebate::getTempos() const {
    return tempos;
}

Cronometro& GerenciadorDebate::getCronometro() {
    return cronometro;
}

void GerenciadorDebate::limparFilaDR() {
    filaDR.clear();
}