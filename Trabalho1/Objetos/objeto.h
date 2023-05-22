#ifndef OBJETO_H
#define OBJETO_H
#include <iostream>
#include <gui.h>
#include <cmath>

class Obj{
    protected:
    bool selecionado{false};
    bool desenhaEixo{false};
    char charId; // char identificador
public:
    Vetor3D translacao;
    Vetor3D escala;
    Vetor3D rotacao;
    Obj();
    virtual int getDesenha();
    char getCharId();
    virtual void setSelecionado();
    virtual void setDesenha();
    virtual void Desenhar();
    virtual void DesenharEixo();
    virtual void ColorirSelecionado();
};
#endif // OBJETO_H
