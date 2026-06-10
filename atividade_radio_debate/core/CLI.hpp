#pragma once
#include <vector>
#include <string>

#include "Fachada.hpp"
#include "../participantes/candidato/CandidatoConcreto.hpp"
#include "../participantes/eleitor/Eleitor.hpp"

enum class EstadoCLI {
    CONFIGURACAO,
    AGUARDANDO_PERGUNTA,
    AGUARDANDO_RESPOSTA,
    AGUARDANDO_REPLICA,
    AGUARDANDO_TREPLICA,
    AGUARDANDO_DR,
    FINALIZADO
};

class CLI {
public:
    static CLI& getInstance(Fachada& fachada);
    void run();

private:
    Fachada& fachada;
    EstadoCLI estadoCLI;
    bool debateConfigurado;
    std::vector<Candidato*> candidatos;
    std::vector<Eleitor*> eleitores;

    CLI(Fachada& fachada);
    void executarComando(const std::vector<std::string>& args);
    void exibirComandos();

    void cmdCriarCandidato(const std::vector<std::string>& args);
    void cmdCriarEleitor(const std::vector<std::string>& args);
    void cmdConfigurarDebate(const std::vector<std::string>& args);
    void cmdConcederDR(const std::vector<std::string>& args);
};