#include "objeto.h"

Obj::Obj(){
    this->rotacao = Vetor3D(0,0,0);
    this->escala = Vetor3D(1,1,1);
    this->translacao = Vetor3D(0,0,0);
}

void Obj::Desenhar(){
    glTranslatef(this->translacao.x, this->translacao.y, this->translacao.z);
    glRotatef(this->rotacao.z, 0, 0, 1);
    glRotatef(this->rotacao.y, 0,1,0);
    glRotatef(this->rotacao.x, 1,0,0);
    this->DesenharEixo();
    this->ColorirSelecionado();
    glScalef(this->escala.x, this->escala.y, this->escala.z);
}

int Obj::getDesenha(){
    if(this->desenhaEixo)
        return 1;
    return 0;
}

char Obj::getCharId(){
    return this->charId;
}

void Obj::setSelecionado(){
    this->selecionado = !this->selecionado;
}

void Obj::setDesenha(){
    this->desenhaEixo = !this->desenhaEixo;
}

void Obj::ColorirSelecionado(){
    if (this->selecionado)
    {GUI::setColor(20,20,20);}
}

void Obj::DesenharEixo(){
    if (this->desenhaEixo)
    {GUI::drawOrigin(1);}
}