#include "Malha.h"

Malha::Malha()
{
    celulas = new vector<Celula*>();
}

void Malha::inserirCelula(Celula *cel)
{
    celulas->push_back(cel);
}

void Malha::gerarMalha(string txt)
{
    ifstream arquivo;
    arquivo.open(txt.c_str());
    if(!arquivo.is_open())
        cout<<"Erro ao abrir o arquivo de leitura!"<<endl;
    else
    {
        //Cria variaveis auxiliares para leitura
        Vertice *v1, *v2, *v3, *v4;
        Aresta *a1, *a2, *a3, *a4;
        Celula *cel;
        int x,y;
        float magn;
        int lin, col, cont = 0;

        //Le a dimensao da malha
        arquivo >> lin >> col;

        //Faz a leitura dos pontos, cria os vertices, arestas, celulas e aloca no vetor da malha
        while(!arquivo.eof()) {
            //Cria os vertices
            arquivo >> x >> y >> magn;
            v1 = new Vertice();
            v1->definirVertice(x, y, magn, cont+1);
            arquivo >> x >> y >> magn;
            v2 = new Vertice();
            v2->definirVertice(x, y, magn, cont+2);
            arquivo >> x >> y >> magn;
            v3 = new Vertice();
            v3->definirVertice(x, y, magn, cont+3);
            arquivo >> x >> y >> magn;
            v4 = new Vertice();
            v4->definirVertice(x, y, magn, cont+4);

            cont = cont + 4;

            //Cria as arestas
            a1 = new Aresta();
            a1->definirAresta(v1, v2);

            a2 = new Aresta();
            a2->definirAresta(v2, v3);

            a3 = new Aresta();
            a3->definirAresta(v3, v4);

            a4 = new Aresta();
            a4->definirAresta(v4, v1);

            //Cria a celula
            cel = new Celula();
            cel->definirCelula(a1, a2, a3, a4);

            //Armazena a celula na malha
            inserirCelula(cel);
        }
    }
    arquivo.close();

    //No linux, ele cria uma celula extra.
    celulas->pop_back();
}

void Malha::imprimirMalha()
{
    Celula *c;
    Aresta *arestas;
    Vertice *v1,*v2,*v3,*v4;
    for(int i=0; i < celulas->size(); i++)
    {
        cout << "Celula " << i << endl;
        c = celulas->at(i);
        arestas = c->consultarArestas();
        v1 = arestas[0].consultarVertice1();
        v2 = arestas[1].consultarVertice1();
        v3 = arestas[2].consultarVertice1();
        v4 = arestas[3].consultarVertice1();

        cout << "v1 = (" << v1->consultarX() << "," << v1->consultarY() << "," <<
             v1->consultarIntensidade() << "," << v1->consultarId() << ")" << endl;
        cout << "v2 = (" << v2->consultarX() << "," << v2->consultarY() << "," <<
             v2->consultarIntensidade() << "," << v2->consultarId() << ")" << endl;
        cout << "v3 = (" << v3->consultarX() << "," << v3->consultarY() << "," <<
             v3->consultarIntensidade() << "," << v3->consultarId() << ")" << endl;
        cout << "v4 = (" << v4->consultarX() << "," << v4->consultarY() << "," <<
             v4->consultarIntensidade() << "," << v4->consultarId() << ")" << endl;
    }
}

void Malha::troca(Vertice **a, Vertice **b)
{
    Vertice *aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

/* Funcao que determina os pontos que possuem a mesma intensidade
 * @param float val: Valor da intensidade buscada
 */

void Malha::curvasDeNivel_forcaBruta(float val)
{
    Celula *c;
    Aresta *arestas;
    Vertice *v1,*v2,*v3,*v4,*q,*aux;
    float magnMin, magnMax;
    float x,y;
    int cont = 0;

    //lista que guardara os pontos escolhidos
    vector<Vertice*> *verticesContorno;

    //percorre todas as celulas buscando quais pontos tem mesma intensidade

    for (int i = 0; i < celulas->size(); i++)
    {
        c = celulas->at(i);
        arestas = c->consultarArestas();

		cout<<"Entrou nas celula: {" << i << "}\n";
        
		for (int j = 0; j < 4; j++)
        {
            v1 = arestas[j].consultarVertice1();
            v2 = arestas[j].consultarVertice2();

            if(v1->consultarIntensidade() > v2->consultarIntensidade())
            {
			
//				cout<<"Valor v1: [" << v1->consultarIntensidade() <<"]\n"<<"Valor v2: [" << v2->consultarIntensidade() <<"]\n";
//				cout << "Teste ponteiros: Antes da Troca: \n" << "v1: "<< v1 << endl << "v2: "<< v2 << endl;

				troca(&v1,&v2);

//				cout << "Teste ponteiros: Depois da Troca: \n" << "v1: "<< v1 << endl << "v2: "<< v2 << endl;

            }
			
            magnMin = v1->consultarIntensidade();
            magnMax = v2->consultarIntensidade();
//			cout << "magnMin:"<< magnMin <<". magnMax:"<< magnMax<<".\n";

            // Faz a interpolacao para o caso do escalar estar entre as magnitudes dos vertices
            if((val > magnMin && val < magnMax))
            {
				cout <<"-----------------------------\n";
				cout <<"\nValor dentro do intervalo\n";

                if (v2->consultarX() - v1->consultarX() == 0) //Aresta vertical
                {
					cout << "\n Entrou no if:Aresta Vertical\n";
//					cout << "v2x:[" << v2->consultarX() <<"]\n";
//					cout << "v1x:[" << v1->consultarX() <<"]\n";

					x = v1->consultarX();

					y = ( (val - magnMin) * (v2->consultarY() - v1->consultarY() ) ) /
                        (magnMax - magnMin) + v1->consultarY();

					cout << "Coord x:(" << x << ")\n";
					cout << "Coord y:(" << y << ")\n";
                }

                else //Aresta horizontal
                {

					cout << "\n Entrou no if:Aresta Horizontal\n";

					x = ((val - magnMin) * (v2->consultarX() - v1->consultarX())) /
						(magnMax - magnMin) + v1->consultarX();
					y = v1->consultarY();

					cout << "Coord x:(" << x << ")\n";
					cout << "Coord y:(" << y << ")\n";
				}
					
				cout << "Coord x:(" << x << ")\n";
				cout << "Coord y:(" << y << ")\n";

                q = new Vertice();
                q->definirVertice(x,y,val,cont);
                cont++;
//                verticesContorno->push_back(q);

            }/* else if(val == magnMin && val != magnMax)
				{
					q = new Vertice();
					q->definirVertice(v1->consultarX(),v1->consultarY(),val,cont);
					cont++;
					verticesContorno->push_back(q);

				} else if(val == magnMax && val != magnMin)
					{
						q = new Vertice();
						q->definirVertice(v2->consultarX(),v2->consultarY(),val,cont);
						cont++;
						verticesContorno->push_back(q);
					}*/
        }
    }
}

Malha::~Malha()
{
    delete celulas;
}
