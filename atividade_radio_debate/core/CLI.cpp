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

// Inicialização da CLI e leitura da entrada
void CLI::run() {

    std::string input;

    std::cout << "\n=========================================================";
    std::cout << "\n================ CLI INICIADA - COMANDOS ================";
    std::cout << "\n=========================================================\n";

    std::cout << "CADASTRAR CANDIDATO  <id>  <nome>\n";
    std::cout << "CADASTRAR ELEITOR    <id>  <nome>  <nomeCandidatoFavorito>\n";
    std::cout << "CONFIGURAR DEBATE    <tempo1> <t2> <t3> <t4>\n";
    std::cout << "INICIAR DEBATE\n";
    std::cout << "PROXIMO\n";
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

// Execução do comando dado pelo usuário
void CLI::executarComando(const std::vector<std::string>& args) {

    // Inicialização do debate
    if (args[0] == "INICIAR" && args.size() >= 2 && args[1] == "DEBATE") {
        fachada.iniciarDebate();
        std::cout << "Debate iniciado.\n\n";
        }

    // Próxima fase do debate
    else if (args[0] == "PROXIMO") {
        fachada.avancarEtapa();
        std::cout << "Proxima fase executada.\n\n";
    }

    // Finalização do debate
    else if (args[0] == "FINALIZAR") {
        fachada.finalizarDebate();
        std::cout << "Debate finalizado.\n\n";
    }

    // Relatório do debate
    else if (args[0] == "RELATORIO") {
        fachada.gerarRelatorio();
        std::cout << std::endl;
    }

    // Cadastrar candidato
    else if (args[0] == "CADASTRAR" && args.size() >= 4 && args[1] == "CANDIDATO") {
        cmdCriarCandidato(args);
    }

    // Cadastrar eleitor
    else if (args[0] == "CADASTRAR" && args.size() >= 5 && args[1] == "ELEITOR") {
        cmdCriarEleitor(args);
    }

    // Inicializa configurações do debate
    else if (args[0] == "CONFIGURAR" && args.size() >= 3 && args[1] == "DEBATE") {
        cmdConfigurarDebate(args);
    }

    // Nenhum comando reconhecido
    else {
        std::cout << "Comando invalido.\n\n";
    }
}

// Cria um novo candidato e armazena do vetor temporário
void CLI::cmdCriarCandidato(const std::vector<std::string>& args) {
    int id = std::stoi(args[2]);
    std::string nome = args[3];
    Candidato* candidato = fachada.criarCandidato(id, nome);
    candidatos.push_back(candidato);
    std::cout << "Candidato " << nome << " cadastrado.\n\n";
}

// Cria um novo eleitor e armazena no vetor temporário
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

// Passa os candidatos/eleitores criados temporariamente e tempos para inicialização do debate
void CLI::cmdConfigurarDebate(const std::vector<std::string>& args) {
    std::vector<int> tempos;
    for (int i = 2; i < args.size(); i++) {
        tempos.push_back(std::stoi(args[i]));
    }
    fachada.configurarDebate(candidatos, tempos);
    std::cout << "Debate configurado.\n\n";
}