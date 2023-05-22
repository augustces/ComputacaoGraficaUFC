#include "flor.h"

char Flor::getCharId(){
    return this->charId;
}

void Flor::FolhasDE(float tamanho){
    glPushMatrix();
    // mais a esquerda
    GUI::setColor(1.8,2.7,0.1);
    this->ColorirSelecionado();
    glPushMatrix();
    glTranslatef(0.08,tamanho,0);
    glRotatef(-90, 0,1,0);
    glRotatef(45, 0,0,1);
    glScalef(0.01,0.05,0.1);
    GUI::drawSphere(0,0,0,1);
    glPopMatrix();

    //mais a direita
    glPushMatrix();
    glTranslatef(-0.08,tamanho,0);
    glRotatef(-90, 0,1,0);
    glRotatef(45, 0,0,1);
    glScalef(0.01,0.05,0.1);
    GUI::drawSphere(0,0,0,1);
    glPopMatrix();
    glPopMatrix();
}

void Flor::Talo(){
    glPushMatrix();
    this->FolhasDE(0.4);
    GUI::setColor(.8,1.7,0.1);
    this->ColorirSelecionado();
    glRotatef(-90,1,0,0);
    Desenha::gluClosedCylinder(gluNewQuadric(), 0.01,0.01,0.8,10,8);
    glPopMatrix();
}

float Flor::Apotema(float lado){
    return (lado*sqrt(3)/2);
}

void Flor::addVertex(Vetor3D A){
    glVertex3f(A.x,A.y,A.z);
}

void Flor::Face(Vetor3D A, Vetor3D B, Vetor3D C){
    glDisable(GL_CULL_FACE);
    glPushMatrix();
    glBegin(GL_POLYGON);

    glNormal3f(A.x,A.y,A.z);
    this->addVertex(A);
    this->addVertex(C);
    float angulo{1};
    for(int i = 0; i < 140; i++) {
    angulo = i * M_PI / 140;
    glVertex3f(0, B.y+ (sin(angulo) * B.x),B.y +B.x + (cos(angulo) * B.x));
    this->addVertex(B);
    }
    glEnd();
    glPopMatrix();
}

void Flor::Petala(float lado){
    Vetor3D A(0,0,0);
    Vetor3D B(lado/2, this->Apotema(lado), 0);
    Vetor3D C (-B.x,B.y, B.z);
    glPushMatrix();
    this->Face(A,B,C);
    glPopMatrix();

}

Flor::Flor(){
    this->charId = 'f';
}

void Flor::Desenhar(){
    glPushMatrix();
    Obj::Desenhar();
    glPushMatrix();
    glScalef(0.5,0.5,.5);
    this->Talo();
    glTranslatef(0,0.8,0);
    glScalef(0.3,.3,.3);
    glPushMatrix();
    for(int i{0};i < 5; i++){
        glPushMatrix();
        glRotatef(72*i, 0,1,0);
        glRotatef(59, 1,0,0);
        GUI::setColor(5,0,3);
        this->ColorirSelecionado();
        this->Petala(0.25);
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix();
    for(int i{0};i < 5; i++){
        glPushMatrix();
        glRotatef(72*i, 0,1,0);
        glRotatef(60, 1,0,0);
        GUI::setColor(15,15,15);
        this->ColorirSelecionado();
        this->Petala(0.5);
        glPopMatrix();
    }
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}