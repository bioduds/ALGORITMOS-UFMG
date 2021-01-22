/*************************************************
** Título: Trabalho Prático I - Vacinação COVID-19
** Contato: eduardocapanema@ufmg.br
** Matrícula: 2020041515
** Disciplina: Algoritmos I
** Prof: Jussara Marques
/*************************************************

/** PACOTES E INCLUSÕES **/
#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

class Graph { // Classe que representa o grafo direcionado usando lista de adjacências
    int V; // Número de Vértices
	list<int> * adj; // Ponteiro para array com a lista de adjacências
	void DFSUtil( int v, bool visited[], int f ); // Função recursiva do DFS
  public:
	Graph( int V ); // Nosso construtor
	void addEdge( int v, int w ); // Função que adiciona arestas ao grafo
	void DFS( int v ); // Travessia nos vértices a partir de v
    vector<int> path; // vetor contendo os vértices nas rotas
    int fuel; // Qte de postos alcançáveis a partir de um Centro de Distribuição
    int hasCycle = 0; // 1 quando revisitamos um vértice
};

Graph::Graph( int V ) {
    this->V = V;
	adj = new list<int>[V]; // iniciamos a lista de adjacencia
}

void Graph::addEdge( int v, int w ) {
	adj[v].push_back( w ); // Adicionamos w à lista de v’s.
}

void Graph::DFSUtil( int v, bool visited[], int f=0 ) {
	visited[v] = true; // Marcamos o vértice atual como visitado
    path.push_back( v ); // incluímos o vértice visitado ao path
	list<int>::iterator i; // Recorrência nos vértices adjacentes
	for( i = adj[v].begin(); i != adj[v].end(); ++i ) {
        int nFuel = f-1;
  		if( !visited[*i] ) {
            if( nFuel >= 0 ){ DFSUtil( *i, visited, nFuel ); } // chamada recursiva
        } else { 
            if( ( *i > 0 ) && ( nFuel > 0 ) ) { hasCycle = 1; }
        }
    }
}

void Graph::DFS( int v ) { // Método Principal que realiza a travessia pelos vértices
	bool *visited = new bool[V]; // Marca todos os vértices como não visitados
	for( int i = 0; i < V; i++ ) { visited[i] = false; } // "zera"
	DFSUtil( v, visited, fuel ); // Inicia a chamada do método recursivo
}

/************* FUNÇÃO MAIN *************/
int main() {
    int c, p, x;
    cin >> c >> p >> x;
    Graph g( p + 1 ); // Incluímos 1 para os CDs - todos na posição 0
    for( int i=0; i <= ( p + c ); i++ ) {
        string line; getline( cin, line ); istringstream is( line );
        int n;
        while( is >> n ) {
            if( i <= c ) { g.addEdge( 0, n ); } // adicionamos vértices para os CDs
            else { if( n > 0 ) { g.addEdge( ( i - c ), n ); } } // adicionamos os demais vértices
        }
    }
    g.fuel = 30/x; // Calculamos o "fuel" - qte de postos que cada saída permite visitar
    g.DFS( 0 ); // Chamamos o método principal de nossa implementação
    sort( g.path.begin(), g.path.end() ); // realizamos uma ordenação conforme solicitado
    cout << g.path.size() - 1 << endl; // imprimimos o número de visitas
    for( int j=1; j < g.path.size(); j++ ) { cout << g.path[j] << " "; } // lançamos os pontos
    if( ( g.path.size() - 1 ) == 0 ) cout << "*";
    cout << endl;
    cout << g.hasCycle << endl; // dizemos se há ciclos
	return 0; // finalizamos nossa implementação
}