#pragma once

#include <iostream>
#include <string>

class Publicacao;

class Implementador{
public:
    // Construtor e Destrutor virtual
    Implementador() = default;
    virtual ~Implementador() = default;

    // Método abstrato
    virtual std::string getDados(Publicacao* pub) const = 0;

private:
    
};