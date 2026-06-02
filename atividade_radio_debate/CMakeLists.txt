cmake_minimum_required(VERSION 3.20)

project(atividade_radio_debate)

set(CMAKE_CXX_STANDARD 17)

add_executable(main
        main.cpp
        core/CLI.cpp
        debate/Colaborador.cpp
        debate/Microfone.cpp
        debate/Cronometro.cpp
        core/Logger.cpp
        participantes/candidato/Candidato.cpp
        participantes/candidato/CandidatoConcreto.cpp
        participantes/eleitor/Eleitor.cpp
        debate/GerenciadorDebate.cpp
        core/Fachada.cpp
        core/CLI.cpp
        core/CLI.hpp
        participantes/comum/ParticipanteBuilder.hpp
        participantes/candidato/CandidatoBuilder.hpp
        participantes/candidato/CandidatoBuilder.cpp
        participantes/eleitor/EleitorBuilder.hpp
        participantes/eleitor/EleitorBuilder.cpp
        participantes/comum/ParticipantePrototype.hpp
)