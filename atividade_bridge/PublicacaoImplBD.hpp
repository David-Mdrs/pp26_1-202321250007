#pragma once

#include <iostream>
#include <string>

#include "Implementador.hpp"

class PublicacaoImplBD : public Implementador {
public:
    // Construtor
    PublicacaoImplBD() = default;

    // Métodos abstratos
     virtual std::string getDados(Publicacao* pub) const override { return "Retornar dados do Banco de Dados."; }

private:

};