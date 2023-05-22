#ifndef PANDA_H
#define PANDA_H
#include "objeto.h"

class Panda : public Obj{
    float raioBarriga{0.2};
    float raioPeito;
    float raioCabeca;
    Vetor3D origem;
    Vetor3D peito;
    Vetor3D cabeca;

    Vetor3D novaEsfera(Vetor3D base, float raioBase, float raioNova);

    void Atribuicoes();
    void Cabeca();
    void Braco();
    void Perna();
    void Tronco();

public:
    Panda();
    char getCharId();
    Panda(float raioBarriga);
    void Desenhar();
};
#endif // PANDA_H
