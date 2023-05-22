#include "arvore.h"

char Arvore::getCharId(){
    return this->charId;
}

//flor
float Arvore::Apotema(float lado){
    return (lado*sqrt(3)/2);
}

void Arvore::addVertex(Vetor3D A){
    glVertex3f(A.x,A.y,A.z);
}

void Arvore::Face3x3(Vetor3D A, Vetor3D B, Vetor3D C){
    glDisable(GL_CULL_FACE);
    glPushMatrix();
    glBegin(GL_POLYGON);

    glNormal3f(A.x,A.y,A.z);
    this->addVertex(A);
    this->addVertex(C);
    float angulo{1};
    for(int i = 0; i < 150; i++) {
    angulo = i * M_PI / 150;
    glVertex3f(0 + (cos(angulo) * B.x), B.x+0.5+ (sin(angulo) * B.x),0);
    }
    this->addVertex(B);
    glEnd();
    glPopMatrix();
}

void Arvore::Petala(float r, float g, float b, float lado){
    Vetor3D A(0,0,0);
    Vetor3D B(lado/2, this->Apotema(lado), 0);
    Vetor3D C (-B.x,B.y, B.z);
    GUI::setColor(r,g,b);
    this->ColorirSelecionado();
    glPushMatrix();
    this->Face3x3(A,B,C);
    glPopMatrix();

}

void Arvore::Flor(){
    glPushMatrix();
    glScalef(0.25,0.25,0.25);
    for(int i{0};i < 4; i++){
        glPushMatrix();
        glRotatef(90*i, 0,1,0);
        glRotatef(54, 1,0,0);
        this->Petala(8,1,2, 0.5);
        glPopMatrix();
    }
    for(int i{0};i < 4; i++){
        glPushMatrix();
        glRotatef(90*i, 0,1,0);
        glRotatef(55, 1,0,0);
        this->Petala(16,4,6, 1);
        glPopMatrix();
    }
    glPopMatrix();
}

//galho
void Arvore::Galho(){
    glPushMatrix();
    glScalef(0.5,0.5,0.5);
    glPushMatrix();
    glPushMatrix();
    GUI::setColor(1.5,.7,0.1);
    this->ColorirSelecionado();
    glRotatef(-90,1,0,0);
    Desenha::gluCapsule(gluNewQuadric(), 0.02*this->tamanho,0.02*this->tamanho,this->tamanho*2,10,2);
    glPopMatrix();

    for(float i{0};i < this->tamanho*2; i+=0.25){
        glPushMatrix();
        glTranslatef(0,i,0);
        this->Flor();
        glPopMatrix();
    }
    glPopMatrix();
    glPopMatrix();
}

void Arvore::Face4x4(Vetor3D A, Vetor3D B, Vetor3D C, Vetor3D D){
    glPushMatrix();
    glBegin(GL_POLYGON);
    glNormal3f(A.x,A.y,A.z);
    this->addVertex(A);
    this->addVertex(B);
    this->addVertex(C);
    this->addVertex(D);
    glEnd();
    glPopMatrix();
}

//tronco
void Arvore::Tronco(){
    glPushMatrix();
    float lado = 0.4*tamanho;
    Vetor3D A(0, 0, 0);
    Vetor3D B(lado, A.y, A.z);
    Vetor3D C(B.x,B.y,-lado);
    Vetor3D D(0, C.y, C.z);
    //superiores
    Vetor3D E(B.x, this->tamanho, B.z);
    Vetor3D F(C.x, this->tamanho, C.z);
    Vetor3D G(D.x, this->tamanho, D.z);
    Vetor3D H(A.x, this->tamanho, A.z);

    //lado frontal
    this->Face4x4(A,B,E,H);

    //lado traseiro
    this->Face4x4(B,C,F,E);

    //lado traseiro esquerdo
    this->Face4x4(C,D,G,F);

    //lado frontal esquerdo
    this->Face4x4(D,A,H,G);

    //topo
    this->Face4x4(H,E,F,G);
    //base
    this->Face4x4(C,D,A,B);
    glPopMatrix();
}

Arvore::Arvore(){
    this->charId = 'a';
}

Arvore::Arvore(float tamanho){
    this->tamanho = tamanho;
    this->charId = 'a';
}

void Arvore::Desenhar(){
    glPushMatrix();
    Obj::Desenhar();
    glPushMatrix();
    for(int i{0};i<=90;i+=45){
        //esquerda
        glPushMatrix();
        glTranslatef(this->tamanho*0.2,this->tamanho, -this->tamanho*0.2);
        glRotatef(-i, 0,0,1);
        this->Galho();
        glPopMatrix();
        //direita
        glPushMatrix();
        glTranslatef(this->tamanho*0.2,this->tamanho, -this->tamanho*0.2);
        glRotatef(i, 0,0,1);
        this->Galho();
        glPopMatrix();
        //frente
        glPushMatrix();
        glTranslatef(this->tamanho*0.2,this->tamanho, -this->tamanho*0.2);
        glRotatef(-i, 1,0,0);
        this->Galho();
        glPopMatrix();
        // trás
        glPushMatrix();
        glTranslatef(this->tamanho*0.2,this->tamanho, -this->tamanho*0.2);
        glRotatef(i, 1,0,0);
        this->Galho();
        glPopMatrix();
        //diagonal frente direita
        glPushMatrix();
        glTranslatef(this->tamanho*0.2,this->tamanho, -this->tamanho*0.2);
        glRotatef(45,0,1,0);
        glRotatef(-i, 1,0,0);
        this->Galho();
        glPopMatrix();
        //diagonal frente esquerda
        glPushMatrix();
        glTranslatef(this->tamanho*0.2,this->tamanho, -this->tamanho*0.2);
        glRotatef(-45,0,1,0);
        glRotatef(-i, 1,0,0);
        this->Galho();
        glPopMatrix();
        //diagonal trás esquerda
        glPushMatrix();
        glTranslatef(this->tamanho*0.2,this->tamanho, -this->tamanho*0.2);
        glRotatef(45, 0,1,0);
        glRotatef(i, 1,0,0);
        this->Galho();
        glPopMatrix();
        //diagonal trás direita
        glPushMatrix();
        glTranslatef(this->tamanho*0.2,this->tamanho, -this->tamanho*0.2);
        glRotatef(-45, 0,1,0);
        glRotatef(i, 1,0,0);
        this->Galho();
        glPopMatrix();
    }
    GUI::setColor(1.5,.7,0.1);
    this->ColorirSelecionado();
    this->Tronco();
    glPopMatrix();
    glPopMatrix();
}
