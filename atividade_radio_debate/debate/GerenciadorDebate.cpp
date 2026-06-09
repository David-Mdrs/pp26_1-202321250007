#include "GerenciadorDebate.hpp"
#include "Microfone.hpp"
#include "estados/EstadoPergunta.hpp"
#include "estados/EstadoResposta.hpp"
#include "estados/EstadoReplica.hpp"
#include "estados/EstadoTreplica.hpp"
#include "estados/EstadoDireitoResposta.hpp"

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

    logger.registrar("Debate configurado com " + std::to_string(candidatos.size()) + " candidato(s).");
}

void GerenciadorDebate::sortearInquiridor() {
    std::vector<Candidato*> disponiveis;

    for (auto* c : candidatos) {
        if (c && !c->getJaPerguntou()) {
            disponiveis.push_back(c);
        }
    }

    if (disponiveis.empty()) {
        logger.registrar("Todos os candidatos ja foram inquiridores.");
        inquiridor = nullptr;
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(disponiveis.size()) - 1);

    inquiridor = disponiveis[dist(gen)];
    inquiridor->marcarComoInquiridor();

    logger.registrar("Inquiridor sorteado: " + inquiridor->getNome());
}

void GerenciadorDebate::definirInquirido(int id) {
    for (auto* c : candidatos) {
        if (c && c->getId() == id && c != inquiridor) {
            inquirido = c;
            logger.registrar("Inquirido definido: " + c->getNome());
            return;
        }
    }
    logger.registrar("Candidato invalido");
}

void GerenciadorDebate::registrarAcao(const std::string& acao) {
    logger.registrar(acao);
}

void GerenciadorDebate::iniciarDebate() {
    sortearInquiridor();

    if (!inquiridor) {
        finalizarDebate();
        return;
    }

    for (auto* c : candidatos) {
        if (c && c != inquiridor) {
            inquirido = c;
            logger.registrar("Inquirido definido automaticamente: " + c->getNome());
            break;
        }
    }

    setEstado(new EstadoPergunta());
    processarEstado();
    cronometro.iniciar(tempos[0]);
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
        registrarAcao("Rodada finalizada");
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
        logger.registrar("Debate finalizado.");
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
    filaDR.push_back(candidato);
    registrarAcao("DR solicitado por: " + candidato->getNome());
}

void GerenciadorDebate::analisarSolicitacoesDR() {
    if (filaDR.empty()) {
        std::cout << "Nenhuma solicitacao de DR.\n";
        return;
    }
    for (Candidato* c : filaDR) {
        std::cout << c->getNome() << " solicitou DR\n";
    }
}

void GerenciadorDebate::concederDR(Candidato* candidato) {
    for (Candidato* c : filaDR) {
        if (c->getId() == candidato->getId()) {
            setEstado(new EstadoDireitoResposta());
            processarEstado();
            return;
        }
    }
    std::cout << "Candidato nao encontrado na fila de DR.\n";
}

void GerenciadorDebate::simularSolicitacoesDR() {
    std::uniform_int_distribution<int> dist(0, 1);
    std::random_device rd;
    std::mt19937 gen(rd());

    for (Candidato* c : candidatos) {
        if (dist(gen) == 1) {
            registrarSolicitacaoDR(c);
            std::cout << c->getNome() << " solicitou Direito de Resposta.\n";
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

void GerenciadorDebate::limparFilaDR() {
    filaDR.clear();
}