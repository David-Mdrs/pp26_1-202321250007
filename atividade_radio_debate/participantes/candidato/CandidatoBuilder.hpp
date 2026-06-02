#pragma once
#include "../comum/ParticipanteBuilder.hpp"
#include "CandidatoConcreto.hpp"

class CandidatoBuilder : public ParticipanteBuilder {
public:
    CandidatoBuilder();
    ~CandidatoBuilder();

    void construirId(int id) override;
    void construirNome(const std::string& nome) override;
    void construirMicrofone(const Microfone& microfone);

    CandidatoConcreto* getResultados();

private:
    CandidatoConcreto* resultados;
};