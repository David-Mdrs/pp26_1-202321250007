#pragma once
#include <string>
#include <vector>
#include <random>
#include <iostream>

#include "Mediador.hpp"
#include "../participantes/candidato/Candidato.hpp"
#include "Cronometro.hpp"
#include "../core/Logger.hpp"
#include "estados/EstadoDebate.hpp"

class GerenciadorDebate : public Mediador {
private:
    std::vector<Candidato*> candidatos;
    Candidato* inquiridor;
    Candidato* inquirido;
    Cronometro cronometro;
    Logger logger;
    std::vector<int> tempos;
    bool encerrado;
    EstadoDebate* estadoAtual;
    std::vector<Candidato*> filaDR;

private:
    Candidato* buscarCandidatoPorId(int id) const;

public:
    GerenciadorDebate();

    void configurarDebate(const std::vector<Candidato*>& novosCandidatos,
                          const std::vector<int>& novosTempos);

    void sortearInquiridor();
    void definirInquirido(int id);
    void registrarAcao(const std::string& acao);

    void iniciarDebate();
    void proximaAcao() override;
    void finalizarDebate();

    bool estaEncerrado() const;
    void gerarRelatorio() const;

    // Métodos do padrão State
    void setEstado(EstadoDebate* estado);
    void processarEstado();

    // Métodos para implementação da DR
    void registrarSolicitacaoDR(Candidato* candidato);
    void analisarSolicitacoesDR();
    void concederDR(Candidato* candidato);
    void simularSolicitacoesDR();           // Simula o botão de DR dos candidatos

    // Métodos get
    Candidato* getInquiridor() const;
    Candidato* getInquirido() const;
    const std::vector<Candidato*>& getCandidatos() const;
    std::vector<Candidato*>& getFilaDR();
    void limparFilaDR();
    const std::vector<int>& getTempos() const;
    Cronometro& getCronometro();
};