#include "Fachada.hpp"
#include "../participantes/candidato/CandidatoBuilder.hpp"
#include "../participantes/eleitor/EleitorBuilder.hpp"
#include "../participantes/candidato/CandidatoConcreto.hpp"
#include "../debate/estados/EstadoPergunta.hpp"
#include "../debate/estados/EstadoResposta.hpp"
#include "../debate/estados/EstadoReplica.hpp"
#include "../debate/estados/EstadoTreplica.hpp"

Fachada::Fachada() {
}

Fachada& Fachada::getInstance() {
    static Fachada instancia;
    return instancia;
}

void Fachada::configurarDebate(const std::vector<Candidato*>& candidatos,
                               const std::vector<int>& tempos) {
    gerenciador.configurarDebate(candidatos, tempos);
}

void Fachada::sortearInquiridor() {
    gerenciador.sortearInquiridor();
}

void Fachada::definirInquirido(int id) {
    gerenciador.definirInquirido(id);
}

void Fachada::iniciarDebate() {
    gerenciador.iniciarDebate();
}

void Fachada::finalizarDebate() {
    gerenciador.finalizarDebate();
}

bool Fachada::debateEncerrado() const {
    return gerenciador.estaEncerrado();
}

void Fachada::gerarRelatorio() const {
    gerenciador.gerarRelatorio();
}

// State
void Fachada::iniciarPergunta() {
    gerenciador.setEstado(new EstadoPergunta());
    gerenciador.processarEstado();
}

void Fachada::iniciarResposta() {
    gerenciador.setEstado(new EstadoResposta());
    gerenciador.processarEstado();
}

void Fachada::iniciarReplica() {
    gerenciador.setEstado(new EstadoReplica());
    gerenciador.processarEstado();
}

void Fachada::iniciarTreplica() {
    gerenciador.setEstado(new EstadoTreplica());
    gerenciador.processarEstado();
}

// DR
void Fachada::analisarSolicitacoesDR() {
    gerenciador.analisarSolicitacoesDR();
}

void Fachada::concederDR(int idCandidato) {
    for (Candidato* c : gerenciador.getFilaDR()) {
        if (c->getId() == idCandidato) {
            gerenciador.concederDR(c);
            return;
        }
    }
    std::cout << "Candidato nao encontrado na fila de DR.\n";
}

// Builder
Candidato* Fachada::criarCandidato(int id, const std::string& nome) {
    CandidatoBuilder builder;
    builder.construirId(id);
    builder.construirNome(nome);
    return builder.getResultados();
}

Eleitor* Fachada::criarEleitor(int id, const std::string& nome, Candidato* candidatoFavorito) {
    EleitorBuilder builder;
    builder.construirId(id);
    builder.construirNome(nome);
    if (candidatoFavorito != nullptr) {
        builder.construirCandidatoFavorito(dynamic_cast<CandidatoConcreto*>(candidatoFavorito));
    }
    return builder.getResultados();
}

// Prototype
Candidato* Fachada::clonarCandidato(Candidato* candidato) {
    CandidatoConcreto* concreto = dynamic_cast<CandidatoConcreto*>(candidato);
    return dynamic_cast<Candidato*>(concreto->clonar());
}

Eleitor* Fachada::clonarEleitor(Eleitor* eleitor) {
    return dynamic_cast<Eleitor*>(eleitor->clonar());
}