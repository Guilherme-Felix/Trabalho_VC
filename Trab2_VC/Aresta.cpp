#include "Aresta.h"

Aresta::Aresta()
{
    vertice1 = NULL;
    vertice2 = NULL;
}

Vertice* Aresta::consultarVertice1()
{
    return vertice1;
}

Vertice* Aresta::consultarVertice2()
{
    return vertice2;
}

Vertice* Aresta::buscarVertice(float magn)
{
    if(vertice1->consultarIntensidade() == magn)
        return vertice1;
    else if(vertice2->consultarIntensidade() == magn)
        return vertice2;
}

void Aresta::definirAresta(Vertice* v1, Vertice* v2)
{
    vertice1 = v1;
    vertice2 = v2;
}

Aresta::~Aresta()
{
    delete vertice1;
    delete vertice2;
}