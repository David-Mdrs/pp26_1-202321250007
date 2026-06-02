#pragma once
#include <string>

class ParticipanteBuilder {
public:
    virtual void construirId(int id) = 0;
    virtual void construirNome(const std::string& nome) = 0;
    virtual ~ParticipanteBuilder() = default;
};