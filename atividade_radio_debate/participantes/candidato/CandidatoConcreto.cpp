#include "CandidatoConcreto.hpp"
#include <random>

CandidatoConcreto::CandidatoConcreto(int id, const std::string& nome)
    : id(id), nome(nome), jaPerguntou(false), microfone(id) {
}

// Métodos get
int CandidatoConcreto::getId() const { return id; }
const std::string& CandidatoConcreto::getNome() const { return nome; }
bool CandidatoConcreto::getJaPerguntou() const { return jaPerguntou; }
Microfone& CandidatoConcreto::obterMicrofone() { return microfone; }
const Microfone& CandidatoConcreto::obterMicrofone() const { return microfone; }

// Métodos set
void CandidatoConcreto::setId(int id) { this->id = id; }
void CandidatoConcreto::setNome(const std::string& nome) { this->nome = nome; }
void CandidatoConcreto::setMicrofone(const Microfone& microfone) { this->microfone = microfone; }

// Método do padrão Builder
void CandidatoConcreto::marcarComoInquiridor() {
    jaPerguntou = true;
}

// Método do padrão Prototype
ParticipantePrototype* CandidatoConcreto::clonar() {
    CandidatoConcreto* novo = new CandidatoConcreto(id, nome);
    novo->jaPerguntou = jaPerguntou;
    novo->microfone = microfone;
    return novo;
}

// Métodos da funcionalidade DR
bool CandidatoConcreto::solicitarDireitoResposta() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1);
    return dist(gen) == 1;
}