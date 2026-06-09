#include "CLI.hpp"

#include <iostream>
#include <sstream>

CLI& CLI::getInstance(Fachada& fachada) {
    static CLI instance(fachada);
    return instance;
}

CLI::CLI(Fachada& fachada)
    : fachada(fachada) {
}

void CLI::run() {

    std::string input;

    std::cout << "\n=========================================================";
    std::cout << "\n================ CLI INICIADA - COMANDOS ================";
    std::cout << "\n=========================================================\n";

    std::cout << "CADASTRAR CANDIDATO  <id>  <nome>\n";
    std::cout << "CADASTRAR ELEITOR    <id>  <nome>  <nomeCandidatoFavorito>\n";
    std::cout << "CONFIGURAR DEBATE    <tempo1> <t2> <t3> <t4>\n";
    std::cout << "INICIAR DEBATE\n";
    std::cout << "INICIAR PERGUNTA\n";
    std::cout << "INICIAR RESPOSTA\n";
    std::cout << "INICIAR REPLICA\n";
    std::cout << "INICIAR TREPLICA\n";
    std::cout << "ANALISAR DR\n";
    std::cout << "CONCEDER DR          <idCandidato>\n";
    std::cout << "FINALIZAR\n";
    std::cout << "RELATORIO\n";
    std::cout << "SAIR\n";

    std::cout << "=========================================================\n\n";

    while (true) {
        std::cout << "Comando: ";
        std::getline(std::cin, input);

        if (input == "SAIR") {
            break;
        }

        std::istringstream iss(input);
        std::vector<std::string> args;
        std::string palavra;

        while (iss >> palavra) {
            args.push_back(palavra);
        }

        if (!args.empty()) {
            executarComando(args);
        }
    }
}

void CLI::executarComando(const std::vector<std::string>& args) {

    if (args[0] == "INICIAR" && args.size() >= 2 && args[1] == "DEBATE") {
        fachada.iniciarDebate();
        std::cout << "Debate iniciado.\n\n";
    }
    else if (args[0] == "INICIAR" && args.size() >= 2 && args[1] == "PERGUNTA") {
        fachada.iniciarPergunta();
        std::cout << "Fase de pergunta iniciada.\n\n";
    }
    else if (args[0] == "INICIAR" && args.size() >= 2 && args[1] == "RESPOSTA") {
        fachada.iniciarResposta();
        std::cout << "Fase de resposta iniciada.\n\n";
    }
    else if (args[0] == "INICIAR" && args.size() >= 2 && args[1] == "REPLICA") {
        fachada.iniciarReplica();
        std::cout << "Fase de replica iniciada.\n\n";
    }
    else if (args[0] == "INICIAR" && args.size() >= 2 && args[1] == "TREPLICA") {
        fachada.iniciarTreplica();
        std::cout << "Fase de treplica iniciada.\n\n";
    }
    else if (args[0] == "ANALISAR" && args.size() >= 2 && args[1] == "DR") {
        fachada.analisarSolicitacoesDR();
        std::cout << std::endl;
    }
    else if (args[0] == "CONCEDER" && args.size() >= 3 && args[1] == "DR") {
        cmdConcederDR(args);
    }
    else if (args[0] == "FINALIZAR") {
        fachada.finalizarDebate();
        std::cout << "Debate finalizado.\n\n";
    }
    else if (args[0] == "RELATORIO") {
        fachada.gerarRelatorio();
        std::cout << std::endl;
    }
    else if (args[0] == "CADASTRAR" && args.size() >= 4 && args[1] == "CANDIDATO") {
        cmdCriarCandidato(args);
    }
    else if (args[0] == "CADASTRAR" && args.size() >= 5 && args[1] == "ELEITOR") {
        cmdCriarEleitor(args);
    }
    else if (args[0] == "CONFIGURAR" && args.size() >= 3 && args[1] == "DEBATE") {
        cmdConfigurarDebate(args);
    }
    else {
        std::cout << "Comando invalido.\n\n";
    }
}

void CLI::cmdCriarCandidato(const std::vector<std::string>& args) {
    int id = std::stoi(args[2]);
    std::string nome = args[3];
    Candidato* candidato = fachada.criarCandidato(id, nome);
    candidatos.push_back(candidato);
    std::cout << "Candidato " << nome << " cadastrado.\n\n";
}

void CLI::cmdCriarEleitor(const std::vector<std::string>& args) {
    int id = std::stoi(args[2]);
    std::string nome = args[3];
    std::string nomeFavorito = args[4];

    Candidato* favorito = nullptr;
    for (Candidato* c : candidatos) {
        if (c->getNome() == nomeFavorito) {
            favorito = c;
            break;
        }
    }

    if (favorito == nullptr) {
        std::cout << "Candidato favorito nao encontrado.\n\n";
        return;
    }

    Eleitor* eleitor = fachada.criarEleitor(id, nome, favorito);
    eleitores.push_back(eleitor);
    std::cout << "Eleitor " << nome << " cadastrado.\n\n";
}

void CLI::cmdConfigurarDebate(const std::vector<std::string>& args) {
    std::vector<int> tempos;
    for (int i = 2; i < (int)args.size(); i++) {
        tempos.push_back(std::stoi(args[i]));
    }
    fachada.configurarDebate(candidatos, tempos);
    std::cout << "Debate configurado.\n\n";
}

void CLI::cmdConcederDR(const std::vector<std::string>& args) {
    int id = std::stoi(args[2]);
    fachada.concederDR(id);
    std::cout << "DR concedido.\n\n";
}