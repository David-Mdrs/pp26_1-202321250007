#include "Logger.hpp"
#include <iostream>

void Logger::registrar(const std::string& mensagem) {
    if (mensagem.empty()) return;
    logs.push_back(mensagem);
    std::cerr << "[LOG] " << mensagem << "\n";
}

void Logger::gerarRelatorio() const {
    std::cout << "\n===== RELATORIO LOGS =====\n";
    for (const auto& log : logs) {
        std::cout << log << '\n';
    }
}