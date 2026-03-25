#pragma once

#include <iostream>
#include <string>

#include "Publicacao.hpp"

class Revista : public Publicacao {
public:
    // Construtor
    Revista(Implementador* implementador) : Publicacao(implementador) {}

    // Métodos abstratos
    virtual std::string getTitulo() const override { return "Retornar titulo da Revista."; }
    virtual std::string getAutor(const int id) const override { return "Retornar autor da Revista de ID: " + std::to_string(id) + "."; }

    // Demais métodos
    std::string getArtigo() const { return "Retornar artigo da Revista."; }

private:
    
};