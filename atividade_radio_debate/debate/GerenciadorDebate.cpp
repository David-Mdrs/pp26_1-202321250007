#include "GerenciadorDebate.hpp"
#include "Microfone.hpp"

GerenciadorDebate::GerenciadorDebate()
    : inquiridor(nullptr),
      inquirido(nullptr),
      faseAtual("NULO"),
      tempos(4, 0),
      encerrado(false) {
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
    if (faseAtual == "NULO") {
        faseAtual = "PERGUNTA";
    }

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

void GerenciadorDebate::iniciarFase(int tempo) {
    if (!inquiridor || !inquirido) {
        logger.registrar("Nao foi possivel iniciar a fase: dupla nao definida.");
        return;
    }

    if (faseAtual == "PERGUNTA") {
        inquiridor->notificar("Candidato " + inquiridor->getNome() + " esta falando");
        std::cout << "\nMicrofone inquiridor " << inquiridor->getNome() <<  ": ";
        inquiridor->obterMicrofone().ligar();
        std::cout << "Microfone inquirido " << inquirido->getNome() <<  ": ";
        inquirido->obterMicrofone().desligar();
        std::cout << std::endl;
    }
    else if (faseAtual == "RESPOSTA") {
        inquirido->notificar("Candidato " + inquirido->getNome() + " esta falando");
        std::cout << "\nMicrofone inquiridor " << inquiridor->getNome() <<  ": ";
        inquirido->obterMicrofone().desligar();
        std::cout << "Microfone inquirido " << inquirido->getNome() <<  ": ";
        inquiridor->obterMicrofone().ligar();
        std::cout << std::endl;
    }
    else if (faseAtual == "REPLICA") {
        inquiridor->notificar("Candidato " + inquiridor->getNome() + " esta falando");
        std::cout << "\nMicrofone inquiridor " << inquiridor->getNome() <<  ": ";
        inquiridor->obterMicrofone().ligar();
        std::cout << "Microfone inquirido " << inquirido->getNome() <<  ": ";
        inquirido->obterMicrofone().desligar();
        std::cout << std::endl;
    }
    else if (faseAtual == "TREPLICA") {
        inquirido->notificar("Candidato " + inquirido->getNome() + " esta falando");
        std::cout << "\nMicrofone inquiridor " << inquiridor->getNome() <<  ": ";
        inquirido->obterMicrofone().desligar();
        std::cout << "Microfone inquirido " << inquirido->getNome() <<  ": ";
        inquiridor->obterMicrofone().ligar();
        std::cout << std::endl;
    }

    cronometro.iniciar(tempo);
    registrarAcao("Fase iniciada: " + faseAtual);
    std::cout << std::endl;
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

    if (candidatos.size() > 1) {
        for (auto* c : candidatos) {
            if (c && c != inquiridor) {
                inquirido = c;
                logger.registrar("Inquirido definido automaticamente: " + c->getNome());
                std::cout << std::endl;
                break;
            }
        }
    }

    faseAtual = "PERGUNTA";
    iniciarFase(tempos[0]);
}

void GerenciadorDebate::proximaAcao() {
    cronometro.finalizarTempo();

    if (faseAtual == "PERGUNTA") {
        faseAtual = "RESPOSTA";
        iniciarFase(tempos[1]);
    }
    else if (faseAtual == "RESPOSTA") {
        faseAtual = "REPLICA";
        iniciarFase(tempos[2]);
    }
    else if (faseAtual == "REPLICA") {
        faseAtual = "TREPLICA";
        iniciarFase(tempos[3]);
    }
    else if (faseAtual == "TREPLICA") {
        registrarAcao("Rodada finalizada");
    }
}

void GerenciadorDebate::finalizarDebate() {
    if (inquiridor) {
        std::cout << "\nMicrofone inquiridor " << inquiridor->getNome() <<  ": ";
        inquiridor->obterMicrofone().desligar();
    }

    if (inquirido) {
        std::cout << "\nMicrofone inquirido " << inquirido->getNome() <<  ": ";
        inquirido->obterMicrofone().desligar();
    }

    std::cout << std::endl;

    if (!encerrado) {
        logger.registrar("Debate finalizado.");
        std::cout << std::endl;
    }

    encerrado = true;
    faseAtual = "FINALIZADO";
}

bool GerenciadorDebate::estaEncerrado() const {
    return encerrado;
}

void GerenciadorDebate::gerarRelatorio() const {
    logger.gerarRelatorio();
}