#pragma once
#include <string>
#include <vector>

class Logger {
private:
    std::vector<std::string> logs;

public:
    void registrar(const std::string& mensagem);
    void gerarRelatorio() const;
};