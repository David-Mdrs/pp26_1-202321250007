#include <vector>

#include "Fachada.hpp"
#include "CLI.hpp"
#include "CandidatoConcreto.hpp"
#include "Eleitor.hpp"

int main() {

    // Candidatos
    CandidatoConcreto candidato1(1, "Ana");
    CandidatoConcreto candidato2(2, "Bruno");
    CandidatoConcreto candidato3(3, "Carla");

    // Lista de candidatos para passar como parâmetro
    std::vector<Candidato*> candidatos = {
        &candidato1,
        &candidato2,
        &candidato3
    };

    // Eleitores
    Eleitor eleitor1(1, "Joao", &candidato1);
    Eleitor eleitor2(2, "Maria", &candidato1);
    Eleitor eleitor3(3, "Pedro", &candidato2);
    Eleitor eleitor4(4, "Lucas", &candidato2);
    Eleitor eleitor5(5, "Julia", &candidato3);

    // Lista de tempos para passar como parâmetro
    std::vector<int> tempos = {10, 8, 5, 3};

    // Inicializando fachada e configurando debate
    Fachada& fachada = Fachada::getInstance();
    fachada.configurarDebate(candidatos, tempos);

    // Inicializando CLI (Canal de interacao do apresentador)
    CLI& cli = CLI::getInstance(fachada);
    cli.run();

    return 0;
}