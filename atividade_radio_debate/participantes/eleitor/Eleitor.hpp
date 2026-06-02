#pragma once
#include <string>

#include "../../debate/Colaborador.hpp"
#include "../comum/ObservadorEleitor.hpp"

class CandidatoConcreto;

class Eleitor : public Colaborador, public ObservadorEleitor {
private:
    int id;
    std::string nome;
    CandidatoConcreto* candidatoFavorito;

public:
    Eleitor(int id, const std::string& nome, CandidatoConcreto* candidatoFavorito = nullptr);

    void setCandidatoFavorito(CandidatoConcreto* candidato);
    void receberNotificacao(const std::string& mensagem) override;

    int getId() const;
    const std::string& getNome() const;
    CandidatoConcreto* getCandidatoFavorito() const;
};