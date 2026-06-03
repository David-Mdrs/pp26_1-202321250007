#pragma once
#include <vector>
#include <string>

#include "Fachada.hpp"
#include "../participantes/candidato/CandidatoConcreto.hpp"
#include "../participantes/eleitor/Eleitor.hpp"

class CLI {
public:
    static CLI& getInstance(Fachada& fachada);

    void run();

private:
    Fachada& fachada;
    std::vector<Candidato*> candidatos;
    std::vector<Eleitor*> eleitores;

    CLI(Fachada& fachada);
    void executarComando(const std::vector<std::string>& args);

    void cmdCriarCandidato(const std::vector<std::string>& args);
    void cmdCriarEleitor(const std::vector<std::string>& args);
    void cmdConfigurarDebate(const std::vector<std::string>& args);
};