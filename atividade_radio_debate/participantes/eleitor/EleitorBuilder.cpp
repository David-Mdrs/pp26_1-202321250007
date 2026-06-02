#include "EleitorBuilder.hpp"

EleitorBuilder::EleitorBuilder() {
    resultados = new Eleitor(0, "");
}

EleitorBuilder::~EleitorBuilder() {
    delete resultados;
}

void EleitorBuilder::construirId(int id) {
    resultados->setId(id);
}

void EleitorBuilder::construirNome(const std::string& nome) {
    resultados->setNome(nome);
}

void EleitorBuilder::construirCandidatoFavorito(CandidatoConcreto* candidato) {
    resultados->setCandidatoFavorito(candidato);
}

Eleitor* EleitorBuilder::getResultados() {
    Eleitor* temp = resultados;
    resultados = nullptr;
    return temp;
}
