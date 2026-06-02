#include "Eleitor.hpp"
#include "../candidato/CandidatoConcreto.hpp"
#include <iostream>

Eleitor::Eleitor(int id, const std::string& nome, CandidatoConcreto* candidatoFavorito)
    : id(id), nome(nome), candidatoFavorito(nullptr) {
    setCandidatoFavorito(candidatoFavorito);
}

// Métodos get
int Eleitor::getId() const { return id; }
const std::string& Eleitor::getNome() const { return nome; }
CandidatoConcreto* Eleitor::getCandidatoFavorito() const { return candidatoFavorito; }

// Métodos set
void Eleitor::setId(int id) { this->id = id; }
void Eleitor::setNome(const std::string& nome) { this->nome = nome; }

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

// Método do padrão Builder
void Eleitor::receberNotificacao(const std::string& mensagem) {
    std::cout << "[Eleitor " << nome << "] " << mensagem << '\n';
}

// Método do padrão Prototype
ParticipantePrototype* Eleitor::clonar() {
    Eleitor* novo = new Eleitor(id, nome);
    novo->candidatoFavorito = candidatoFavorito;
    return novo;
}