#ifndef PEDRA_H
#define PEDRA_H
#include "objeto.h"

class Pedra: public Obj{
    void Unidade(float tamanho);
    void addVertex(Vetor3D A);
    void Face(Vetor3D A, Vetor3D B, Vetor3D C, Vetor3D D);
    void Hexaedro(float lado1, float lado2, float y1, float y2);
    float apotema(float lado);
    public:
    Pedra();
    void Desenhar();
    char getCharId();

};

#endif // PEDRA_H
