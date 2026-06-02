#include "CandidatoBuilder.hpp"

CandidatoBuilder::CandidatoBuilder() {
    resultados = new CandidatoConcreto(0, "");
}

CandidatoBuilder::~CandidatoBuilder() {
    delete resultados;
}

void CandidatoBuilder::construirId(int id) {
    resultados->setId(id);
}

void CandidatoBuilder::construirNome(const std::string& nome) {
    resultados->setNome(nome);
}

void CandidatoBuilder::construirMicrofone(const Microfone& microfone) {
    resultados->setMicrofone(microfone);
}

CandidatoConcreto* CandidatoBuilder::getResultados() {
    return resultados;
}