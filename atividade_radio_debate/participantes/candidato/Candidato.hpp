#pragma once
#include <string>
#include <vector>

#include "../../debate/Colaborador.hpp"
#include "../comum/ObservadorEleitor.hpp"

class Microfone;

class Candidato : public Colaborador {
protected:
    std::vector<ObservadorEleitor*> eleitores;

public:
    virtual ~Candidato() = default;

    void cadastrar(ObservadorEleitor* observador);
    void remover(ObservadorEleitor* observador);
    void notificar(const std::string& mensagem);

    virtual int getId() const = 0;
    virtual const std::string& getNome() const = 0;
    virtual bool getJaPerguntou() const = 0;
    virtual Microfone& obterMicrofone() = 0;
    virtual const Microfone& obterMicrofone() const = 0;
    virtual void marcarComoInquiridor() = 0;
};