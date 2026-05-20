#pragma once
#include <string>
#include <vector>
#include <random>
#include <iostream>

#include "Mediador.hpp"
#include "Candidato.hpp"
#include "Cronometro.hpp"
#include "Logger.hpp"

class GerenciadorDebate : public Mediador {
private:
    std::vector<Candidato*> candidatos;
    Candidato* inquiridor;
    Candidato* inquirido;
    Cronometro cronometro;
    Logger logger;
    std::string faseAtual;
    std::vector<int> tempos;
    bool encerrado;

private:
    Candidato* buscarCandidatoPorId(int id) const;

public:
    GerenciadorDebate();

    void configurarDebate(const std::vector<Candidato*>& novosCandidatos,
                          const std::vector<int>& novosTempos);

    void sortearInquiridor();
    void definirInquirido(int id);
    void iniciarFase(int tempo);
    void registrarAcao(const std::string& acao);

    void iniciarDebate();
    void proximaAcao() override;
    void finalizarDebate();

    bool estaEncerrado() const;
    void gerarRelatorio() const;
};