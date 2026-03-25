#pragma once

#include <iostream>
#include <string>

#include "Implementador.hpp"

class Publicacao {
public:
    // Construtor e Destrutor virtual
    Publicacao(Implementador* implementador) : imp(implementador) {}
    virtual ~Publicacao() = default;

    // Métodos abstratos
    virtual std::string getTitulo() const = 0;
    virtual std::string getAutor(const int id) const = 0;

    // Demais métodos
    virtual std::string obterDados(Implementador* tipo) { return tipo->getDados(this); }

protected:
    Implementador* imp;
};