#include "pedra.h"

char Pedra::getCharId(){
    return this->charId;
}

float Pedra::apotema(float lado){
    return (lado*sqrt(3)/2);
}

void Pedra::addVertex(Vetor3D A){
    glVertex3f(A.x,A.y,A.z);
}

void Pedra::Face(Vetor3D A, Vetor3D B, Vetor3D C, Vetor3D D){
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

void Pedra::Hexaedro(float lado1, float lado2, float y1, float y2){
    y2 += y1;
    //inferiores
    Vetor3D A(lado1/2, y1, this->apotema(lado1));
    Vetor3D E(lado1, A.y, 0);
    Vetor3D D(-A.x,A.y,A.z);
    Vetor3D G(A.x, A.y, - A.z);
    Vetor3D I(-A.x,A.y,-A.z);
    Vetor3D K(-E.x, E.y, E.z);
    //superiores
    Vetor3D B(lado2/2, y2, this->apotema(lado2));
    Vetor3D F(lado2, B.y, 0);
    Vetor3D C(-B.x,B.y,B.z);
    Vetor3D H(B.x, B.y, -B.z);
    Vetor3D J(-B.x, B.y, -B.z);
    Vetor3D L(-F.x,F.y,F.z);

    //lado frontal
    this->Face(A,B,C,D);

    //lado frontal direito
    this->Face(E,F,B,A);

    //lado traseiro direito
    this->Face(G,H,F,E);

    //lado traseiro
    this->Face(I,J,H,G);

    //lado traseiro esquerdo
    this->Face(K,L,J,I);

    //lado frontal esquerdo
    this->Face(D,C,L,K);

    glBegin(GL_POLYGON);
    this->addVertex(D);
    this->addVertex(K);
    this->addVertex(I);
    this->addVertex(G);
    this->addVertex(E);
    this->addVertex(A);
    glEnd();
}

Pedra::Pedra(){
    this->charId ='r';
}

void Pedra::Unidade(float tamanho){
    glPushMatrix();
    glScalef(tamanho, tamanho, tamanho);
    this->Hexaedro(0.1, 0,0.57,0.02);
    this->Hexaedro(0.2,0.1,0.5, 0.07);
    this->Hexaedro(0.3, 0.2, 0.4, 0.1 );
    this->Hexaedro(0.4,0.3,0.28,0.12);
    this->Hexaedro(0.48, 0.4,0.15, 0.13);
    this->Hexaedro(0.55,0.48,0, 0.15);
    glPopMatrix();
}

void Pedra::Desenhar(){
    glPushMatrix();
    GUI::setColor(2,2,2);
    Obj::Desenhar();
    glPushMatrix();
    this->Unidade(0.4);
    glTranslatef(0.5,0,0);
    this->Unidade(0.8);
    glPopMatrix();
    glPopMatrix();
}
