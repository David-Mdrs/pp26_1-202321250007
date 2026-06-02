#include "Fachada.hpp"
#include "../participantes/candidato/CandidatoBuilder.hpp"
#include "../participantes/eleitor/EleitorBuilder.hpp"
#include "../participantes/candidato/CandidatoConcreto.hpp"

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

void Fachada::avancarEtapa() {
    gerenciador.proximaAcao();
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

// Métodos de criação que utilizam o padrão Builder
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