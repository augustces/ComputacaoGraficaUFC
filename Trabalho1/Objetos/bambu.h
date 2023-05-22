#ifndef BAMBU_H
#define BAMBU_Hs
#include "objeto.h"

class Bambu : public Obj{
    float tamanho{4.0};
    float altUnidade{0.4};
    float altDivisoria{0.01};
    float raio{0.05};
    void Divisoria();
    void Unidade();
    void FolhasDE(float tamanho);
    void FolhaC();
    void Talo();
    public:
    Bambu();
    Bambu(float tamanho);
    char getCharId();
    void Desenhar();
};
#endif // BAMBU_H
