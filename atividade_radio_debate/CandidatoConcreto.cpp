#include "CandidatoConcreto.hpp"

CandidatoConcreto::CandidatoConcreto(int id, const std::string& nome)
    : id(id), nome(nome), jaPerguntou(false), microfone(id) {
}

int CandidatoConcreto::getId() const {
    return id;
}

const std::string& CandidatoConcreto::getNome() const {
    return nome;
}

bool CandidatoConcreto::getJaPerguntou() const {
    return jaPerguntou;
}

Microfone& CandidatoConcreto::obterMicrofone() {
    return microfone;
}

const Microfone& CandidatoConcreto::obterMicrofone() const {
    return microfone;
}

void CandidatoConcreto::marcarComoInquiridor() {
    jaPerguntou = true;
}