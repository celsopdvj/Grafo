#include "Grafo.h"

namespace ED2
{

std::vector<Aresta *> *Grafo::getArestas() const
{
    return arestas;
}

bool Grafo::existeAresta(Vertice *a, Vertice *b) const
{
    try{
        // cria uma aresta para verificar se existe no vetor de arestas
        Aresta *nova = new Aresta(a,b);
        // percorre o vetor de arestas
        for(std::vector<Aresta*>::iterator i = arestas->begin(); i!=arestas->end(); i++) {
            Aresta *aux = *i;
            // caso ache a aresta retorna verdadeiro
            if(aux->operator ==(nova))
            {
                delete nova;
                return true;
            }
        }
        // caso nao encontre a aresta retorna falso
        delete nova;
        return false;
    }catch(std::bad_alloc&){
        throw QString("Maquina sem memoria");
    }
}

bool Grafo::getQuantidadeArestas() const
{
    return arestas->size();
}

void Grafo::incluirAdjacencia(Vertice *a, Vertice *b) const
{
    // obtem a posicao de cada um dos vertices na matriz
    int linha = getPosicaoVertice(a);
    int coluna = getPosicaoVertice(b);

    // atribui a adjacencia caso nao exista
    if(matrizAdjacencia[linha][coluna]) throw QString("Adjacencia ja existe");
    matrizAdjacencia[linha][coluna] = 1;
}

void Grafo::excluirAdjacencia(Vertice *a, Vertice *b)
{
    // obtem a posicao de cada um dos vertices na matriz
    int linha = getPosicaoVertice(a);
    int coluna = getPosicaoVertice(b);

    //  retira a adjacencia caso exista
    if(!matrizAdjacencia[linha][coluna]) throw QString("Adjacencia nao existe");
    matrizAdjacencia[linha][coluna] = 0;
}

int **Grafo::getMatrizAdjacencia() const
{
    return matrizAdjacencia;
}

int Grafo::BuscaEmLargura(Vertice *partida) const
{
    try{
        int nosAlcancados = 0; // quantidade de nos alcancados
        if(!partida) return 0;

        // inicializa todos os vertices com distancia infinita e pai NIL
        for(int i=0;i<getVerticesOcupados();i++){
            vertices[i]->setCor(Branco);
            vertices[i]->setDistancia(INT32_MAX);
            vertices[i]->setPai(0);
        }
        // atribui cor cinza e distancia 0 para o vertice de partida
        partida->setCor(Cinza);
        partida->setDistancia(0);

        nosAlcancados++;

        // inicializa a fila
        std::queue<Vertice*> fila;
        fila.push(partida);
        while(!fila.empty())
        {
            // retira o elemento da fila
            Vertice *u = fila.front();
            fila.pop();
            std::list<Vertice*> adjacentes = u->getListaAdjacencia();

            // para cada adjacente do elemento, atribui a nova cor, nova distancia e novo Pai caso seja Branco
            for(std::list<Vertice*>::iterator i = adjacentes.begin(); i!= adjacentes.end(); i++)
            {
                Vertice *aux = *i;
                if(aux->getCor()==Branco)
                {
                    aux->setCor(Cinza);
                    aux->setDistancia(u->getDistancia()+1);
                    aux->setPai(u);
                    fila.push(aux);
                    nosAlcancados++;
                }
            }
            // atribui cor Preto para o elemento que ja teve seus adjacentes visitados
            u->setCor(Preto);
        }
        return nosAlcancados;
    }catch(QString &erro) {
        throw erro;
    }
}

QString Grafo::printPath(Vertice *partida,Vertice *destino)
{
    if(partida==destino)
    {
        return partida->getDescricao();
    }
    else
    {
        if(!destino->getPai())
        {
            return QString("Nenhum caminho existente de "+partida->getDescricao()+" -- "+destino->getDescricao());
        }
        else
        {
            return printPath(partida,destino->getPai())+" -- "+destino->getDescricao();
        }
    }
}

void Grafo::setMatrizAdjacencia(int **value)
{
    for(int i=0;i<tamanho;i++)
        delete [] matrizAdjacencia[i];
    delete [] matrizAdjacencia;
    matrizAdjacencia = value;
}

Grafo::Grafo(int tamanho):
    tamanho(tamanho),
    ultimoVerticeOcupado(0),
    matrizAdjacencia(0)
{
    if (tamanho<=0) throw QString("Tamanho invalido");
    try{
        vertices = new Vertice*[tamanho];
        arestas = new std::vector<Aresta*>();
        matrizAdjacencia = new int*[tamanho];
        for(int i=0;i<tamanho;i++)
        {
            matrizAdjacencia[i] = new int[tamanho];
            vertices[i] = NULL;
            for(int j=0;j<tamanho;j++)
            {
                matrizAdjacencia[i][j] = 0;
            }
        }
    }catch(std::bad_alloc&){
        throw QString("Maquina sem memoria");
    }
}

Grafo::~Grafo()
{
    for(int i=0;i<ultimoVerticeOcupado;i++)
        delete vertices[i];

    if(matrizAdjacencia)
    {
        for(int i=0;i<tamanho;i++)
            delete [] matrizAdjacencia[i];
        delete [] matrizAdjacencia;
    }

    if(arestas) delete arestas;
}

void Grafo::incluirVertice(Vertice *vertice)
{
    if(!vertice) throw QString("Parametro vazio");
    if(isFull()) throw QString("Grafo cheio");
    vertices[ultimoVerticeOcupado] = vertice;
    ultimoVerticeOcupado++;
}

void Grafo::incluirAresta(Vertice *a, Vertice *b)
{
    if(!a || !b) throw QString("Parametro vazio");
    try{

        Aresta *nova = new Aresta(a,b);

        if(existeAresta(a,b)) throw QString("Aresta ja existe");

        arestas->push_back(nova);

    }catch(std::bad_alloc&){
        throw QString("Maquina sem memoria");
    }catch(QString &erro){
        throw erro;
    }
}

void Grafo::removerAresta(Vertice *a, Vertice *b)
{
    Aresta *nova = new Aresta(a,b);
    int cont = 0;
    for(std::vector<Aresta*>::iterator i = arestas->begin(); arestas->size() && i!=arestas->end(); i++,cont++)
    {
        Aresta *aux = *i;
        if(aux->operator ==(nova)){
            i--;
            arestas->erase(arestas->begin()+cont);
        }
    }
}

Vertice **Grafo::getListaVertices() const
{
    return vertices;
}

Vertice *Grafo::getVertice(QString descricao) const
{
    int i;
    for(i=0;i<ultimoVerticeOcupado && vertices[i]->getDescricao()!=descricao ;i++);
    if(i==ultimoVerticeOcupado) throw QString("Vertice "+descricao+" nao encontrado");
    return vertices[i];
}

Vertice *Grafo::getVerticePorPosicao(int pos) const
{
    return vertices[pos];
}


int Grafo::getTamanho() const
{
    return tamanho;
}

bool Grafo::conexo() const
{
    if(!vertices[0]) return true;
    if(BuscaEmLargura(vertices[0]) == getVerticesOcupados())
        return true;
    return false;
}

bool Grafo::direcionado() const
{
    // retorna false caso seja uma matriz simetrica, ou seja, grafo nao direcionado
    for(int i=0;i<getTamanho();i++)
        for(int j=0;j<getTamanho();j++)
            if(matrizAdjacencia[i][j]!=matrizAdjacencia[j][i]) return true;
    return false;
}

bool Grafo::existeVertice(QString descricao) const
{
    int i;
    for(i=0;i<ultimoVerticeOcupado && vertices[i]->getDescricao()!=descricao ;i++);
    return i!=ultimoVerticeOcupado;
}

int Grafo::getPosicaoVertice(Vertice *vertice) const
{
    int i;
    for(i=0;i<ultimoVerticeOcupado && vertices[i]->getDescricao()!=vertice->getDescricao() ;i++);
    if(i!=ultimoVerticeOcupado) return i;
    throw QString("Vertice não existe");
}



}
