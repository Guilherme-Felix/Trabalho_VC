#ifndef TRAB2_VC_MALHA_H
#define TRAB2_VC_MALHA_H

/**
 *  Estrutura que guarda as celulas e as operacoes
 *  Algoritmo Forca Bruta e Marching Squares para
 *  deteccao de isolinhas (ou curvas de nivel ou ainda superficies equipotenciais)
 */

#include "Celula.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Malha
{
private:
    vector<Celula*> *celulas; //vector que guarda as celulas
    void troca(Vertice **a, Vertice **b); //funcao que troca o conteudo de duas variaveis float
public:
    Malha();
    void inserirCelula(Celula* cel);
    void gerarMalha(string txt);
    void imprimirMalha();
    void curvasDeNivel_forcaBruta(float val);
    ~Malha();

};

#endif //TRAB2_VC_MALHA_H
