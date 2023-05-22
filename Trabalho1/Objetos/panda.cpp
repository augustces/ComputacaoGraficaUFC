#include "panda.h"

char Panda::getCharId(){
    return this->charId;
}

Vetor3D Panda::novaEsfera(Vetor3D base, float raioBase, float raioNova){
    Vetor3D nova;
    nova.x = base.x;
    nova.y = base.y + raioBase + raioNova/3;
    nova.z = base.z;
    return nova;
}

 void Panda::Cabeca(){
    glPushMatrix();
    //orelha esquerda
    glPushMatrix();
    glTranslatef(this->cabeca.x+0.8*this->raioCabeca,this->cabeca.y+0.8*this->raioCabeca,this->cabeca.z);
    Desenha::gluClosedCylinder(gluNewQuadric(), 0.4*this->raioCabeca,0.4*this->raioCabeca,0.02,10,20);
    glPopMatrix();

    //orelha direita
    glPushMatrix();
    glTranslatef(-this->cabeca.x-0.8*this->raioCabeca,this->cabeca.y+0.8*this->raioCabeca,this->cabeca.z);
    Desenha::gluClosedCylinder(gluNewQuadric(), 0.4*this->raioCabeca,0.4*this->raioCabeca,0.02,10,20);
    glPopMatrix();

    //fucinho
    glPushMatrix();
    GUI::drawSphere(this->cabeca.x,this->cabeca.y,this->cabeca.z + this->raioCabeca,0.3*this->raioCabeca);
    glPopMatrix();

    //olho esquerdo
    glPushMatrix();
    GUI::drawSphere(this->cabeca.x+this->raioCabeca/2,this->cabeca.y + this->raioCabeca/2,this->cabeca.z+0.6*this->raioCabeca,0.2* this->raioCabeca);
    glPopMatrix();

    //olho direito
    glPushMatrix();
    GUI::drawSphere(-this->cabeca.x-this->raioCabeca/2,this->cabeca.y + this->raioCabeca/2,this->cabeca.z+0.6*this->raioCabeca,0.2* this->raioCabeca);
    glPopMatrix();
    glPopMatrix();
}

void Panda::Braco(){
    //esquerdo
    glPushMatrix();
    glPushMatrix();
    glTranslatef(this->peito.x+this->raioPeito,this->peito.y,0);
    glRotatef(20,0,0,1);
    glRotatef(85, 1,0,0);
    Desenha::gluCapsule(gluNewQuadric(), 0.3*this->raioPeito,0.3*this->raioPeito,this->raioBarriga,8,20);
    glPopMatrix();

    //direito
    glPushMatrix();
    glTranslatef(-this->peito.x-this->raioPeito,this->peito.y,0);
    glRotatef(-20,0,0,1);
    glRotatef(85, 1,0,0);
    Desenha::gluCapsule(gluNewQuadric(), 0.3*this->raioPeito,0.3*this->raioPeito,this->raioBarriga,8,20);
    glPopMatrix();
    glPopMatrix();
}

void Panda::Perna(){
    glPushMatrix();
    //esquerda
    glPushMatrix();
    glTranslatef(this->origem.x + this->raioBarriga/2,-this->origem.y-this->raioBarriga/2,this->origem.z+this->raioBarriga*0.8);
    glRotatef(5,1,0,0);
    Desenha::gluCapsule(gluNewQuadric(), 0.5*this->raioBarriga,0.5*this->raioBarriga,this->raioBarriga,8,20);
    glPopMatrix();

    //direita
    glPushMatrix();
    glTranslatef(-this->origem.x - this->raioBarriga/2,-this->origem.y-this->raioBarriga/2,this->origem.z+this->raioBarriga*0.8);
    glRotatef(5,1,0,0);
    Desenha::gluCapsule(gluNewQuadric(), 0.5*this->raioBarriga,0.5*this->raioBarriga,this->raioBarriga,8,20);
    glPopMatrix();
    glPopMatrix();
}

void Panda::Tronco(){
    glPushMatrix();
    //barriga
    GUI::setColor(20,20,20);
    this->ColorirSelecionado();
    GUI::drawSphere(this->origem.x,this->origem.y,this->origem.z,this->raioBarriga);
    //peito
    GUI::setColor(0,0,0);
    this->ColorirSelecionado();
    GUI::drawSphere(this->peito.x,this->peito.y,this->peito.z,this->raioPeito);
    //cabeça
    GUI::setColor(20,20,20);
    this->ColorirSelecionado();
    GUI::drawSphere(this->cabeca.x,this->cabeca.y,this->cabeca.z,this->raioCabeca);
    glPopMatrix();
}

void Panda::Atribuicoes(){
    this->raioPeito = 0.7*this->raioBarriga;
    this->raioCabeca = 0.6* this->raioPeito;
    
    //vetores
    this->origem.x=0;
    this->origem.y=0;
    this->origem.z=0;
    this->peito = novaEsfera(this->origem,this->raioBarriga,this->raioPeito);
    this->cabeca = novaEsfera(peito, this->raioPeito,this->raioCabeca);
}

Panda::Panda(){
    this->charId = 'p';
    this->Atribuicoes();
}

Panda::Panda(float raioBarriga){
    this->charId = 'p';
    this->raioBarriga = raioBarriga;
    this->Atribuicoes();
}

void Panda::Desenhar(){
    glPushMatrix();
    Obj::Desenhar();
    glPushMatrix();
    glTranslatef(0,this->raioBarriga,0);
    glPushMatrix();
    this->Tronco();
    GUI::setColor(0,0,0);
    this->ColorirSelecionado();
    this->Braco();
    this->Perna();
    this->Cabeca();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}