#include "Candidato.hpp"
#include <algorithm>

void Candidato::cadastrar(ObservadorEleitor* observador) {
    if (!observador) return;

    if (std::find(eleitores.begin(), eleitores.end(), observador) == eleitores.end()) {
        eleitores.push_back(observador);
    }
}

void Candidato::remover(ObservadorEleitor* observador) {
    eleitores.erase(
        std::remove(eleitores.begin(), eleitores.end(), observador),
        eleitores.end()
    );
}

void Candidato::notificar(const std::string& mensagem) {
    for (auto* observador : eleitores) {
        if (observador) {
            observador->receberNotificacao(mensagem);
        }
    }
}