#pragma once
#include <string>

#include "Candidato.hpp"
#include "../../debate/Microfone.hpp"

class CandidatoConcreto : public Candidato {
private:
    int id;
    std::string nome;
    bool jaPerguntou;
    Microfone microfone;

public:
    CandidatoConcreto(int id, const std::string& nome);

    int getId() const override;
    const std::string& getNome() const override;
    bool getJaPerguntou() const override;
    Microfone& obterMicrofone() override;
    const Microfone& obterMicrofone() const override;

    void marcarComoInquiridor() override;
};