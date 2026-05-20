#include "Eleitor.hpp"
#include "CandidatoConcreto.hpp"
#include <iostream>

Eleitor::Eleitor(int id, const std::string& nome, CandidatoConcreto* candidatoFavorito)
    : id(id), nome(nome), candidatoFavorito(nullptr) {
    setCandidatoFavorito(candidatoFavorito);
}

void Eleitor::setCandidatoFavorito(CandidatoConcreto* candidato) {
    if (candidatoFavorito == candidato) return;

    if (candidatoFavorito != nullptr) {
        candidatoFavorito->remover(this);
    }

    candidatoFavorito = candidato;

    if (candidatoFavorito != nullptr) {
        candidatoFavorito->cadastrar(this);
    }
}

void Eleitor::receberNotificacao(const std::string& mensagem) {
    std::cout << "[Eleitor " << nome << "] " << mensagem << '\n';
}

int Eleitor::getId() const {
    return id;
}

const std::string& Eleitor::getNome() const {
    return nome;
}

CandidatoConcreto* Eleitor::getCandidatoFavorito() const {
    return candidatoFavorito;
}