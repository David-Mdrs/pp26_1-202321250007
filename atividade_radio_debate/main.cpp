#include "core/Fachada.hpp"
#include "core/CLI.hpp"

int main() {
    Fachada& fachada = Fachada::getInstance();
    CLI& cli = CLI::getInstance(fachada);
    cli.run();

    return 0;
}