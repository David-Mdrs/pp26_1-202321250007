#pragma once
#include "../comum/ParticipanteBuilder.hpp"
#include "Eleitor.hpp"

class EleitorBuilder : public ParticipanteBuilder {
private:
    Eleitor* resultados;

public:
    EleitorBuilder();
    ~EleitorBuilder();

    void construirId(int id) override;
    void construirNome(const std::string& nome) override;
    void construirCandidatoFavorito(CandidatoConcreto* candidato);

    Eleitor* getResultados();
};