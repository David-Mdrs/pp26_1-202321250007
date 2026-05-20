#pragma once
#include <string>

class ObservadorEleitor {
public:
    virtual ~ObservadorEleitor() = default;
    virtual void receberNotificacao(const std::string& mensagem) = 0;
};