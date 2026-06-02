#pragma once

class ParticipantePrototype {
public:
    virtual ParticipantePrototype* clonar() = 0;
    virtual ~ParticipantePrototype() = default;
};