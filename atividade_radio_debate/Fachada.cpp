#include "Fachada.hpp"

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