#include <Desenha.h>
#include <extra.h>
#include <vector>
#include <../Objetos/arvore.h>
#include <../Objetos/bambu.h>
#include <../Objetos/flor.h>
#include <../Objetos/panda.h>
#include <../Objetos/pedra.h>
#include <fstream>
#include <sstream>

using namespace std;

struct Controlador{
    vector<Obj*> objetos;
    int indexAtual{-1};
    ofstream fout;
    ifstream fin;

    Controlador(){
        this->fin.open("objetos.txt");
        this->ler();
        this->fout.open("objetos.txt"); 
    }

    Obj* selecao(char c){
        switch (c)
        {
        case 'a': 
        return(new Arvore());
        break;
        case 'b': 
        return (new Bambu());
        case 'f': 
        return (new Flor());
        case 'r': 
        return (new Pedra());
        case 'p': 
        return (new Panda());
        default:
        return nullptr;
            break;
        }
        
    }

    void escrever(){
        this->fout.seekp(ios::beg);
        for(int i{0}; i< this->objetos.size();i++){
            Obj* objeto = this->objetos[i];
            this->fout << objeto->getCharId() << ' ';
            this->fout << objeto->translacao.x << ' ' << objeto->translacao.y << ' ' <<  objeto->translacao.z<< ' ';
            this->fout << objeto->rotacao.x<< ' ' << objeto->rotacao.y<< ' ' << objeto->rotacao.z << ' ';
            this->fout << objeto->escala.x << ' ' << objeto->escala.y << ' ' << objeto->escala.z << endl;
        }
    }

    void ler(){
        char c;
        if(this->fin.beg == this->fin.end){
            return;
        }
        string linha;

        while(getline(this->fin, linha)){
            stringstream ss(linha);
            ss >> c;
            Obj* objTemp = this->selecao(c);
            if (objTemp == nullptr)
                continue;
            ss >> objTemp->translacao.x >> objTemp->translacao.y >> objTemp->translacao.z;
            ss >> objTemp->rotacao.x >> objTemp->rotacao.y >> objTemp->rotacao.z;
            ss >> objTemp->escala.x >> objTemp->escala.y >> objTemp->escala.z;
            this->addObjeto(objTemp);
        }
        this->fin.close();
    }

    void addObjeto(Obj* objetoNovo){
        if(this->indexAtual == -1)
            this->indexAtual = 0;
        this->objetos.push_back(objetoNovo);
    }
    void retornar(){
        if (this->indexAtual != -1 && !(this->objetos.empty())){
                this->objetos[this->indexAtual]->setSelecionado();
            if(this->objetos[this->indexAtual] == *this->objetos.begin())
                this->indexAtual = this->objetos.size() - 1;
            else
                this->indexAtual-=1;
            this->objetos[this->indexAtual]->setSelecionado();
            }
    }

    void desenharEixo(){
        if (this->indexAtual != -1 && !(this->objetos.empty())){
            objetos[indexAtual]->setDesenha();
        }
        
    }
    void On(){
        this->indexAtual = 0;
        this->objetos[this->indexAtual]->setSelecionado();
    }

    void avancar(){
        if (this->indexAtual != -1 && !(this->objetos.empty())){
            this->objetos[this->indexAtual]->setSelecionado();
            if(this->objetos[this->indexAtual] == this->objetos.back()){
                this->indexAtual = 0;
            }
            else{
                this->indexAtual+=1;
            }
            this->objetos[this->indexAtual]->setSelecionado();
            }
    }

    void Off(){
        if (this->indexAtual != -1){
            this->objetos[this->indexAtual]->setSelecionado();
            this->indexAtual = -1;
        }
    }
    void remObjeto(){
        if (this->indexAtual != -1 && !(this->objetos.empty())){
            vector<Obj*>::iterator it = this->objetos.begin();
            for(it; it != this->objetos.end();it++){
                if(this->objetos[this->indexAtual] == *it){
                    break;
                }
            }
            this->retornar();
            if(this->objetos.size() == 1){
                this->indexAtual = 0;
                
            }
            this->objetos.erase(it);
            this->fout.close();
            this->fout.open("objetos.txt");
        }
    }
    ~Controlador(){
        this->fout.close();
    }
};

Controlador controle;

void floresta(){
    GUI::displayInit();
    GUI::setLight(0, 0,1.5,1.5,true);
    GUI::setColor(0,4,0.5);
    GUI::drawFloor(8);

    glPushMatrix();
    if (controle.indexAtual >= 0) {
        controle.objetos[controle.indexAtual]->translacao.x += 10*glutGUI::dtx;
        controle.objetos[controle.indexAtual]->translacao.y += 10*glutGUI::dty;
        controle.objetos[controle.indexAtual]->translacao.z += 10*glutGUI::dtz;

        controle.objetos[controle.indexAtual]->rotacao.x += 10*glutGUI::dax;
        controle.objetos[controle.indexAtual]->rotacao.y += 10*glutGUI::day;
        controle.objetos[controle.indexAtual]->rotacao.z +=10* glutGUI::daz;

        controle.objetos[controle.indexAtual]->escala.x +=10* glutGUI::dsx;
        controle.objetos[controle.indexAtual]->escala.y += 10*glutGUI::dsy;
        controle.objetos[controle.indexAtual]->escala.z += 10*glutGUI::dsz;
    }
    controle.escrever();

    for(int i{0}; i<controle.objetos.size();i++){
        controle.objetos[i]->Desenhar();
    }
    glPopMatrix();
    GUI::displayEnd();
}

bool incluirObjs{false};

void teclado(unsigned char tecla, int mx, int my) {
    if (!incluirObjs)
        GUI::keyInit(tecla, mx,my);

    switch (tecla) {
        case '+':
        incluirObjs = !incluirObjs;
        break;
        case 'a': 
        controle.addObjeto(new Arvore());
        controle.escrever();
        break;
        case 'b': 
        controle.addObjeto(new Bambu());
        controle.escrever();
        break;
        case 'c':
        controle.Off();
        break;
        case 'd': 
        controle.desenharEixo();
        controle.escrever();
        break;
        case 'f': 
        controle.addObjeto(new Flor());
        controle.escrever();
        break;
        case 'i': 
        controle.On();
        break;
        case 'l': 
        controle.avancar();
        break;
        case 'j': 
        controle.retornar();
        break;
        case 'm':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;
        case 'p': 
        controle.addObjeto(new Panda());
        controle.escrever();
        break;
        case 'r': 
        controle.addObjeto(new Pedra());
        controle.escrever();
        break;
        case 't':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        break;
        case 'z':
        controle.remObjeto();
        controle.escrever();
        break;
        case '1':
        glutGUI::cam->e.x = 0;
        glutGUI::cam->e.y = 1.5;
        glutGUI::cam->e.z = 10.5;
        glutGUI::cam->c.x = 0;
        glutGUI::cam->c.y = 1.5;
        glutGUI::cam->c.z = 0;
        glutGUI::cam->u.x = 0;
        glutGUI::cam->u.y = 1;
        glutGUI::cam->u.z = 0;
        break;
        case '2':
        glutGUI::cam->e.x = 8;
        glutGUI::cam->e.y = 4;
        glutGUI::cam->e.z = 8;
        glutGUI::cam->c.x = 0;
        glutGUI::cam->c.y = 1;
        glutGUI::cam->c.z = 0;
        glutGUI::cam->u.x = 0;
        glutGUI::cam->u.y = 1;
        glutGUI::cam->u.z = 0;
        break;
        case '3':
        glutGUI::cam->e.x = -8;
        glutGUI::cam->e.y = 4;
        glutGUI::cam->e.z = 8;
        glutGUI::cam->c.x = 0;
        glutGUI::cam->c.y = 1;
        glutGUI::cam->c.z = 0;
        glutGUI::cam->u.x = 0;
        glutGUI::cam->u.y = 1;
        glutGUI::cam->u.z = 0;
        break;
        case '4':
        glutGUI::cam->e.x = 8;
        glutGUI::cam->e.y = 4.5;
        glutGUI::cam->e.z = -8;
        glutGUI::cam->c.x = 0;
        glutGUI::cam->c.y = 1.5;
        glutGUI::cam->c.z = 0;
        glutGUI::cam->u.x = 0;
        glutGUI::cam->u.y = 1;
        glutGUI::cam->u.z = 0;
        break;
        case '5':
        glutGUI::cam->e.x = -8;
        glutGUI::cam->e.y = 4.5;
        glutGUI::cam->e.z = -8;
        glutGUI::cam->c.x = 0;
        glutGUI::cam->c.y = 1.5;
        glutGUI::cam->c.z = 0;
        glutGUI::cam->u.x = 0;
        glutGUI::cam->u.y = 1;
        glutGUI::cam->u.z = 0;
        break;
        case '6':
        glutGUI::cam->e.x = 0;
        glutGUI::cam->e.y = 1.5;
        glutGUI::cam->e.z = -10.5;
        glutGUI::cam->c.x = 0;
        glutGUI::cam->c.y = 1.5;
        glutGUI::cam->c.z = 0;
        glutGUI::cam->u.x = 0;
        glutGUI::cam->u.y = 1;
        glutGUI::cam->u.z = 0;
        break;
        case '7':
        glutGUI::cam->e.x = 0;
        glutGUI::cam->e.y = 12;
        glutGUI::cam->e.z = 0;
        glutGUI::cam->c.x = 0;
        glutGUI::cam->c.y = 1.5;
        glutGUI::cam->c.z = 0;
        glutGUI::cam->u.x = 0;
        glutGUI::cam->u.y = 0;
        glutGUI::cam->u.z = -1;
        break;
        default:
        break;
    }
}

int main()
{
    std::cout << "ORIENTAÇÃO:" << endl;
    cout << "Para criar e manipular os objetos, primeiramente deve-se digitar +\n";
    cout << "Caso não for criar ou manipular nenhum objeto, apertar + de novo, inclise se for sair da aplicação\n";
    cout << "Comando de criação de objetos:\n";
    cout << "p - criar um panda\n";
    cout << "r - criar uma pedra\n";
    cout << "b - criar um bambu\n";
    cout << "f - criar uma flor\n";
    cout << "a - criar uma árvore\n";
    cout << "Demais comandos:\n";
    
    cout << "i  - inicializa o vetor, em que o primeiro elemento será selecionado\n";
    cout << "c - fecha o acesso ao vetor de objetos, caso feche terá que digitar i novamente\n";
    cout << "z - apagar o objeto selecionado, se apagar o último objeto, precisa digitar o i novamente para percorrer o vetor\n";
    cout << "Percorrer o vetor de objetos:\n";
    cout << "j - voltar no vetor, indo para o objeto anterior\n";
    cout << "l - avançar no vetor, indo para o objeto seguinte\n";
    cout << "t - permite que seja possível aplicar transformações o objeto selecioando\n";
    cout << "m - permite que seja possível alterar a posição da luz\n";

    GUI gui = GUI(800,600,floresta, teclado);
    return 0;
}
