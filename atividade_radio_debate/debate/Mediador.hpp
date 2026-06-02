#pragma once

class Mediador {
public:
    virtual ~Mediador() = default;
    virtual void proximaAcao() = 0;
};