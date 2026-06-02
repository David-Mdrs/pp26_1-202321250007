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

    std::cout << "\n====== CLI INICIADA ======";
    std::cout << "\n======== COMANDOS ========\n";

    std::cout << "iniciar debate\n";
    std::cout << "proximo\n";
    std::cout << "finalizar\n";
    std::cout << "relatorio\n";
    std::cout << "sair\n";

    std::cout << "==========================\n\n";

    while (true) {
        std::cout << "Comando: ";
        std::getline(std::cin, input);

        if (input == "sair") {
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

    // iniciar debate
    if (args[0] == "iniciar" &&
        args.size() >= 2 &&
        args[1] == "debate") {

        fachada.iniciarDebate();
        std::cout << "Debate iniciado.\n\n";
        }

    // proxima fase
    else if (args[0] == "proximo") {
        fachada.avancarEtapa();
        std::cout << "Proxima fase executada.\n\n";
    }

    // finalizar debate
    else if (args[0] == "finalizar") {
        fachada.finalizarDebate();
        std::cout << "Debate finalizado.\n\n";
    }

    // relatorio
    else if (args[0] == "relatorio") {
        fachada.gerarRelatorio();
        std::cout << std::endl;
    }

    else {
        std::cout << "Comando invalido.\n\n";
    }
}