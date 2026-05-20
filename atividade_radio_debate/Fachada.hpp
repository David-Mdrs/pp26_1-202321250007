#pragma once
#include <vector>

#include "GerenciadorDebate.hpp"

class Fachada {
private:
    GerenciadorDebate gerenciador;

    Fachada();

public:
    Fachada(const Fachada&) = delete;
    Fachada& operator=(const Fachada&) = delete;

    static Fachada& getInstance();

    void configurarDebate(const std::vector<Candidato*>& candidatos,
                          const std::vector<int>& tempos);

    void sortearInquiridor();
    void definirInquirido(int id);
    void iniciarDebate();
    void avancarEtapa();
    void finalizarDebate();

    bool debateEncerrado() const;
    void gerarRelatorio() const;
};