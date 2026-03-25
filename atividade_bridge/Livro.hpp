#pragma once

#include <iostream>
#include <string>

#include "Publicacao.hpp"

class Livro : public Publicacao {
public:
    // Construtor
    Livro(Implementador* implementador) : Publicacao(implementador) {}

    // Métodos abstratos
    virtual std::string getTitulo() const override { return "Retornar titulo do Livro."; }
    virtual std::string getAutor(const int id) const override { return "Retornar autor do Livro de ID: " + std::to_string(id) + "."; }

    // Demais métodos
    std::string getISBN() const { return "Retornar ISBN do Livro."; }

private:

};