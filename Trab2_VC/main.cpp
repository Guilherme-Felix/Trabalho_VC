#include <iostream>
#include "Vertice.h"
#include "Aresta.h"
#include "Celula.h"
#include "Malha.h"
using namespace std;

int main() 
{

    Malha *m1;
    m1 = new Malha();
    m1->gerarMalha("dados2d.txt");
    m1->imprimirMalha();
	m1->curvasDeNivel_forcaBruta(0.48);
    return 0;
}
