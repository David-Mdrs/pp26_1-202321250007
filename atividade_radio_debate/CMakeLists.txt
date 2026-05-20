cmake_minimum_required(VERSION 3.20)

project(atividade_radio_debate)

set(CMAKE_CXX_STANDARD 17)

add_executable(main
        main.cpp
        CLI.cpp
        Colaborador.cpp
        Microfone.cpp
        Cronometro.cpp
        Logger.cpp
        Candidato.cpp
        CandidatoConcreto.cpp
        Eleitor.cpp
        GerenciadorDebate.cpp
        Fachada.cpp
        cli.cpp
        CLI.hpp
)