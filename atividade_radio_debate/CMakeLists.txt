cmake_minimum_required(VERSION 3.20)

project(atividade_radio_debate)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        .
        core
        debate
        debate/estados
        debate/geral
        participantes/candidato
        participantes/eleitor
        participantes/comum
)

add_executable(main
        main.cpp

        # Core
        core/CLI.cpp
        core/Logger.cpp
        core/Fachada.cpp

        # Debate
        debate/Colaborador.cpp
        debate/Microfone.cpp
        debate/Cronometro.cpp
        debate/GerenciadorDebate.cpp

        # Estados
        debate/estados/estadoPergunta.cpp
        debate/estados/estadoResposta.cpp
        debate/estados/estadoReplica.cpp
        debate/estados/estadoTreplica.cpp
        debate/estados/estadoDireitoResposta.cpp

        # Participantes
        participantes/candidato/Candidato.cpp
        participantes/candidato/CandidatoConcreto.cpp
        participantes/candidato/CandidatoBuilder.cpp
        participantes/eleitor/Eleitor.cpp
        participantes/eleitor/EleitorBuilder.cpp
)