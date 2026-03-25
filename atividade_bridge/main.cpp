#include <iostream>
#include <string>

#include "Livro.hpp"
#include "Revista.hpp"

#include "PublicacaoImplBD.hpp"
#include "PublicacaoImplXML.hpp"

int main() {
    std::string cmd;
    std::cout << std::endl;
    std::cout << "Tipos de publicacoes: Livro - Revista" << std::endl;
    std::cout << "Tipos de arquivo:     BD - XML" << std::endl << std::endl;

    std::cout << "Comando: 'publicacao' 'arquivo'" << std::endl;
    std::cout << "Indique 'Sair' para finalizar." << std::endl;

    while (true) {
        std::cout << std::endl << "Comando: ";
        std::getline(std::cin, cmd);

        if (cmd == "Sair") {
            std::cout << "Programa encerrado." << std::endl;
            break;
        }

        Implementador* impl = nullptr;
        Publicacao* pub = nullptr;

        // Interpretador de comandos
        if (cmd == "Livro BD") {
            impl = new PublicacaoImplBD();
            pub = new Livro(impl);
        }

        else if (cmd == "Livro XML") {
            impl = new PublicacaoImplXML();
            pub = new Livro(impl);
        }

        else if (cmd == "Revista BD") {
            impl = new PublicacaoImplBD();
            pub = new Revista(impl);
        }

        else if (cmd == "Revista XML") {
            impl = new PublicacaoImplXML();
            pub = new Revista(impl);
        }

        else {
            std::cout << "Comando desconhecido.\n";
            continue;
        }

        // Buscando dados da "pub" através do "imp"
        std::cout << "Titulo: " << pub->getTitulo() << "\n";
        std::cout << "Dados:  " << pub->obterDados(impl) << "\n";

        delete pub;
        delete impl;
    }
    return 0;
}