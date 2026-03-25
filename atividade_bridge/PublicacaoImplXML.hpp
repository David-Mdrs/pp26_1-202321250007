#pragma once

#include <iostream>
#include <string>

#include "Implementador.hpp"

class PublicacaoImplXML : public Implementador {
public:
    // Construtor
    PublicacaoImplXML() = default;

    // Métodos abstratos
    virtual std::string getDados(Publicacao* pub) const override { return "Retornar dados do XML."; }

private:

};