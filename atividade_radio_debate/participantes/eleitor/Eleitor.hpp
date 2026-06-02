#pragma once
#include <string>

#include "../../debate/Colaborador.hpp"
#include "../comum/ObservadorEleitor.hpp"
#include "../comum/ParticipantePrototype.hpp"

class CandidatoConcreto;

class Eleitor : public Colaborador, public ObservadorEleitor, public ParticipantePrototype {
private:
    int id;
    std::string nome;
    CandidatoConcreto* candidatoFavorito;

public:
    Eleitor(int id, const std::string& nome, CandidatoConcreto* candidatoFavorito = nullptr);

    // Métodos get
    int getId() const;
    const std::string& getNome() const;
    CandidatoConcreto* getCandidatoFavorito() const;

    // Métodos set
    void setId(int id);
    void setNome(const std::string& nome);
    void setCandidatoFavorito(CandidatoConcreto* candidato);

    // Métodos auxiliares
    void receberNotificacao(const std::string& mensagem) override;
    ParticipantePrototype* clonar() override;
};