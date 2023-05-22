#ifndef FLOR_H
#define FLOR_H
#include "objeto.h"

class Flor : public Obj{
    void FolhasDE(float tamanho);
    void Talo();
    float Apotema(float lado);
    void Face(Vetor3D A, Vetor3D B, Vetor3D C);
    void addVertex(Vetor3D A);
    void Petala(float lado);
    public:
    Flor();
    void Desenhar();
    char getCharId();
};

#endif // FLOR_H
