#ifndef ARVORE_H
#define ARVORE_H
#include "objeto.h"

class Arvore : public Obj{
    float tamanho{1};
    void addVertex(Vetor3D A);
    float Apotema(float lado);
    void Face3x3(Vetor3D A, Vetor3D B, Vetor3D C);
    void Face4x4(Vetor3D A, Vetor3D B, Vetor3D C, Vetor3D D);
    void Petala(float r, float g, float b, float lado);
    void Galho();
    void Tronco();
    void Flor();
    public:
    Arvore();
    Arvore(float tamanho);
    char getCharId();
    void Desenhar();

};
#endif // ARVORE_H
