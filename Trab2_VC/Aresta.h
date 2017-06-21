#ifndef TRAB2_VC_ARESTA_H
#define TRAB2_VC_ARESTA_H

#include <iostream>
#include "Vertice.h"

class Aresta
{
    private:
        Vertice* vertice1;
        Vertice* vertice2;

    public:
        Aresta();
        Vertice* consultarVertice1();
        Vertice* consultarVertice2();
        Vertice* buscarVertice(float magn);
        void definirAresta(Vertice* v1, Vertice* v2);
        ~Aresta();
};

#endif //TRAB2_VC_ARESTA_H
