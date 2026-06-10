#include "core/Fachada.hpp"
#include "core/CLI.hpp"
#include <cstdlib>

int main() {
    freopen("logs.txt", "w", stderr);
    setvbuf(stderr, nullptr, _IOLBF, 0);

    system("start powershell -Command \"Get-Content -Path logs.txt -Wait\"");

    Fachada& fachada = Fachada::getInstance();
    CLI& cli = CLI::getInstance(fachada);
    cli.run();

    return 0;
}