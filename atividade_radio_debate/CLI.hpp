#pragma once
#include <vector>

#include "Fachada.hpp"

class CLI {
public:
    static CLI& getInstance(Fachada& fachada);

    void run();

private:
    Fachada& fachada;
    CLI(Fachada& fachada);
    void executarComando(const std::vector<std::string>& args);
};