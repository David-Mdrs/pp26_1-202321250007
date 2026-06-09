#pragma once
#include <string>

#include "Candidato.hpp"
#include "../../debate/Microfone.hpp"
#include "../comum/ParticipantePrototype.hpp"

class CandidatoConcreto : public Candidato, public ParticipantePrototype {
private:
    int id;
    std::string nome;
    bool jaPerguntou;
    Microfone microfone;

public:
    CandidatoConcreto(int id, const std::string& nome);

    // Métodos get
    int getId() const override;
    const std::string& getNome() const override;
    bool getJaPerguntou() const override;
    Microfone& obterMicrofone() override;
    const Microfone& obterMicrofone() const override;

    // Métodos set
    void setId(int id);
    void setNome(const std::string& nome);
    void setMicrofone(const Microfone& microfone);

    // Métodos auxiliares
    void marcarComoInquiridor() override;
    ParticipantePrototype* clonar() override;

    // Métodos da funcionalidade DR
    bool solicitarDireitoResposta();
};