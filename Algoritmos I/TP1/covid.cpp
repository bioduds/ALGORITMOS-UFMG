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
#include <queue>
#include <algorithm>
using namespace std;

class Graph { // Classe que representa o grafo direcionado usando lista de adjacências
  private:
    int V; // Número de Vértices
	list<int> * adj; // Ponteiro para array com a lista de adjacências
	void DFSUtil( int v, bool visited[], int f ); // Função recursiva do DFS
  public:
	Graph( int V ); // Nosso construtor
	void addEdge( int v, int w ); // Função que adiciona arestas ao grafo
	void DFS( int v ); // Travessia nos vértices a partir de v
    vector<int> path; // vetor contendo os vértices nas rotas
    int fuel; // Qte de postos alcançáveis a partir de um Centro de Distribuição
    bool hasCycle();
};

Graph::Graph( int V ) {
    this->V = V;
	adj = new list<int>[V]; // iniciamos a lista de adjacencia
}

void Graph::addEdge( int v, int w ) {
	adj[v].push_back( w ); // Adicionamos w à lista de v’s.
}

bool Graph::hasCycle() { // encontra ciclos no grafo
    vector<int> in_degree( V, 0 ); // Cria um vetor para guardar graus dos vértices
    for( int u=0; u < V; u++ ) { // Realiza travessia na lista de adjacência preenchendo os graus. Obs: O(V+E)
        for( auto v : adj[u] ) { in_degree[v]++; }
    }
    queue<int> q; // Cria uma fila para os vértices com grau 0
    for( int i = 0; i < V; i++ ) {
        if( ( in_degree[i] == 0 ) && ( i == 0 ) ) { q.push(i); }
    }
    int cnt = 0; // inicializa contagem de vértices visitados
    vector<int> top_order; // cria vetor para guardar resultados (ordenação topológica dos vértices)
    while( !q.empty() ) { // um a um retira da fila e coloca em nova fila de adjacentes se grau do adjacente for 0
        int u = q.front(); // Pega frente da fila e adiciona na ordem topológica
        q.pop(); top_order.push_back( u );
        list<int>::iterator itr; // Corre vizinhos do retirado u e diminui seu grau
        for( itr = adj[u].begin(); itr != adj[u].end(); itr++ ) {
            if( --in_degree[*itr] == 0 ) { q.push( *itr ); } // se chegar a 0 o grau adiciona na fila
        }
        cnt++; // incrementa
    }
    return ( cnt != V );
}

void Graph::DFSUtil( int v, bool visited[], int f=0 ) {
	visited[v] = true; // Marcamos o vértice atual como visitado
    path.push_back( v ); // incluímos o vértice visitado ao path
	list<int>::iterator i; // Recorrência nos vértices adjacentes
	for( i = adj[v].begin(); i != adj[v].end(); ++i ) {
        int nFuel = f-1;
  		if( !visited[*i] ) {
            if( nFuel >= 0 ){ DFSUtil( *i, visited, nFuel ); } // chamada recursiva
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
    cout << ( g.hasCycle() ? 1 : 0 ) << endl; // dizemos se há ciclos
	return 0; // finalizamos nossa implementação
}