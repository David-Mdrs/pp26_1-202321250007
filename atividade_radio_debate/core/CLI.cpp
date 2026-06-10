#include "CLI.hpp"
#include <iostream>
#include <sstream>

CLI& CLI::getInstance(Fachada& fachada) {
    static CLI instance(fachada);
    return instance;
}

CLI::CLI(Fachada& fachada)
    : fachada(fachada), estadoCLI(EstadoCLI::CONFIGURACAO), debateConfigurado(false) {
}

void CLI::exibirComandos() {
    std::cout << "\n=========================================================\n";

    if (estadoCLI == EstadoCLI::CONFIGURACAO) {
        std::cout << "CADASTRAR CANDIDATO  <id>  <nome>\n";
        std::cout << "CADASTRAR ELEITOR    <id>  <nome>  <nomeCandidatoFavorito>\n";
        std::cout << "CONFIGURAR DEBATE    <tempo1> <t2> <t3> <t4>\n";
        std::cout << "INICIAR DEBATE\n";
    }
    else if (estadoCLI == EstadoCLI::AGUARDANDO_PERGUNTA) {
        std::cout << "INICIAR PERGUNTA\n";
        std::cout << "FINALIZAR\n";
        std::cout << "RELATORIO\n";
    }
    else if (estadoCLI == EstadoCLI::AGUARDANDO_RESPOSTA) {
        std::cout << "INICIAR RESPOSTA\n";
    }
    else if (estadoCLI == EstadoCLI::AGUARDANDO_REPLICA) {
        std::cout << "INICIAR REPLICA\n";
    }
    else if (estadoCLI == EstadoCLI::AGUARDANDO_TREPLICA) {
        std::cout << "INICIAR TREPLICA\n";
    }
    else if (estadoCLI == EstadoCLI::AGUARDANDO_DR) {
        std::cout << "ANALISAR DR\n";
        std::cout << "CONCEDER DR          <idCandidato>\n";
        std::cout << "PROXIMO ROUND\n";
        std::cout << "FINALIZAR\n";
        std::cout << "RELATORIO\n";
    }
    else if (estadoCLI == EstadoCLI::FINALIZADO) {
        std::cout << "RELATORIO\n";
    }

    std::cout << "SAIR\n";
    std::cout << "=========================================================\n\n";
}

void CLI::run() {
    std::string input;

    while (true) {
        exibirComandos();

        std::cout << "Comando: ";
        std::getline(std::cin, input);

        if (input == "SAIR") break;

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

    // CONFIGURACAO
    if (estadoCLI == EstadoCLI::CONFIGURACAO) {
        if (args[0] == "CADASTRAR" && args.size() >= 4 && args[1] == "CANDIDATO") {
            cmdCriarCandidato(args);
        }
        else if (args[0] == "CADASTRAR" && args.size() >= 5 && args[1] == "ELEITOR") {
            cmdCriarEleitor(args);
        }
        else if (args[0] == "CONFIGURAR" && args.size() >= 3 && args[1] == "DEBATE") {
            cmdConfigurarDebate(args);
        }
        else if (args[0] == "INICIAR" && args.size() >= 2 && args[1] == "DEBATE") {
            if (candidatos.size() < 2) {
                std::cout << "Cadastre ao menos dois candidatos antes de iniciar.\n\n";
                return;
            }
            if (!debateConfigurado) {
                std::cout << "Configure o debate antes de iniciar.\n\n";
                return;
            }
            fachada.iniciarDebate();
            estadoCLI = EstadoCLI::AGUARDANDO_PERGUNTA;
            std::cout << "Debate iniciado.\n\n";
        }
        else {
            std::cout << "Comando invalido nesta fase.\n\n";
        }
    }

    // AGUARDANDO_PERGUNTA
    else if (estadoCLI == EstadoCLI::AGUARDANDO_PERGUNTA) {
        if (args[0] == "INICIAR" && args.size() >= 2 && args[1] == "PERGUNTA") {
            fachada.iniciarPergunta();
            estadoCLI = EstadoCLI::AGUARDANDO_RESPOSTA;
            std::cout << "Fase de pergunta iniciada.\n\n";
        }
        else if (args[0] == "FINALIZAR") {
            fachada.finalizarDebate();
            estadoCLI = EstadoCLI::FINALIZADO;
            std::cout << "Debate finalizado.\n\n";
        }
        else if (args[0] == "RELATORIO") {
            fachada.gerarRelatorio();
            std::cout << std::endl;
        }
        else {
            std::cout << "Comando invalido nesta fase.\n\n";
        }
    }

    // AGUARDANDO_RESPOSTA
    else if (estadoCLI == EstadoCLI::AGUARDANDO_RESPOSTA) {
        if (args[0] == "INICIAR" && args.size() >= 2 && args[1] == "RESPOSTA") {
            fachada.iniciarResposta();
            estadoCLI = EstadoCLI::AGUARDANDO_REPLICA;
            std::cout << "Fase de resposta iniciada.\n\n";
        }
        else {
            std::cout << "Comando invalido nesta fase.\n\n";
        }
    }

    // AGUARDANDO_REPLICA
    else if (estadoCLI == EstadoCLI::AGUARDANDO_REPLICA) {
        if (args[0] == "INICIAR" && args.size() >= 2 && args[1] == "REPLICA") {
            fachada.iniciarReplica();
            estadoCLI = EstadoCLI::AGUARDANDO_TREPLICA;
            std::cout << "Fase de replica iniciada.\n\n";
        }
        else {
            std::cout << "Comando invalido nesta fase.\n\n";
        }
    }

    // AGUARDANDO_TREPLICA
    else if (estadoCLI == EstadoCLI::AGUARDANDO_TREPLICA) {
        if (args[0] == "INICIAR" && args.size() >= 2 && args[1] == "TREPLICA") {
            fachada.iniciarTreplica();
            estadoCLI = EstadoCLI::AGUARDANDO_DR;
            std::cout << "Fase de treplica iniciada.\n\n";
        }
        else {
            std::cout << "Comando invalido nesta fase.\n\n";
        }
    }

    // AGUARDANDO_DR
    else if (estadoCLI == EstadoCLI::AGUARDANDO_DR) {
        if (args[0] == "ANALISAR" && args.size() >= 2 && args[1] == "DR") {
            fachada.analisarSolicitacoesDR();
            std::cout << std::endl;
        }
        else if (args[0] == "CONCEDER" && args.size() >= 3 && args[1] == "DR") {
            cmdConcederDR(args);
        }
        else if (args[0] == "PROXIMO" && args.size() >= 2 && args[1] == "ROUND") {
            fachada.sortearInquiridor();
            estadoCLI = EstadoCLI::AGUARDANDO_PERGUNTA;
            std::cout << "Proximo round iniciado.\n\n";
        }
        else if (args[0] == "FINALIZAR") {
            fachada.finalizarDebate();
            estadoCLI = EstadoCLI::FINALIZADO;
            std::cout << "Debate finalizado.\n\n";
        }
        else if (args[0] == "RELATORIO") {
            fachada.gerarRelatorio();
            std::cout << std::endl;
        }
        else {
            std::cout << "Comando invalido nesta fase.\n\n";
        }
    }

    // FINALIZADO
    else if (estadoCLI == EstadoCLI::FINALIZADO) {
        if (args[0] == "RELATORIO") {
            fachada.gerarRelatorio();
            std::cout << std::endl;
        }
        else {
            std::cout << "Debate encerrado. Apenas RELATORIO disponivel.\n\n";
        }
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
    debateConfigurado = true;
    std::cout << "Debate configurado.\n\n";
}

void CLI::cmdConcederDR(const std::vector<std::string>& args) {
    int id = std::stoi(args[2]);
    fachada.concederDR(id);
    std::cout << "DR concedido.\n\n";
}