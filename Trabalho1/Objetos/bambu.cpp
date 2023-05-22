#include "bambu.h"

char Bambu::getCharId(){
    return this->charId;
}

Bambu::Bambu(float tamanho){
    this->charId = 'b';
    this->tamanho = tamanho;
}
Bambu::Bambu(){
    this->charId =  'b';
}

void Bambu::Divisoria(){
    glPushMatrix();
    
    glRotatef(-90, 1,0,0);
    Desenha::gluClosedCylinder(gluNewQuadric(), this->raio, this->raio,this->altDivisoria,10,8);
    glPopMatrix();
}

void Bambu::Unidade(){
    glPushMatrix();
    
    glRotatef(-90, 1,0,0);
    Desenha::gluClosedCylinder(gluNewQuadric(), this->raio,this->raio,this->altUnidade,10,8);
    glPopMatrix();
}

void Bambu::FolhasDE(float tamanho){
    glPushMatrix();
    // mais a esquerda
    glPushMatrix();
    glTranslatef(tamanho/sqrt(2),tamanho/sqrt(2)+(0.08*sin(45)),-(0.1*cos(45)));
    GUI::setColor(1.8,2.7,0.1);
    this->ColorirSelecionado();
    glRotatef(-45,1,0,0);
    glRotatef(90, 0,0,1);
    glRotatef(-90,0,1,0);
    glRotatef(45, 0,0,1);
    glScalef(0.01,0.05,0.1);
    GUI::drawSphere(0,0,0,1);
    glPopMatrix();

    //mais a direita
    glPushMatrix();
    glTranslatef(tamanho/sqrt(2)+(0.05*cos(45)),tamanho/sqrt(2)-(0.08*sin(45)),0);
    GUI::setColor(1.8,2.7,0.1);
    this->ColorirSelecionado();
    glRotatef(135, 0,0,1);
    glRotatef(-90,0,1,0);
    glRotatef(45, 0,0,1);
    glScalef(0.01,0.05,0.1);
    GUI::drawSphere(0,0,0,1);
    glPopMatrix();
    glPopMatrix();
}

void Bambu::FolhaC(){
    //central
    glPushMatrix();
    glTranslatef(this->altUnidade/sqrt(2)+(0.1*cos(45)),this->altUnidade/sqrt(2)+(0.05*sin(45)),0);
    GUI::setColor(1.8,2.7,0.1);
    this->ColorirSelecionado();
    glRotatef(45, 0,0,1);
    glRotatef(-90,0,1,0);
    glRotatef(45, 0,0,1);
    glScalef(0.01,0.05,0.1);
    GUI::drawSphere(0,0,0,1);
    glPopMatrix();
}

void Bambu::Talo(){
    glPushMatrix();
    glPushMatrix();
    glRotatef(-90, 0,1,0);
    this->FolhaC();
    this->FolhasDE(this->altUnidade/2);
    glPopMatrix();
    GUI::setColor(2.5,2.5,1.5);
    this->ColorirSelecionado();
    glRotatef(-45, 1,0,0);
    Desenha::gluClosedCylinder(gluNewQuadric(), this->altDivisoria/2,this->altDivisoria/2,this->altUnidade,10,8);
    glPopMatrix();
}

void Bambu::Desenhar(){
    glPushMatrix();
    Obj::Desenhar();
    glPushMatrix();
    for (int i{0}; i<this->tamanho;i++){
        glPushMatrix();
        glTranslatef(0,i*(this->altUnidade + 0.01), 0);
        GUI::setColor(1.8,2.7,0.1);
        this->ColorirSelecionado();
        this->Unidade();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0,(i+1)*(this->altUnidade) + i*(0.01), 0);
        GUI::setColor(2.5,2.5,1.5);
        this->ColorirSelecionado();
        this->Divisoria();
        glPopMatrix();
        glPushMatrix();
        if (i % 2 == 0){
            glTranslatef(this->raio,(i+1)*(this->altUnidade) + i*(0.01), 0);
            glRotatef(90, 0,1,0);
        }
        else {
            glTranslatef(-this->raio,(i+1)*(this->altUnidade) + i*(0.01), 0);
            glRotatef(-90, 0,1,0);
        }
        this->Talo();
        glPopMatrix();
    }
    glPopMatrix();
    glPopMatrix();
}
